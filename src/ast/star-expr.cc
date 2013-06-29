#include <ast/star-expr.hh>

namespace ast
{
    StarExpr::StarExpr(const yy::location& location, Expr* e)
        : Expr(location)
        , expr_(e)
    {}

    StarExpr::~StarExpr()
    {}

    const Expr* StarExpr::expr_get() const
    {
        return expr_;
    }

    Expr* StarExpr::expr_get()
    {
        return expr_;
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
