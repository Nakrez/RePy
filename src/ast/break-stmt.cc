#include <ast/break-stmt.hh>

namespace ast
{
    BreakStmt::BreakStmt(const yy::location& location)
        : Stmt(location)
    {}

    BreakStmt::~BreakStmt()
    {}

    void BreakStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void BreakStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
