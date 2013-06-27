#include <type/type-checker.hh>
#include <ast/all.hh>

namespace type
{
    TypeChecker::TypeChecker()
    {}

    TypeChecker::~TypeChecker()
    {}

    misc::Error& TypeChecker::error_get()
    {
        return error_;
    }

    void TypeChecker::operator()(ast::FunctionDec&)
    {

    }

    void TypeChecker::operator()(ast::AssignExpr&)
    {

    }
} // namespace type
