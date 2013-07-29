#include <type/type.hh>
#include <type/polymorphic.hh>

namespace type
{
    Type::Type()
    {}

    Type::~Type()
    {}

    bool Type::compatible_with(const Type& t)
    {
        if (&t == &Polymorphic::instance())
            return true;

        return this == &t;
    }

    std::ostream& operator<<(std::ostream& o, const type::Type& type)
    {
        type.dump(o);

        return o;
    }

    std::string Type::cpp_type() const
    {
        return "lol";
    }
} // namespace type
