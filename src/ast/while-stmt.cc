#include <ast/while-stmt.hh>

namespace ast
{
    WhileStmt::WhileStmt(const yy::location& location, Expr* cond, Stmt* loop)
        : Stmt(location)
        , cond_(cond)
        , loop_(loop)
    {}

    WhileStmt::~WhileStmt()
    {}

    const Expr* WhileStmt::cond_get() const
    {
        return cond_;
    }

    Expr* WhileStmt::cond_get()
    {
        return cond_;
    }

    const Stmt* WhileStmt::loop_get() const
    {
        return loop_;
    }

    Stmt* WhileStmt::loop_get()
    {
        return loop_;
    }

    void WhileStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void WhileStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
