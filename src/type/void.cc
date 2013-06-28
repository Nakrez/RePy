#include <type/void.hh>

namespace type
{
    Void& Void::instance()
    {
        static Void v;

        return v;
    }

    std::ostream& Void::dump(std::ostream& o) const
    {
        o << "void";

        return o;
    }
} // namespace type
