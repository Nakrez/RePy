#include <ast/pass-stmt.hh>

namespace ast
{
    PassStmt::PassStmt(const yy::location& location)
        : Stmt(location)
    {}

    PassStmt::~PassStmt()
    {}

    void PassStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void PassStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
