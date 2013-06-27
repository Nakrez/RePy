#include <ast/typed.hh>

namespace ast
{
    Typed::Typed()
        : type_(nullptr)
    {}

    Typed::~Typed()
    {}

    const type::Type* Typed::type_get() const
    {
        return type_;
    }

    type::Type* Typed::type_get()
    {
        return type_;
    }

    void Typed::type_set(type::Type* type)
    {
        type_ = type;
    }
} // namespace ast
