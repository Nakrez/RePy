#include <ast/string-expr.hh>

namespace ast
{
    StringExpr::StringExpr(const yy::location& location,
                           const std::string& str)
        : Expr(location)
        , str_(str)
    {}

    StringExpr::~StringExpr()
    {}

    void StringExpr::append(const std::string& str)
    {
        str_ += str;
    }

    const std::string& StringExpr::str_get() const
    {
        return str_;
    }

    void StringExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void StringExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }

} // namespace ast
