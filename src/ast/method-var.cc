#include <ast/method-var.hh>

namespace ast
{
    MethodVar::MethodVar(const yy::location& loc, FieldVar* field,
                         FunctionVar* call)
        : Var(loc)
        , field_(field)
        , call_(call)
    {}

    MethodVar::~MethodVar()
    {
        delete field_;
        delete call_;
    }

    const std::string& MethodVar::name_get() const
    {
        return field_->name_get();
    }

    std::string& MethodVar::name_get()
    {
        return field_->name_get();
    }

    const ExprList* MethodVar::params_get() const
    {
        return call_->params_get();
    }

    ExprList* MethodVar::params_get()
    {
        return call_->params_get();
    }


    const FunctionVar* MethodVar::call_get() const
    {
        return call_;
    }

    FunctionVar* MethodVar::call_get()
    {
        return call_;
    }

    const Var* MethodVar::var_get() const
    {
        return field_->var_get();
    }

    Var* MethodVar::var_get()
    {
        return field_->var_get();
    }

    void MethodVar::add_component(Var* v)
    {
        field_->add_component(v);
    }

    void MethodVar::accept(Visitor& v)
    {
        v(*this);
    }

    void MethodVar::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
