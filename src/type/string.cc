#include <type/string.hh>

namespace type
{
    String& String::instance()
    {
        static String s;

        return s;
    }

    bool String::compatible_with(const Type& t)
    {
        return this == &t;
    }

    std::ostream& String::dump(std::ostream& o) const
    {
        o << "String";

        return o;
    }
} // namespace type
