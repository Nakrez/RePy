#include <ast/yield-expr.hh>

namespace ast
{
    YieldExpr::YieldExpr(const yy::location& location, Expr* ret_value)
        : Expr(location)
        , ret_value_(ret_value)
    {}

    YieldExpr::~YieldExpr()
    {}

    const Expr* YieldExpr::ret_value_get() const
    {
        return ret_value_;
    }

    Expr* YieldExpr::ret_value_get()
    {
        return ret_value_;
    }

    void YieldExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void YieldExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
