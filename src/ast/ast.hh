#ifndef AST_AST_HH
# define AST_AST_HH

namespace ast
{
    class Ast
    {
        public:
            Ast() = default;
            virtual ~Ast() = default;

            virtual void accept(ConstVisitor& v) const = 0;
            virtual void accept(Visitor& v) const = 0;
    };
} // namespace ast

#endif /* !AST_AST_HH */
