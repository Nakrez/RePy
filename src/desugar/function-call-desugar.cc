#include <desugar/function-call-desugar.hh>
#include <ast/all.hh>

namespace desugar
{
    FunctionCallDesugar::FunctionCallDesugar()
    {}

    FunctionCallDesugar::~FunctionCallDesugar()
    {}

    void FunctionCallDesugar::operator()(ast::FunctionVar& ast)
    {
        ast::Var* var = clone(ast.var_get());
        ast::ExprList* params = nullptr;

        if (ast.params_get())
            params = clone_list(*ast.params_get());

        ast::FunctionVar* v = new ast::FunctionVar(ast.location_get(), var,
                                                   params);

        v->type_set(ast.type_get());

        cloned_ast_ = v;
    }
} // namespace desugar
