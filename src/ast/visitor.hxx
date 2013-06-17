#ifndef AST_VISITOR_HXX
# define AST_VISITOR_HXX

# include <ast/visitor.hh>

namespace ast
{
    template <template <typename> class Const>
    template <typename T>
    void GenVisitor<Const>::visit(T* a)
    {
        if (a)
            a->accept(*this);
    }

    template <template <typename> class Const>
    template <typename T>
    void GenVisitor<Const>::visit(typename Const<T>::type& a)
    {
        a.accept(*this);
    }

    template <template <typename> class Const>
    void GenVisitor<Const>::operator()(typename Const<Ast>::type& ast)
    {
        ast.accept(*this);
    }
} // namespace ast

#endif /* !AST_VISITOR_HXX */
