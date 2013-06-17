#ifndef MISC_CONSTNESS_HH
# define MISC_CONSTNESS_HH

namespace misc
{
    template <typename T>
    struct const_type
    {
        typedef const T type;
    };

    template <typename T>
    struct nonconst_type
    {
        typedef T type;
    };
} // namespace misc

#endif /* !MISC_CONSTNESS_HH */
