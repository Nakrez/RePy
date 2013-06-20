#include <ast/var.hh>

namespace ast
{
    Var::Var(const yy::location& location)
        : Expr(location)
    {}

    Var::~Var()
    {}
} // namespace ast
