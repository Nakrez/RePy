#include <type/polymorphic.hh>

namespace type
{
    Polymorphic& Polymorphic::instance()
    {
        static Polymorphic p;

        return p;
    }

    bool Polymorphic::compatible_with(const Type&)
    {
        return true;
    }

    std::ostream& Polymorphic::dump(std::ostream& o) const
    {
        o << "***";

        return o;
    }

    std::string Polymorphic::cpp_type() const
    {
        assert(false && "Polymorphic type can't be translated to C++");

        return "";
    }
} // namespace type
