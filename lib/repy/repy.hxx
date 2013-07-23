#ifndef LIB_REPY_HXX
# define LIB_REPY_HXX

# include <repy/repy.hh>

namespace repy
{
    template<class T>
    T __add__(T a, T b)
    {
        return a.__add__(b);
    }

    template <>
    __repy_int __add__(__repy_int a, __repy_int b)
    {
        return a + b;
    }

    template<class T>
    T __mul__(T a, T b)
    {
        return a.__mul__(b);
    }

    template <>
    __repy_int __mul__(__repy_int a, __repy_int b)
    {
        return a * b;
    }

    template<class T>
    T __le__(T a, T b)
    {
        return a.__le__(b);
    }

    template <>
    __repy_int __le__(__repy_int a, __repy_int b)
    {
        return a <= b;
    }
} // namespace repy

#endif /* !LIB_REPY_HXX */
