#include <desugar/tasks.hh>

namespace desugar
{
    void fun_call_desugar()
    {
        assert(ast::program_ast && "No ast to desugar (function call)");

        FunctionDecDesugar desugar;
        desugar.visit(ast::program_ast);

        ast::Ast* old = ast::program_ast;

        ast::program_ast = desugar.cloned_ast_get();

        bind::Binder bind;
        bind.visit(ast::program_ast);

        delete old;
    }

    void fun_dec_desugar()
    {
        assert(ast::program_ast && "No ast to desugar (function dec)");

        FunctionDecDesugar desugar;
        desugar.visit(ast::program_ast);

        ast::Ast* old = ast::program_ast;

        ast::program_ast = desugar.cloned_ast_get();

        bind::Binder bind;
        bind.visit(ast::program_ast);

        delete old;
    }
} // namespace desugar
