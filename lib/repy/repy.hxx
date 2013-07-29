#ifndef LIB_REPY_HXX
# define LIB_REPY_HXX

# include <repy/repy.hh>

namespace repy
{
    template<class T>
    T __add__(T a, T b)
    {
        return a->__add__(b);
    }

    template <>
    __repy_int __add__(__repy_int a, __repy_int b)
    {
        return a + b;
    }

    template <>
    __repy_string* __add__(__repy_string* a, __repy_string* b)
    {
        a->append(*b);
        return a;
    }

    template<class T>
    T __mul__(T a, T b)
    {
        return a->__mul__(b);
    }

    template <>
    __repy_int __mul__(__repy_int a, __repy_int b)
    {
        return a * b;
    }

    template<class T>
    T __ge__(T a, T b)
    {
        return a->__ge__(b);
    }

    template <>
    __repy_int __ge__(__repy_int a, __repy_int b)
    {
        return a >= b;
    }

    template<class T>
    T __gt__(T a, T b)
    {
        return a->__gt__(b);
    }

    template <>
    __repy_int __gt__(__repy_int a, __repy_int b)
    {
        return a > b;
    }

    template<class T>
    T __le__(T a, T b)
    {
        return a->__le__(b);
    }

    template <>
    __repy_int __le__(__repy_int a, __repy_int b)
    {
        return a <= b;
    }

    template<class T>
    T __lt__(T a, T b)
    {
        return a->__lt__(b);
    }

    template <>
    __repy_int __lt__(__repy_int a, __repy_int b)
    {
        return a < b;
    }
} // namespace repy

#endif /* !LIB_REPY_HXX */
