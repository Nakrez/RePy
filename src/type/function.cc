#include <type/function.hh>
#include <type/polymorphic.hh>

namespace type
{
    Function::Function()
        : return_type_(nullptr)
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

    bool Function::compatible_with(const Type& t)
    {
        // This function must be called from the definition of the function
        // to match a call prototype. Otherwise it wont work
        const Function* f = dynamic_cast<const Function*> (&t);

        if (!f)
            return false;

        auto it = args_type_.begin();

        for (auto arg : f->args_get())
        {
            if (!arg->compatible_with(**it))
                return false;

            ++it;
        }

        return true;
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

    std::string Function::cpp_type() const
    {
        assert(false && "Internal compiler error: no C++ function type");

        return "";
    }
} // namespace type
