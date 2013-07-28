#include <type/class.hh>

namespace type
{
    Class::Class(const std::string& name)
        : name_(name)
    {}

    Class::~Class()
    {}

    const std::string& Class::name_get() const
    {
        return name_;
    }

    ast::Ast* Class::component_get(const std::string& name)
    {
        return content_[name];
    }

    bool Class::component_add(const std::string& name, ast::Ast* dec)
    {
        // Component already exists
        if (!content_[name])
            return false;

        content_[name] = dec;

        return true;
    }

    std::ostream& Class::dump(std::ostream& o) const
    {
        o << "Class (" << name_ << ")";

        return o;
    }

    std::string Class::cpp_type() const
    {
        return name_ + "*";
    }
} // namespace type
