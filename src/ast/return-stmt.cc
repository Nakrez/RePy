#include <ast/return-stmt.hh>

namespace ast
{
    ReturnStmt::ReturnStmt(const yy::location& location, Expr* ret_value)
        : Stmt(location)
        , ret_value_(ret_value)
    {}

    ReturnStmt::~ReturnStmt()
    {}

    const Expr* ReturnStmt::ret_value_get() const
    {
        return ret_value_;
    }

    Expr* ReturnStmt::ret_value_get()
    {
        return ret_value_;
    }

    void ReturnStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void ReturnStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
