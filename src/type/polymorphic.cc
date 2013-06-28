#include <type/polymorphic.hh>

namespace type
{
    Polymorphic& Polymorphic::instance()
    {
        static Polymorphic p;

        return p;
    }

    bool Polymorphic::compatible_with(const Type& t)
    {
        return true;
    }

    std::ostream& Polymorphic::dump(std::ostream& o) const
    {
        o << "***";

        return o;
    }
} // namespace type
