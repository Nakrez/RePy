#include <type/int.hh>

namespace type
{
    Type& Int::instance()
    {
        static Int i;

        return i;
    }

    bool Int::compatible_with(const Type& t)
    {
        return this == &t;
    }

    std::ostream& Int::dump(std::ostream& o)
    {
        o << "int";

        return o;
    }
} // namespace type
