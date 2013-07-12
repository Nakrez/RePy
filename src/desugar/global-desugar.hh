// The goal of this desugar visitor is to extract all the global components
// and put it in an __init function that will be called on every namespace
// later. Futhermore it will also flaged variables that are global. Then, later
// we will be able to declared them as global in the namespace module
#ifndef DESUGAR_GLOBAL_DESUGAR_HH
# define DESUGAR_GLOBAL_DESUGAR_HH

# include <cloner/ast-cloner.hh>

namespace desugar
{
    class GlobalDesugar : public cloner::AstCloner
    {
        public:
            using cloner::AstCloner::operator();

            GlobalDesugar();
            virtual ~GlobalDesugar();

            virtual void operator()(ast::ModuleStmt& ast);

        protected:
            bool global_space_;
            ast::FunctionDec* init_fun_;
            ast::StmtList* init_body_;
    };
} // namespace desugar

#endif /* !DESUGAR_GLOBAL_DESUGAR_HH */
