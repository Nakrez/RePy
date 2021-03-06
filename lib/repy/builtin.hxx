#ifndef REPY_BUILTIN_HXX
# define REPY_BUILTIN_HXX

# include <repy/builtin.hh>

namespace repy
{
    template<class T>
    T& deref(T& t)
    {
        return t;
    }

    template<class T>
    T& deref(T* t)
    {
        return *t;
    }

    template<int N>
    struct __internal_print
    {
        template<typename T>
        static void call(T& a, int size)
        {
            __internal_print<N - 1>::call(a, size);
            std::cout << deref(std::get<N>(a));

            if (N != size)
                std::cout << " ";
        }
    };

    template<>
    struct __internal_print<0>
    {
        template<typename T>
        static void call(T& a, int size)
        {
            std::cout << deref(std::get<0>(a));
            if (size != 0)
                std::cout << " ";
        }
    };

    template<>
    struct __internal_print<-1>
    {
        template<typename T>
        static void call(T& a, int size)
        {}
    };

    template<typename... Args>
    void __builtin_print(Args... a)
    {
        std::tuple<Args...> args = std::make_tuple(a...);

        const int size = std::tuple_size<std::tuple<Args...>>::value - 1;

        __internal_print<size>::call(args, size);

        std::cout << std::endl;
    }
} // namespace repy

#endif /* !REPY_BUILTIN_HXX */
