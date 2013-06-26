#ifndef TYPY_HH
# define TYPY_HH

namespace typy
{
    extern char* input_name;
} // namespace typy

namespace ast
{
    class Ast;

    extern Ast* program_ast;
} // namespace ast

namespace bind
{
    extern bool print_bind;
} // namespace bind

#endif /* !TYPY_HH */
