#ifndef AST_UNARY_EXPR_HH
# define AST_UNARY_EXPR_HH

# include <string>

# include <ast/expr.hh>

namespace ast
{
    class UnaryExpr : public Expr
    {
        public:
            enum Operator
            {
                UNARY_PLUS,
                UNARY_MINUS,
                UNARY_COMPLEMENT,
                UNARY_NOT
            };

            UnaryExpr(const yy::location& location,
                      UnaryExpr::Operator op,
                      Expr* expr);
            virtual ~UnaryExpr();

            const Expr* expr_get() const;
            Expr* expr_get();

            UnaryExpr::Operator op_get() const;

            std::string op_to_string() const;

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* expr_;
            UnaryExpr::Operator op_;
    };
} // namespace ast

#endif /* !AST_UNARY_EXPR_HH */
