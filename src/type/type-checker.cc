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
            if (!fun_type->compatible_with(*ret_type))
            {
                error_ << misc::Error::TYPE
                       << ast.location_get() << ": Type error, function has "
                       << "deduced type " << *fun_type << ", but return is "
                       << *ret_type << std::endl;
            }
        }
        else
        {
            to_type->type_get()->return_type_set(ret_type);
        }
    }

    void TypeChecker::operator()(ast::FunctionDec& s)
    {
        s.type_set(new Function());

        if (s.args_get())
        {
            for (auto arg : s.args_get()->list_get())
            {
                ast::IdVar* var = dynamic_cast<ast::IdVar*> (arg);

                if (var)
                {
                    var->type_set(&Polymorphic::instance());
                    s.type_get()->args_type_add(&Polymorphic::instance());
                }
                else
                {
                    arg->accept(*this);
                    s.type_get()->args_type_add(arg->type_get());
                }
            }
        }

        in_declaration_.push(&s);
        s.body_get()->accept(*this);
        in_declaration_.pop();

        if (!s.type_get()->return_type_get())
            s.type_get()->return_type_set(&Void::instance());
    }

    void TypeChecker::operator()(ast::FunctionVar&)
    {

    }

    void TypeChecker::operator()(ast::OpExpr& ast)
    {
        ast.left_expr_get()->accept(*this);
        ast.right_expr_get()->accept(*this);

        type_check(ast.left_expr_get(), ast.right_expr_get());

        // So far if there is no error it does not really matter if the opexpr
        // has right expr of left expr type since they are the same due to
        // strong type of python
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
