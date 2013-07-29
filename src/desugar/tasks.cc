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

        delete old;

        bind::Binder b;
        b.visit(ast::program_ast);

        type::TypeChecker c;
        c.visit(ast::program_ast);
    }
} // namespace desugar
