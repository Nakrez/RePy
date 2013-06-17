#ifndef AST_DEFAULT_VISITOR_HXX
# define AST_DEFAULT_VISITOR_HXX

# include <ast/default-visitor.hh>

namespace ast
{
    template <template <typename> class Const>
    GenDefaultVisitor<Const>::~GenDefaultVisitor()
    {}
} // namespace ast

#endif /* !AST_DEFAULT_VISITOR_HXX */
