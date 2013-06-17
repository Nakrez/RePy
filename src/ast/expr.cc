#include <ast/expr.hh>

namespace ast
{
    Expr::Expr(const yy::location& location)
        : Ast(location)
    {}

    Expr::~Expr()
    {}
} // namespace ast
