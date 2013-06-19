#include <ast/if-stmt.hh>

namespace ast
{

    IfStmt::IfStmt(const yy::location& location,
                   Expr* cond,
                   Stmt* true_stmt,
                   Stmt* else_stmt)
        : Stmt(location)
        , cond_(cond)
        , true_(true_stmt)
        , else_(else_stmt)
    {}

    IfStmt::~IfStmt()
    {
        delete cond_;
        delete true_;
        delete else_;
    }

    void IfStmt::set_else_stmt(Stmt* else_stmt)
    {
        if (else_ == nullptr)
        {
            else_ = else_stmt;
            return;
        }

        IfStmt* i = dynamic_cast<IfStmt*> (else_);

        if (i)
            i->set_else_stmt(else_stmt);
    }

    const Expr* IfStmt::cond_get() const
    {
        return cond_;
    }

    Expr* IfStmt::cond_get()
    {
        return cond_;
    }

    const Stmt* IfStmt::true_stmt_get() const
    {
        return true_;
    }

    Stmt* IfStmt::true_stmt_get()
    {
        return true_;
    }

    const Stmt* IfStmt::else_stmt_get() const
    {
        return else_;
    }

    Stmt* IfStmt::else_stmt()
    {
        return else_;
    }

    void IfStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void IfStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
