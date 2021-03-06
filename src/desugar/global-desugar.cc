#include <desugar/global-desugar.hh>
#include <ast/all.hh>

namespace desugar
{
    GlobalDesugar::GlobalDesugar()
        : global_space_(false)
        , init_fun_(nullptr)
        , init_body_(nullptr)
    {}

    GlobalDesugar::~GlobalDesugar()
    {}

    void GlobalDesugar::operator()(ast::ModuleStmt& ast)
    {
        type::Function* init_type = new type::Function();

        init_body_ = new ast::StmtList(yy::location());

        init_fun_ = new ast::FunctionDec(yy::location(), "__init", nullptr,
                                         init_body_);

        init_type->return_type_set(&type::Void::instance());
        init_fun_->to_generate_add(init_type);


        global_space_ = true;
        ast::AstList* content = clone(ast.content_get());
        global_space_ = false;

        ast::ModuleStmt* s = new ast::ModuleStmt(ast.location_get(),
                                                 ast.name_get(), content);

        s->content_get()->push_back(init_fun_);

        cloned_ast_ = s;
    }

    void GlobalDesugar::operator()(ast::IfStmt& ast)
    {
        global_treatment(ast);
    }

    void GlobalDesugar::operator()(ast::WhileStmt& ast)
    {
        global_treatment(ast);
    }

    void GlobalDesugar::operator()(ast::ExprStmt& ast)
    {
        global_treatment(ast);
    }

    void GlobalDesugar::operator()(ast::ReturnStmt& ast)
    {
        global_treatment(ast);
    }

    void GlobalDesugar::operator()(ast::FunctionDec& ast)
    {
        bool temp = global_space_;

        global_space_ = false;
        cloner::AstCloner::operator()(ast);
        global_space_ = temp;
    }

    void GlobalDesugar::operator()(ast::IdVar& ast)
    {
        if (!ast.def_get() && global_space_)
            ast.global_set(true);

        cloner::AstCloner::operator()(ast);
    }
} // namespace desugar
