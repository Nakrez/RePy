#include <desugar/global-desugar.hh>
#include <ast/all.hh>

namespace desugar
{
    GlobalDesugar::GlobalDesugar()
        : global_space_(true)
        , init_fun_(nullptr)
        , init_body_(nullptr)
    {}

    GlobalDesugar::~GlobalDesugar()
    {}

    void GlobalDesugar::operator()(ast::ModuleStmt& ast)
    {
        init_body_ = new ast::StmtList(yy::location());

        init_fun_ = new ast::FunctionDec(yy::location(), "__init", nullptr,
                                         init_body_);

        ast::AstList* content = clone(ast.content_get());

        ast::ModuleStmt* s = new ast::ModuleStmt(ast.location_get(),
                                                 ast.name_get(), content);

        s->content_get()->push_back(init_fun_);

        cloned_ast_ = s;
    }
} // namespace desugar
