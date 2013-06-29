#include <ast/star-expr.hh>

namespace ast
{
    StarExpr::StarExpr(const yy::location& location, Expr* e)
        : Expr(location)
        , expr_(e)
        , def_(nullptr)
    {}

    StarExpr::~StarExpr()
    {
        delete expr_;
    }

    const Expr* StarExpr::expr_get() const
    {
        return expr_;
    }

    Expr* StarExpr::expr_get()
    {
        return expr_;
    }

    const Ast* StarExpr::def_get() const
    {
        return def_;
    }

    Ast* StarExpr::def_get()
    {
        return def_;
    }

    void StarExpr::def_set(Ast* e)
    {
        def_ = e;
    }

    void StarExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void StarExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
