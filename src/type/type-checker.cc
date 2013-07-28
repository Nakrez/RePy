#include <type/type-checker.hh>
#include <ast/all.hh>

namespace type
{
    TypeChecker::TypeChecker()
        : current_class_(nullptr)
    {}

    TypeChecker::~TypeChecker()
    {}

    misc::Error& TypeChecker::error_get()
    {
        return error_;
    }

    void TypeChecker::type_check(ast::Expr* e1, ast::Expr* e2)
    {
        // FIXME : quick fix that breaks multiple type error report
        if (error_.error_type_get() == misc::Error::NONE)
        {
            if (!e1->type_get() || !e2->type_get())
                assert(false && "Compiler internal error");

            if (!e1->type_get()->compatible_with(*(e2->type_get())))
            {
                error_ << misc::Error::TYPE
                    << e1->location_get() << ": Type error, excpected "
                    << *(e1->type_get()) << ", got " << *(e2->type_get())
                    << std::endl;
            }
        }
    }

    void TypeChecker::type_set(ast::Expr* e1, ast::Expr* e2)
    {
        e1->type_set(e2->type_get());
    }

    Type* TypeChecker::type_call(ast::FunctionDec* d, Function* type)
    {
        // Look if prototype has already been checked
        for (auto proto : d->to_generate_get())
        {
            if (proto->compatible_with(*type))
                return proto->return_type_get();
        }

        // Else check this prototype
        Function* temp = d->type_get();

        // Set the prototype to function prototype
        d->type_set(type);

        // Add the prototype to be generated later (and for same check later)
        d->to_generate_add(type);

        // Check the body
        in_declaration_.push(d);
        d->body_get()->accept(*this);
        in_declaration_.pop();

        if (!d->type_get()->return_type_get())
            d->type_get()->return_type_set(&Void::instance());

        // Restore function original prototype
        d->type_set(temp);

        return type->return_type_get();
    }

    void TypeChecker::operator()(ast::ReturnStmt& ast)
    {
        type::Type* ret_type = &Void::instance();
        ast::FunctionDec* to_type = in_declaration_.top();
        type::Type* fun_type = to_type->type_get()->return_type_get();

        if (ast.ret_value_get())
        {
            ast.ret_value_get()->accept(*this);
            ret_type = ast.ret_value_get()->type_get();
        }

        if (fun_type)
        {
            if (fun_type == &Polymorphic::instance())
                to_type->type_get()->return_type_set(ret_type);
            else if (!fun_type->compatible_with(*ret_type))
                error_ << misc::Error::TYPE
                       << ast.location_get() << ": Type error, function has "
                       << "deduced type " << *fun_type << ", but return is "
                       << *ret_type << std::endl;
        }
        else
            to_type->type_get()->return_type_set(ret_type);
    }

    void TypeChecker::operator()(ast::FunctionDec& s)
    {
        Function* f_type = new Function();

        s.type_set(f_type);

        if (s.args_get())
        {
            for (auto arg : s.args_get()->list_get())
            {
                ast::IdVar* var = dynamic_cast<ast::IdVar*> (arg);

                if (var)
                {
                    // If it is a var type it as polymorphic type
                    // for the correctness check (better check will be
                    // performed when type checking function call)
                    // -> see operator()(ast::FunctionVar&)
                    var->type_set(&Polymorphic::instance());
                    f_type->args_type_add(&Polymorphic::instance());
                }
                else
                {
                    // If it is an assignement type it as it must be
                    arg->accept(*this);
                    f_type->args_type_add(arg->type_get());
                }
            }
        }

        in_declaration_.push(&s);
        s.body_get()->accept(*this);
        in_declaration_.pop();

        if (!f_type->return_type_get())
            f_type->return_type_set(&Void::instance());
    }

    void TypeChecker::operator()(ast::ClassDec& ast)
    {
        if (declared_class_[ast.name_get()])
            error_ << misc::Error::TYPE
                   << ast.location_get() << " : Redeclaration of class"
                   << ast.name_get() << std::endl;
        else
            declared_class_[ast.name_get()] = &ast.type_get();

        current_class_ = &ast.type_get();
        ast.def_get()->accept(*this);
        current_class_ = nullptr;
    }

    void TypeChecker::operator()(ast::FunctionVar& e)
    {
        // FIXME : Dirty fix supposed to be set when an ambiguous call is made
        // This ambiguous call must only be made when checking function
        // declaration. Else it is a bug or something I did not think of.
        ast::ExprList* tmp = generate_prototype(e);

        if (e.params_get() != tmp)
        {
            delete e.params_get();
            e.params_set(tmp);
        }

        // If def get is null it is a builtin function (or a bug)
        if (!e.def_get())
        {
            builtin::BuiltinLibrary::instance().type_check(e, error_, *this);
            return;
        }

        bool ambigous = false;
        Function* prototype = new Function();

        if (e.params_get())
        {
            for (auto p : e.params_get()->list_get())
            {
                p->accept(*this);

                if (p->type_get() == &Polymorphic::instance())
                    ambigous = true;

                prototype->args_type_add(p->type_get());
            }
        }

        if (!ambigous)
        {
            e.type_set(type_call(e.def_get(), prototype));

            // If the result of the process is Polymorphic type then the code
            // is invalid or contains a part of unsupported stuff.
            // If you fine any example that is valid and fully supported
            // I would be glad to see it and review my algorithm
            if (e.type_get() == &Polymorphic::instance())
                error_ << misc::Error::TYPE
                       << e.location_get() << ": Function return type "
                       << "ambiguous or contains unsupported stuff."
                       << " If you believe your code works and is supported "
                       << "please report it as BUG. Thanks !"
                       << std::endl;
            else if (!e.type_get())
                e.type_set(&Polymorphic::instance());
        }
        else
            e.type_set(&Polymorphic::instance());
    }

    void TypeChecker::operator()(ast::OpExpr& ast)
    {
        ast.left_expr_get()->accept(*this);
        ast.right_expr_get()->accept(*this);

        type_check(ast.left_expr_get(), ast.right_expr_get());

        // So far if there is no error it does not really matter if the opexpr
        // has right expr of left expr type since they are the same due to
        // strong type of python just check if one of them is non polymorphic
        if (ast.left_expr_get()->type_get() == &Polymorphic::instance())
            type_set(&ast, ast.right_expr_get());
        else
            type_set(&ast, ast.left_expr_get());
    }

    void TypeChecker::operator()(ast::IdVar& ast)
    {
        if (ast.id_get() == "self")
        {
            if (current_class_)
                ast.type_set(current_class_);
            else
                error_ << misc::Error::TYPE
                       << ast.location_get() << " : self used outside class "
                       << "definition" << std::endl;
            return;
        }
        ast::Expr* e = dynamic_cast<ast::Expr*> (ast.def_get());

        if (e)
            type_set(&ast, e);
        else if (ast.def_get())
            assert(false && "Compiler internal error");
    }

    void TypeChecker::operator()(ast::FieldVar& ast)
    {
        ast.var_get()->accept(*this);

        type::Class* field_super = nullptr;

        field_super = dynamic_cast<type::Class*> (ast.var_get()->type_get());

        // If the type of the field before is not a class or is not set
        if (!field_super)
        {
            error_ << misc::Error::TYPE
                   << ast.location_get() << " : not a class" << std::endl;
            return;
        }

        // If name already exists in the class definition
        if (field_super->component_get(ast.name_get()))
        {
            ast::Ast* dec = field_super->component_get(ast.name_get());

            ast::FieldVar* var = dynamic_cast<ast::FieldVar*> (dec);

            // If the name is not a field in the definition -> error
            if (!var)
            {
                error_ << misc::Error::TYPE
                       << ast.location_get() << " : " << ast.name_get()
                       << " member of " << field_super << " not declared as"
                       << " field" << std::endl;
                return;
            }

            // If the definition as no type
            if (!var->type_get())
            {
                error_ << misc::Error::TYPE
                       << ast.location_get() << " : can't deduce type of "
                       << *ast.var_get() << std::endl;
                return;
            }

            // Else OK
            type_set(&ast, var);
        }
        else // If the name does not exists the define it in the class
            field_super->component_add(ast.name_get(), &ast);
    }

    void TypeChecker::operator()(ast::AssignExpr& e)
    {
        e.rvalue_get()->accept(*this);
        e.lvalue_get()->accept(*this);

        type_set(e.lvalue_get(), e.rvalue_get());
        type_set(&e, e.rvalue_get());

        // FIXME avoid dirty (and unsafe) thing
        if (e.def_get())
            type_check(dynamic_cast<ast::Expr*> (e.def_get()), &e);
    }

    void TypeChecker::operator()(ast::NumeralExpr& ast)
    {
        ast.type_set(&Int::instance());
    }

    void TypeChecker::operator()(ast::StringExpr& ast)
    {
        ast.type_set(&String::instance());
    }

    const std::string& TypeChecker::name_get(const ast::Expr* e)
    {
        const ast::IdVar* v = dynamic_cast<const ast::IdVar*> (e);

        assert(v && "Internal compiler error");

        return v->id_get();
    }

    void TypeChecker::build_mapping(const ast::ExprList* args,
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

    void TypeChecker::build_call(const ast::ExprList* args,
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

    ast::ExprList* TypeChecker::generate_list(const yy::location& loc,
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

    ast::Expr* TypeChecker::clone(ast::Ast* ast)
    {
        cloner::AstCloner clone;

        clone.visit(ast);

        return dynamic_cast<ast::Expr*> (clone.cloned_ast_get());
    }
} // namespace type
