#include <desugar/tasks.hh>

namespace desugar
{
    void dec_generator()
    {
        assert(ast::program_ast && "No ast to desugar (dec generator)");

        DeclarationGenerator desugar;
        desugar.visit(ast::program_ast);
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
