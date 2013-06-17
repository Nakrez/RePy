#ifndef AST_AST_HXX
# define AST_AST_HXX

# include <ast/ast.hh>

namespace ast
{
    inline const yy::location& Ast::location_get() const
    {
        return loc_;
    }
} // namespace ast

#endif /* !AST_AST_HXX */
