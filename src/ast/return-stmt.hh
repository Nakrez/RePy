#ifndef AST_RETURN_STMT_HH
# define AST_RETURN_STMT_HH

# include <ast/stmt.hh>
# include <ast/expr.hh>

namespace ast
{
    class ReturnStmt : public Stmt
    {
        public:
            ReturnStmt(const yy::location& location, Expr* ret_value);
            virtual ~ReturnStmt();

            const Expr* ret_value_get() const;
            Expr* ret_value_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* ret_value_;
    };
} // namespace ast

#endif /* !AST_RETURN_STMT_HH */
