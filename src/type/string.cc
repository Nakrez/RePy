#include <type/string.hh>

namespace type
{
    String& String::instance()
    {
        static String s;

        return s;
    }

    std::ostream& String::dump(std::ostream& o) const
    {
        o << "String";

        return o;
    }

    std::string String::cpp_type() const
    {
        return "__repy_string*";
    }
} // namespace type
