#ifndef AST_EXPR_HH
# define AST_EXPR_HH

# include <ast/ast.hh>
# include <ast/visitor.hh>

namespace ast
{
    class Expr : public Ast
    {
        public:
            Expr(const yy::location& location);
            virtual ~Expr();

            virtual void accept(Visitor& v) = 0;
            virtual void accept(ConstVisitor& v) = 0;
    };
} // namespace ast

#endif /* !AST_EXPR_HH */
