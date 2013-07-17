#ifndef REPY_BUILTIN_HXX
# define REPY_BUILTIN_HXX

# include <repy/builtin.hh>

namespace repy
{
    template<unsigned N>
    struct __internal_print
    {
        template<typename T>
        static void call(T& a)
        {
            __internal_print<N - 1>::call(a);
            std::cout << std::get<N>(a) << " ";
        }
    };

    template<>
    struct __internal_print<0>
    {
        template<typename T>
        static void call(T& a)
        {
            std::cout << std::get<0>(a) << " ";
        }
    };

    template<typename... Args>
    void __builtin_print(Args... a)
    {
        std::tuple<Args...> args = std::make_tuple(a...);

        const unsigned size = std::tuple_size<std::tuple<Args...>>::value - 1;

        __internal_print<size>::call(args);
        std::cout << std::endl;
    }
} // namespace repy

#endif /* !REPY_BUILTIN_HXX */
