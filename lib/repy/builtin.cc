#include <repy/builtin.hh>

namespace repy
{
    __repy_string* __builtin_input(__repy_string* str)
    {
        __repy_string* in = new __repy_string;

        std::cout << str << std::endl;

        std::cin >> *in;

        return in;
    }
} // namespace repy
