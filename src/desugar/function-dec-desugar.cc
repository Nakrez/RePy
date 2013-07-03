#include <desugar/function-dec-desugar.hh>
#include <ast/all.hh>

namespace desugar
{
    FunctionDecDesugar::FunctionDecDesugar()
    {}

    FunctionDecDesugar::~FunctionDecDesugar()
    {}

    void FunctionDecDesugar::operator()(ast::FunctionDec& ast)
    {
        ast::ExprList* args = nullptr;
        ast::Stmt* body = clone(ast.body_get());

        if (ast.args_get())
        {
            args = new ast::ExprList(ast.args_get()->location_get());

            for (auto arg : ast.args_get()->list_get())
            {
                ast::AssignExpr* e = dynamic_cast<ast::AssignExpr*> (arg);

                if (e)
                    args->push_back(clone(e->lvalue_get()));
                else
                    args->push_back(clone(arg));
            }
        }

        ast::FunctionDec* f = new ast::FunctionDec(ast.location_get(),
                                                   ast.name_get(), args, body);

        f->type_set(ast.type_get());
        f->to_generate_set(ast.to_generate_get());

        cloned_ast_ = f;
    }
} // namespace desugar
