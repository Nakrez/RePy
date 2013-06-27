#include <type/tasks.hh>

namespace type
{
    void type_check()
    {
        assert(ast::program_ast && "No ast to type check");

        TypeChecker type_check;
        type_check.visit(ast::program_ast);

        type_check.error_get().throw_if_needed();
    }
} // namespace type
