#include <ast/all.hh>

namespace ast
{
    FunctionDec::FunctionDec(const yy::location& location,
                             const std::string& name,
                             ExprList* args,
                             Stmt* body)
        : Stmt(location)
        , name_(name)
        , args_(args)
        , body_(body)
        , type_(nullptr)
    {}

    FunctionDec::~FunctionDec()
    {
        delete args_;
        delete body_;
    }

    const std::string& FunctionDec::name_get() const
    {
        return name_;
    }

    std::string& FunctionDec::name_get()
    {
        return name_;
    }

    const ExprList* FunctionDec::args_get() const
    {
        return args_;
    }

    ExprList* FunctionDec::args_get()
    {
        return args_;
    }

    const Stmt* FunctionDec::body_get() const
    {
        return body_;
    }

    Stmt* FunctionDec::body_get()
    {
        return body_;
    }

    const type::Function* FunctionDec::type_get() const
    {
        return type_;
    }

    type::Function* FunctionDec::type_get()
    {
        return type_;
    }

    void FunctionDec::type_set(type::Function* t)
    {
        type_ = t;

        if (t)
        {
            if (args_ && t->args_get().size())
            {
                auto it = t->args_get().begin();

                for (auto params : args_->list_get())
                {
                    params->type_set(*it);
                    ++it;
                }
            }
        }
    }

    const std::list<type::Function*>& FunctionDec::to_generate_get() const
    {
        return to_generate_;
    }

    std::list<type::Function*>& FunctionDec::to_generate_get()
    {
        return to_generate_;
    }

    void FunctionDec::to_generate_set(const std::list<type::Function*>& l)
    {
        to_generate_ = l;
    }

    void FunctionDec::to_generate_add(type::Function* f)
    {
        // Don't accept polymorphic generation
        if (f->return_type_get() == &type::Polymorphic::instance())
            return;

        for (auto arg : f->args_get())
            if (arg == &type::Polymorphic::instance())
                return;

        to_generate_.push_back(f);
    }

    void FunctionDec::accept(Visitor& v)
    {
        v(*this);
    }

    void FunctionDec::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
