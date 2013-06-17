#ifndef AST_STMT_HH
# define AST_STMT_HH

# include <ast/ast.hh>

namespace ast
{
    class Stmt : public Ast
    {
        public:
            Stmt(const yy::location& location);
            virtual ~Stmt();

            virtual void accept(ConstVisitor& v) const = 0;
            virtual void accept(Visitor& v) = 0;
    };
} // namespace ast

#endif /* !AST_STMT_HH */
