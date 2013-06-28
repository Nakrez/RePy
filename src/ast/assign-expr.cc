#include <ast/assign-expr.hh>

namespace ast
{
    AssignExpr::AssignExpr(const yy::location& location,
                           Expr* lvalue,
                           Expr* rvalue)
        : Expr(location)
        , lvalue_(lvalue)
        , rvalue_(rvalue)
        , def_(nullptr)
    {}

    AssignExpr::~AssignExpr()
    {
        delete lvalue_;
        delete rvalue_;
    }

    const Expr* AssignExpr::lvalue_get() const
    {
        return lvalue_;
    }

    Expr* AssignExpr::lvalue_get()
    {
        return lvalue_;
    }

    const Expr* AssignExpr::rvalue_get() const
    {
        return rvalue_;
    }

    Expr* AssignExpr::rvalue_get()
    {
        return rvalue_;
    }

    void AssignExpr::lvalue_set(Expr* e)
    {
        if (lvalue_ == nullptr)
        {
            lvalue_ = e;
            return;
        }

        AssignExpr* l = dynamic_cast<AssignExpr*> (lvalue_);

        if (l)
            l->lvalue_set(e);
    }

    const Ast* AssignExpr::def_get() const
    {
        return def_;
    }

    Ast* AssignExpr::def_get()
    {
        return def_;
    }

    void AssignExpr::def_set(Ast* a)
    {
        def_ = a;
    }

    void AssignExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void AssignExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
