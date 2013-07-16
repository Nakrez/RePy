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

    std::string Int::cpp_type() const
    {
        return "__repy_int*";
    }
} // namespace type
