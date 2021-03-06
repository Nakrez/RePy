#ifndef AST_STAR_EXPR_HH
# define AST_STAR_EXPR_HH

# include <ast/expr.hh>

namespace ast
{
    class StarExpr : public Expr
    {
        public:
            StarExpr(const yy::location& location, Expr* e);
            virtual ~StarExpr();

            const Expr* expr_get() const;
            Expr* expr_get();

            const Ast* def_get() const;
            Ast* def_get();

            void def_set(Ast* e);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* expr_;
            Ast* def_;
    };
} // namespace ast

#endif /* !AST_STAR_EXPR_HH */
