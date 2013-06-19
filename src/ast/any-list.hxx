#ifndef AST_ANY_LIST_HXX
# define AST_ANY_LIST_HXX

# include <ast/any-list.hh>

namespace ast
{
    template <class T>
    AnyList<T>::AnyList(const yy::location& location)
        : T(location)
        , delete_(true)
    {}

    template <class T>
    AnyList<T>::~AnyList()
    {
        if (delete_)
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

    template <class T>
    void AnyList<T>::set_delete(bool d)
    {
        delete_ = d;
    }
    template <class T>
    void AnyList<T>::push_back(T* elem)
    {
        list_.push_back(elem);
    }

    template <class T>
    void AnyList<T>::splice(AnyList<T>* list)
    {
        list->set_delete(false);

        list_.splice(list_.end(), list->list_get());

        delete list;
    }
} // namespace ast

#endif /* !ANY_LIST_HXX */
