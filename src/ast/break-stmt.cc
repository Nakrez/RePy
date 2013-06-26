#include <ast/break-stmt.hh>

namespace ast
{
    BreakStmt::BreakStmt(const yy::location& location)
        : Stmt(location)
        , in_loop_(nullptr)
    {}

    BreakStmt::~BreakStmt()
    {
        // Not responsable to delete the loop
    }

    const Stmt* BreakStmt::in_loop_get() const
    {
        return in_loop_;
    }

    Stmt* BreakStmt::in_loop_get()
    {
        return in_loop_;
    }

    void BreakStmt::in_loop_set(Stmt* loop)
    {
        in_loop_ = loop;
    }

    void BreakStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void BreakStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
