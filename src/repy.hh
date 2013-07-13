#ifndef REPY_HH
# define REPY_HH

namespace repy
{
    extern char* input_name;
} // namespace repy

namespace ast
{
    class Ast;

    extern Ast* program_ast;
} // namespace ast

namespace bind
{
    extern bool print_bind;
} // namespace bind

namespace type
{
    extern bool print_type;
} // namespace type

#endif /* !TYPY_HH */
