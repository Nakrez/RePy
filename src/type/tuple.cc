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
} // namespace type
