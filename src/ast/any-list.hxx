#ifndef AST_ANY_LIST_HXX
# define AST_ANY_LIST_HXX

# include <ast/any-list.hh>

namespace ast
{
    template <class T>
    AnyList<T>::AnyList(const yy::location& location)
        : Ast(location)
    {}

    template <class T>
    AnyList<T>::~AnyList()
    {
        for (auto elem : list_)
            delete elem;
    }

    template <class T>
    void AnyList<T>::accept(Visitor& v)
    {
        v(*this);
    }

    template <class T>
    void AnyList<T>::accept(ConstVisitor& v) const
    {
        v(*this);
    }

    template <class T>
    const std::list<T*>& AnyList<T>::list_get() const
    {
        return list_;
    }

    template <class T>
    std::list<T*>& AnyList<T>::list_get()
    {
        return list_;
    }
} // namespace ast

#endif /* !ANY_LIST_HXX */
