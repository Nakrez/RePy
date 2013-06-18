#include <ast/numeral-expr.hh>

namespace ast
{
    NumeralExpr::NumeralExpr(const yy::location& location, double value)
        : Expr(location)
        , value_(value)
    {}

    NumeralExpr::~NumeralExpr()
    {}

    // FIXME : inline
    double NumeralExpr::value_get() const
    {
        return value_;
    }

    void NumeralExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void NumeralExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
}
