#include <type/function.hh>

namespace type
{
    Function::Function()
        : return_type_()
    {}

    Function::~Function()
    {}

    const Type* Function::return_type_get() const
    {
        return return_type_;
    }

    Type* Function::return_type_get()
    {
        return return_type_;
    }

    const std::list<Type*>& Function::args_get() const
    {
        return args_type_;
    }

    std::list<Type*>& Function::args_get()
    {
        return args_type_;
    }

    void Function::return_type_set(Type* t)
    {
        return_type_ = t;
    }

    void Function::args_type_add(Type* t)
    {
        args_type_.push_back(t);
    }

    std::ostream& Function::dump(std::ostream& o) const
    {
        o << "(";

        auto beg = args_type_.begin();
        auto end = args_type_.end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                o << ", ";

            (*it)->dump(o);
        }

        o << ") -> ";

        return_type_->dump(o);

        return o;
    }
} // namespace type
