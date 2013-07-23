#include <ast/field-var.hh>

namespace ast
{
    FieldVar::FieldVar(const yy::location& loc, Var* var,
                       const std::string name)
        : Var(loc)
        , var_(var)
        , name_(name)
    {}

    FieldVar::~FieldVar()
    {
        delete var_;
    }

    const std::string FieldVar::name_get() const
    {
        return name_;
    }

    std::string FieldVar::name_get()
    {
        return name_;
    }

    const Var* FieldVar::var_get() const
    {
        return var_;
    }

    Var* FieldVar::var_get()
    {
        return var_;
    }

    void FieldVar::add_component(Var* v)
    {
        if (var_ == nullptr)
        {
            var_ = v;
            return;
        }

        var_->add_component(v);
    }

    void FieldVar::accept(Visitor& v)
    {
        v(*this);
    }

    void FieldVar::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
