#ifndef LIB_REPY_HH
# define LIB_REPY_HH

# include <repy/types.hh>
# include <repy/builtin.hh>

namespace repy
{
    template<class T>
    T __add__(T a, T b);

    template<class T>
    T __mul__(T a, T b);

    template<class T>
    T __ge__(T a, T b);

    template<class T>
    T __le__(T a, T b);

    template<class T>
    T __lt__(T a, T b);
} // namespace repy

# include <repy/repy.hxx>

#endif /* !LIB_REPY_HH */
