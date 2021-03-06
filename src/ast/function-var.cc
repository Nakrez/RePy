#include <ast/function-var.hh>
#include <ast/any-list.hh>

namespace ast
{
    FunctionVar::FunctionVar(const yy::location& location,
                             Var* var,
                             ExprList* params)
        : Var(location)
        , var_(var)
        , params_(params)
        , def_(nullptr)
        , constructor_(false)
    {}

    FunctionVar::~FunctionVar()
    {
        delete var_;
        delete params_;
    }

    const Var* FunctionVar::var_get() const
    {
        return var_;
    }

    Var* FunctionVar::var_get()
    {
        return var_;
    }

    const ExprList* FunctionVar::params_get() const
    {
        return params_;
    }

    ExprList* FunctionVar::params_get()
    {
        return params_;
    }

    const FunctionDec* FunctionVar::def_get() const
    {
        return def_;
    }

    FunctionDec* FunctionVar::def_get()
    {
        return def_;
    }

    bool FunctionVar::constructor_get() const
    {
        return constructor_;
    }

    void FunctionVar::constructor_set(bool c)
    {
        constructor_ = c;
    }

    void FunctionVar::def_set(FunctionDec* d)
    {
        def_ = d;
    }

    void FunctionVar::params_set(ExprList* p)
    {
        params_ = p;
    }

    void FunctionVar::add_component(Var* v)
    {
        if (var_ == nullptr)
        {
            var_ = v;
            return;
        }

        var_->add_component(v);
    }

    void FunctionVar::accept(Visitor& v)
    {
        v(*this);
    }

    void FunctionVar::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
