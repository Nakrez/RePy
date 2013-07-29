#include <ast/all.hh>

namespace ast
{
    FunctionDec::FunctionDec(const yy::location& location,
                             const std::string& name,
                             ExprList* args,
                             Stmt* body)
        : Stmt(location)
        , name_(name)
        , final_args_(nullptr)
        , original_args_(args)
        , body_(body)
        , type_(nullptr)
    {}

    FunctionDec::~FunctionDec()
    {
        delete final_args_;
        delete original_args_;
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
        return final_args_;
    }

    ExprList* FunctionDec::args_get()
    {
        return final_args_;
    }

    const ExprList* FunctionDec::original_args_get() const
    {
        return original_args_;
    }

    ExprList* FunctionDec::original_args_get()
    {
        return original_args_;
    }

    void FunctionDec::args_set(ExprList* args)
    {
        final_args_ = args;
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
            if (final_args_ && t->args_get().size())
            {
                auto it = t->args_get().begin();

                for (auto params : final_args_->list_get())
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

    void FunctionDec::delete_self()
    {
        auto self = dynamic_cast<ast::IdVar*> (final_args_->list_get().front());

        if (self && self->id_get() == "self")
        {
            final_args_->pop_front();
            original_args_->pop_front();

            if (final_args_->list_get().empty())
            {
                delete final_args_;
                final_args_ = nullptr;
            }

            if (original_args_->list_get().empty())
            {
                delete original_args_;
                original_args_ = nullptr;
            }
        }
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
