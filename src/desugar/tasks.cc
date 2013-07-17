#include <desugar/tasks.hh>

namespace desugar
{
    void fun_call_desugar()
    {
        // Compute binding after this desugar is not needed since we are going
        // to execute function dec desugar after it. It does not need
        // binding computed

        assert(ast::program_ast && "No ast to desugar (function call)");

        FunctionCallDesugar desugar;
        desugar.visit(ast::program_ast);

        desugar.error_get().throw_if_needed();

        ast::Ast* old = ast::program_ast;

        ast::program_ast = desugar.cloned_ast_get();

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

    void global_desugar()
    {
        assert(ast::program_ast && "No ast to desugar (global)");

        GlobalDesugar desugar;
        desugar.visit(ast::program_ast);

        ast::Ast* old = ast::program_ast;

        ast::program_ast = desugar.cloned_ast_get();

        bind::Binder bind;
        bind.visit(ast::program_ast);

        delete old;
    }
} // namespace desugar
