#include <desugar/function-call-desugar.hh>
#include <ast/all.hh>

namespace desugar
{
    FunctionCallDesugar::FunctionCallDesugar()
    {}

    FunctionCallDesugar::~FunctionCallDesugar()
    {}

    misc::Error& FunctionCallDesugar::error_get()
    {
        return error_;
    }

    // TODO: Some of the argument order modification can result to side effects
    // We need to put in temporary variables expressions that can lead to side
    // effects (function call, ...) and keep the order between all possible
    // expression that can have side effects. (We can let the constant in
    // place)
    void FunctionCallDesugar::operator()(ast::FunctionVar& ast)
    {
        const ast::ExprList* dec_get;

        if (!ast.def_get())
            dec_get = builtin::BuiltinLibrary::instance().args_get(ast);
        else
            dec_get = ast.def_get()->args_get();

        // Map all args with it expression, bool are to keep track of double
        // assignement of the same parameter which is wrong
        std::map<std::string, parameter> mapped_args;

        // Keep the order of insertion to the final recontruction
        std::vector<std::string> order_insertion;

        ast::Var* var = clone(ast.var_get());
        ast::ExprList* params = nullptr;

        if (dec_get)
        {
            if (ast.params_get() &&
                ast.params_get()->list_get().size() >
                dec_get->list_get().size())
                error_ << misc::Error::TYPE
                       << ast.params_get()->location_get()
                       << ": Too much parameters specified"
                       << std::endl;
            else
            {
                // Takes the function definition and build a mapping from it
                // for example def fun(a, b, c = 1)
                // will generate
                // a -> nullptr
                // b -> nullptr
                // c -> 1
                build_mapping(dec_get, mapped_args, order_insertion);

                if (ast.params_get())
                {
                    // Match the function call with the map built previously
                    // Let takes the same example. (def fun(a, b, c=1))
                    // Called it with fun(1, 2)
                    // The function will do
                    // a -> 1
                    // b -> 2
                    // c -> 1
                    build_call(ast.params_get(), mapped_args, order_insertion);
                }

                // Finally transform the map to a function call
                // So from or previous example we will build
                // fun(1, 2, 1)
                params = generate_call(ast.location_get(), mapped_args,
                                       order_insertion);
            }
        }
        else if (ast.params_get() && ast.params_get()->list_get().size() > 0)
                error_ << misc::Error::TYPE
                       << ast.params_get()->location_get()
                       << ": Too much parameters specified"
                       << std::endl;

        ast::FunctionVar* v = new ast::FunctionVar(ast.location_get(), var,
                                                   params);

        v->type_set(ast.type_get());

        cloned_ast_ = v;
    }

    void FunctionCallDesugar::build_call(const ast::ExprList* args,
                                         std::map<std::string,
                                                  parameter>& args_map,
                                         std::vector<std::string>& order)
    {
        auto order_it = order.begin();
        bool positional = true;

        for (auto call_arg : args->list_get())
        {
            ast::AssignExpr* e = dynamic_cast<ast::AssignExpr*> (call_arg);

            if (e)
            {
                std::string s = name_get(e->lvalue_get());
                positional = false;

                if (args_map[s].second)
                    error_ << misc::Error::TYPE
                        << call_arg->location_get() << ": Parameter " << s
                        << " already specified" << std::endl;
                else
                    args_map[s] = parameter(e->rvalue_get(), true);
            }
            else if (!positional)
                error_ << misc::Error::TYPE
                    << call_arg->location_get() << ": Non positional argument"
                    << " detected after positional argument"
                    << std::endl;
            else
            {
                std::string s = *order_it;

                if (args_map[s].second)
                    error_ << misc::Error::TYPE
                        << call_arg->location_get() << ": Parameter " << s
                        << " already specified" << std::endl;
                else
                    args_map[s] = parameter(call_arg, true);

                ++order_it;
            }
        }
    }

    void FunctionCallDesugar::build_mapping(const ast::ExprList* args,
            std::map<std::string,
            parameter>& args_map,
            std::vector<std::string>& order)
    {
        // Build the mapping
        for (auto param : args->list_get())
        {
            ast::AssignExpr* e = dynamic_cast<ast::AssignExpr*> (param);

            if (e)
            {
                std::string s = name_get(e->lvalue_get());

                args_map[s] = parameter(e->rvalue_get(), false);
                order.push_back(s);
            }
            else
            {
                std::string s = name_get(param);

                args_map[s] = parameter(nullptr,
                        false);
                order.push_back(s);
            }
        }
    }

    ast::ExprList*
    FunctionCallDesugar::generate_call(const yy::location& loc,
                                       std::map<std::string,
                                                parameter>& args_map,
                                       std::vector<std::string>& order)
    {
        ast::ExprList* params = new ast::ExprList(loc);

        for (auto arg : order)
        {
            if (!args_map[arg].first)
                error_ << misc::Error::TYPE
                       << loc << ": Argument " << arg
                       << " not specified" << std::endl;
            else
                params->push_back(clone(args_map[arg].first));
        }

        return params;
    }

    const std::string& FunctionCallDesugar::name_get(const ast::Expr* e)
    {
        const ast::IdVar* v = dynamic_cast<const ast::IdVar*> (e);

        assert(v && "Internal compiler error");

        return v->id_get();
    }
} // namespace desugar
