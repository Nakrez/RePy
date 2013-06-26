#include <ast/continue-stmt.hh>

namespace ast
{
    ContinueStmt::ContinueStmt(const yy::location& location)
        : Stmt(location)
    {}

    ContinueStmt::~ContinueStmt()
    {}

    const Stmt* ContinueStmt::in_loop_get() const
    {
        return in_loop_;
    }

    Stmt* ContinueStmt::in_loop_get()
    {
        return in_loop_;
    }

    void ContinueStmt::in_loop_set(Stmt* l)
    {
        in_loop_ = l;
    }

    void ContinueStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void ContinueStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
