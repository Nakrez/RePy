#include <type/tuple.hh>

namespace type
{
    Tuple& Tuple::instance()
    {
        static Tuple t;

        return t;
    }

    std::ostream& Tuple::dump(std::ostream& o) const
    {
        o << "Tuple";

        return o;
    }

    std::string Tuple::cpp_type() const
    {
        return "__repy_tuple*";
    }
} // namespace type
