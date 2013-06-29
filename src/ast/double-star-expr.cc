#include <ast/double-star-expr.hh>

namespace ast
{
    DoubleStarExpr::DoubleStarExpr(const yy::location& loc, Expr* e)
        : StarExpr(loc, e)
    {}

    DoubleStarExpr::~DoubleStarExpr()
    {}

    void DoubleStarExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void DoubleStarExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
