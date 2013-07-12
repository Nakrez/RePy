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
            // Imported operators

            // void operator()(ast::PassStmt& ast);
            // void operator()(ast::BreakStmt& ast);
            // void operator()(ast::ContinueStmt& ast);

            // void operator()(ast::YieldExpr& ast);
            // void operator()(ast::StarExpr& ast);
            // void operator()(ast::DoubleStarExpr& ast);



            GlobalDesugar();
            virtual ~GlobalDesugar();

            virtual void operator()(ast::IfStmt& ast);
            virtual void operator()(ast::WhileStmt& ast);
            virtual void operator()(ast::ExprStmt& ast);
            virtual void operator()(ast::ReturnStmt& ast);
            virtual void operator()(ast::FunctionDec& ast);
            virtual void operator()(ast::ModuleStmt& ast);

        protected:
            template <class T>
            void global_treatment(T& ast);

        protected:
            bool global_space_;
            ast::FunctionDec* init_fun_;
            ast::StmtList* init_body_;
    };
} // namespace desugar

# include <desugar/global-desugar.hxx>

#endif /* !DESUGAR_GLOBAL_DESUGAR_HH */
