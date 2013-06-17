#include <ast/continue-stmt.hh>

namespace ast
{
    ContinueStmt::ContinueStmt(const yy::location& location)
        : Stmt(location)
    {}

    ContinueStmt::~ContinueStmt()
    {}

    void ContinueStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void ContinueStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
