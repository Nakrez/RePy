#ifndef MISC_MUTABLE_REF_HXX
# define MISC_MUTABLE_REF_HXX

# include <misc/mutable-ref.hh>

namespace misc
{
    template <class T>
    MutableRef<T>::MutableRef(T& t)
        : ref_(&t)
    {}

    template <class T>
    MutableRef<T>::~MutableRef()
    {}

    template <class T>
    T& MutableRef<T>::operator&()
    {
        return *ref_;
    }

    template <class T>
    const T& MutableRef<T>::operator&() const
    {
        return *ref_;
    }

    template <class T>
    void MutableRef<T>::swap(MutableRef<T>& ref)
    {
        T* temp = ref_;

        ref_ = ref.ref_;
        ref.ref_ = temp;
    }
} // namespace misc

namespace std
{
    template<class T>
    inline void swap(misc::MutableRef<T>& a, misc::MutableRef<T>& b)
    {
        a.swap(b);
    }
}

#endif /* !MISC_MUTABLE_REF_HXX */
