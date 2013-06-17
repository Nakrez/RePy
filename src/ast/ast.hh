#ifndef AST_AST_HH
# define AST_AST_HH

# include <parser/location.hh>

# include <ast/visitor.hh>

namespace ast
{
    class Ast
    {
        public:
            Ast(const yy::location& location);
            virtual ~Ast();

            virtual void accept(ConstVisitor& v) const = 0;
            virtual void accept(Visitor& v) = 0;

            const yy::location& location_get() const;

        protected:
            yy::location loc_;
    };
} // namespace ast

# include <ast/ast.hxx>

#endif /* !AST_AST_HH */
