#ifndef AST_ASSIGN_EXPR_HH
# define AST_ASSIGN_EXPR_HH

# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class AssignExpr : public Expr
    {
        public:
            AssignExpr(const yy::location& location,
                       Expr* lvalue,
                       Expr* rvalue);
            virtual ~AssignExpr();

            const Expr* lvalue_get() const;
            Expr* lvalue_get();

            const Expr* rvalue_get() const;
            Expr* rvalue_get();

            void lvalue_set(Expr* e);

            void accept(Visitor& v);
            void accept(ConstVisitor& v) const;

        protected:
            Expr* lvalue_;
            Expr* rvalue_;
    };
} // namespace ast

#endif /* !AST_ASSIGN_EXPR_HH */
