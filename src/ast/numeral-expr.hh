#ifndef AST_NUMERAL_EXPR_HH
# define AST_NUMERAL_EXPR_HH

# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class NumeralExpr : public Expr
    {
        public:
            NumeralExpr(const yy::location& location, double value);
            virtual ~NumeralExpr();

            double value_get() const;

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            double value_;
    };
} // namespace ast

#endif /* !AST_NUMERAL_EXPR_HH */
