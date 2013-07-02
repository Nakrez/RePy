#include <cloner/tasks.hh>

namespace cloner
{
    void clone_ast()
    {
        assert(ast::program_ast && "No ast to clone");

        AstCloner cloner;
        cloner.visit(ast::program_ast);

        ast::Ast* old = ast::program_ast;

        ast::program_ast = cloner.cloned_ast_get();

        delete old;
    }
} // namespace cloner
