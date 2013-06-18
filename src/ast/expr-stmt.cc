#include <ast/expr-stmt.hh>

namespace ast
{
    ExprStmt::ExprStmt(Expr* e)
        : Stmt(e->location_get())
        , expr_(e)
    {}

    ExprStmt::~ExprStmt()
    {
        delete expr_;
    }

    // FIXME : inline
    const Expr* ExprStmt::expr_get() const
    {
        return expr_;
    }

    // FIXME : inline
    Expr* ExprStmt::expr_get()
    {
        return expr_;
    }

    void ExprStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void ExprStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
