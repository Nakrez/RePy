#include <type/type.hh>

namespace type
{
    Type::Type()
    {}

    Type::~Type()
    {}

    std::ostream& operator<<(std::ostream& o, const type::Type& type)
    {
        type.dump(o);

        return o;
    }
} // namespace type
