#ifndef DESUGAR_GLOBAL_DESUGAR_HXX
# define DESUGAR_GLOBAL_DESUGAR_HXX

# include <desugar/global-desugar.hh>

# include <ast/all.hh>

namespace desugar
{
    template <class T>
    void GlobalDesugar::global_treatment(T& ast)
    {
        bool temp = global_space_;

        global_space_ = false;
        cloner::AstCloner::operator()(ast);
        global_space_ = temp;

        if (global_space_)
        {
            init_body_->push_back(dynamic_cast<ast::Stmt*>(cloned_ast_));
            cloned_ast_ = nullptr;
        }
    }
} // namespace desugar

#endif /* !DEUGAR_GLOBAL_DESUGAR_HXX */
