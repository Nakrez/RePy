#include <ast/stmt.hh>

namespace ast
{
    Stmt::Stmt(const yy::location& location)
        : Ast(location)
    {}

    Stmt::~Stmt()
    {}
} // ast
