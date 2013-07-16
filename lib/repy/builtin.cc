#include <repy/builtin.hh>

namespace repy
{
    template<typename... Args>
    void __builtin_print(Args... a)
    {
        std::tuple<Args...> args = {a...};

        auto beg = args.begin();
        auto end = args.end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                std::cout << " ";

            std::cout << *it;
        }

        std::cout << std::endl;
    }
} // namespace repy
