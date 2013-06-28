#include <type/int.hh>

namespace type
{
    Type& Int::instance()
    {
        static Int i;

        return i;
    }

    std::ostream& Int::dump(std::ostream& o) const
    {
        o << "int";

        return o;
    }
} // namespace type
