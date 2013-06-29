#ifndef AST_DOUBLE_STAR_EXPR_HH
# define AST_DOUBLE_STAR_EXPR_HH

# include <ast/star-expr.hh>

namespace ast
{
    class DoubleStarExpr : public StarExpr
    {
        public:
            DoubleStarExpr(const yy::location& loc, Expr* e);
            virtual ~DoubleStarExpr();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;
    };
} // namespace ast

#endif /* !AST_DOUBLE_STAR_EXPR_HH */
