#ifndef REPY_BUILTIN_HH
# define REPY_BUILTIN_HH

# include <tuple>
# include <iostream>
# include <algorithm>

# include <repy/types.hh>

namespace repy
{
    template<class T>
    T& deref(T& t);

    template<class T>
    T& deref(T* t);

    template<typename... Args>
    void __builtin_print(Args... a);

    __repy_string* __builtin_input(__repy_string* str);

    __repy_int __builtin_float(__repy_string* str);
} // namespace repy

# include <repy/builtin.hxx>

#endif /* !REPY_BUILTIN_HH */
