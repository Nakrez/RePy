#include <type/type-checker.hh>
#include <ast/all.hh>

namespace type
{
    TypeChecker::TypeChecker()
    {}

    TypeChecker::~TypeChecker()
    {}

    misc::Error& TypeChecker::error_get()
    {
        return error_;
    }

    void TypeChecker::type_check(ast::Expr* e1, ast::Expr* e2)
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

    void TypeChecker::operator()(ast::FunctionVar& e)
    {
        // FIXME : Dirty fix supposed to be set when an ambiguous call is made
        // This ambiguous call must only be made when checking function
        // declaration. Else it is a bug or something I did not think of.
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

        if (prototype->args_get().size()
                != e.def_get()->type_get()->args_get().size())
            error_ << misc::Error::TYPE
                   << e.location_get() << ": Function "
                   << e.def_get()->name_get() << " takes "
                   << e.def_get()->type_get()->args_get().size()
                   << " parameter(s), call made with "
                   << prototype->args_get().size() << std::endl;
        else if (!ambigous)
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
        ast::Expr* e = dynamic_cast<ast::Expr*> (ast.def_get());

        if (e)
            type_set(&ast, e);
        else if (ast.def_get())
            assert(false && "Compiler internal error");
    }

    void TypeChecker::operator()(ast::AssignExpr& e)
    {
        e.rvalue_get()->accept(*this);
        e.lvalue_get()->accept(*this);

        type_set(e.lvalue_get(), e.rvalue_get());
        type_set(&e, e.rvalue_get());

        // FIXME avoid dirty (and unsafe) thing
        if (e.def_get())
            type_set(dynamic_cast<ast::Expr*> (e.def_get()), e.rvalue_get());
    }

    void TypeChecker::operator()(ast::NumeralExpr& ast)
    {
        ast.type_set(&Int::instance());
    }

    void TypeChecker::operator()(ast::StringExpr& ast)
    {
        ast.type_set(&String::instance());
    }
} // namespace type
