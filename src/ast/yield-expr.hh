#ifndef AST_YIELD_EXPR_HH
# define AST_YIELD_EXPR_HH

# include <ast/expr.hh>

namespace ast
{
    class YieldExpr : public Expr
    {
        public:
            YieldExpr(const yy::location& location, Expr* ret_value);
            virtual ~YieldExpr();

            const Expr* ret_value_get() const;
            Expr* ret_value_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* ret_value_;
    };
} // namespace ast

#endif /* !AST_YIELD_EXPR_HH */
