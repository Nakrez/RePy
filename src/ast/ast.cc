#include <ast/ast.hh>

namespace ast
{
    Ast::Ast(const yy::location& location)
        : loc_(location)
    {}

    Ast::~Ast()
    {}
} // namespace ast
