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

    void FunctionDec::accept(Visitor& v)
    {
        v(*this);
    }

    void FunctionDec::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
