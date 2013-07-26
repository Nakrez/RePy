#include <desugar/declaration-generator.hh>
#include <ast/all.hh>

namespace desugar
{
    DeclarationGenerator::DeclarationGenerator()
    {}

    DeclarationGenerator::~DeclarationGenerator()
    {}

    void DeclarationGenerator::operator()(ast::FunctionDec& ast)
    {
        ast::ExprList* final_args = nullptr;

        if (ast.original_args_get())
        {
            final_args = new ast::ExprList(ast.original_args_get()->location_get());

            for (auto arg : ast.original_args_get()->list_get())
            {
                ast::AssignExpr* e = dynamic_cast<ast::AssignExpr*> (arg);

                if (e)
                    final_args->push_back(clone_part(e->lvalue_get()));
                else
                    final_args->push_back(clone_part(arg));
            }
        }

        ast.args_set(final_args);
    }

    ast::Expr* DeclarationGenerator::clone_part(ast::Ast* ast)
    {
        ast::Expr* ret_expr = nullptr;

        ast->accept(cloner_);

        ret_expr = dynamic_cast<ast::Expr*> (cloner_.cloned_ast_get());

        assert(ret_expr && "Declaration generator error");

        return ret_expr;
    }
} // namespace desugar
