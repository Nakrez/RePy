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
    }

    const std::list<type::Function*>& FunctionDec::to_generate_get() const
    {
        return to_generate_;
    }

    std::list<type::Function*>& FunctionDec::to_generate_get()
    {
        return to_generate_;
    }

    void FunctionDec::to_generate_add(type::Function* f)
    {
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
