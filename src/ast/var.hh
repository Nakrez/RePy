#ifndef AST_VAR_HH
# define AST_VAR_HH

# include <ast/expr.hh>

namespace ast
{
    class Var : public Expr
    {
        public:
            Var(const yy::location& location);
            virtual ~Var();

            virtual void accept(Visitor& v) = 0;
            virtual void accept(ConstVisitor& v) const = 0;
    };
}

#endif /* !AST_VAR_HH */
