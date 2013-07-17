#ifndef REPY_BUILTIN_HH
# define REPY_BUILTIN_HH

# include <tuple>
# include <iostream>
# include <algorithm>

# include <repy/types.hh>

namespace repy
{
    template<typename... Args>
    void __builtin_print(Args... a);

    __repy_string* __builtin_input(__repy_string* str);
} // namespace repy

# include <repy/builtin.hxx>

#endif /* !REPY_BUILTIN_HH */
