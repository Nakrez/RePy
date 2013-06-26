#ifndef AST_IF_STMT_HH
# define AST_IF_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class IfStmt : public Stmt
    {
        public:
            IfStmt(const yy::location& location,
                   Expr* cond,
                   Stmt* true_stmt,
                   Stmt* else_stmt);
            virtual ~IfStmt();

            void set_else_stmt(Stmt* else_stmt);

            const Expr* cond_get() const;
            Expr* cond_get();

            const Stmt* true_stmt_get() const;
            Stmt* true_stmt_get();

            const Stmt* else_stmt_get() const;
            Stmt* else_stmt_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* cond_;
            Stmt* true_;
            Stmt* else_;
    };
} // namespace ast

#endif /* !AST_IF_STMT_HH */
