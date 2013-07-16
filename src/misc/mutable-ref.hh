#ifndef MISC_MUTABLE_REF_HH
# define MISC_MUTABLE_REF_HH

namespace misc
{
    template <class T>
    class MutableRef
    {
        public:
            MutableRef(T& t);
            ~MutableRef();

            T& operator&();
            const T& operator&() const;

            void swap(MutableRef<T>& ref);
        protected:
            T* ref_;
    };
} // namespace misc

namespace std
{
    template<class T>
    void swap(misc::MutableRef<T>& a, misc::MutableRef<T>& b);
}

# include <misc/mutable-ref.hxx>

#endif /* !MISC_MUTABLE_REF_HH */
