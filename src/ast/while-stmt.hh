#ifndef AST_WHILE_STMT_HH
# define AST_WHILE_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class WhileStmt : public Stmt
    {
        public:
            WhileStmt(const yy::location& location, Expr* cond, Stmt* loop);
            virtual ~WhileStmt();

            const Expr* cond_get() const;
            Expr* cond_get();

            const Stmt* loop_get() const;
            Stmt* loop_get();

            void accept(Visitor& v);
            void accept(ConstVisitor& v) const;

        protected:
            Expr* cond_;
            Stmt* loop_;
    };
} // namespace ast

#endif /* !AST_WHILE_STMT_HH */
