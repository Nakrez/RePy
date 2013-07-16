#ifndef REPY_BUILTIN_HH
# define REPY_BUILTIN_HH

# include <tuple>
# include <iostream>

namespace repy
{
    template<typename... Args>
    void __builtin_print(Args... a);
} // namespace repy

#endif /* !REPY_BUILTIN_HH */
