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

    ast::Stmt* Class::component_get(const std::string& name)
    {
        return content_.at(name);
    }

    bool Class::component_add(const std::string& name, ast::Stmt* dec)
    {
        // Component already exists
        if (!content_.at(name))
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
