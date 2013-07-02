#include <desugar/tasks.hh>

namespace desugar
{
    void fun_call_desugar()
    {
        assert(ast::program_ast && "No ast to desugar (function call)");
    }
} // namespace desugar
