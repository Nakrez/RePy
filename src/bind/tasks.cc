#include <bind/tasks.hh>

namespace bind
{
    void compute_bind()
    {
        assert(ast::program_ast && "No ast to bind");

        Binder bind;
        bind.visit(ast::program_ast);

        bind.error_get().throw_if_needed();
    }
} // namespace bind
