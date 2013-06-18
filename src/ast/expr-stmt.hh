#ifndef AST_EXPR_STMT_HH
# define AST_EXPR_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class ExprStmt : public Stmt
    {
        public:
            ExprStmt(Expr* e);
            virtual ~ExprStmt();

            const Expr* expr_get() const;
            Expr* expr_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* expr_;
    };
} // namespace ast

#endif /* !AST_EXPR_STMT_HH */
