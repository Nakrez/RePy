#ifndef CLONER_AST_CLONER_HH
# define CLONER_AST_CLONER_HH

# include <cassert>

# include <misc/error.hh>

# include <ast/default-visitor.hh>

namespace cloner
{
    class AstCloner : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            AstCloner();
            virtual ~AstCloner();

            ast::Ast* cloned_ast_get();

            template <typename T>
            T* clone(T* t);

            template <typename T>
            T* clone(T& t);

            template <typename T>
            ast::AnyList<T>* clone_list(ast::AnyList<T>& l);

            virtual void operator()(ast::AstList& ast);
            virtual void operator()(ast::StmtList& ast);
            virtual void operator()(ast::ExprList& ast);

            virtual void operator()(ast::PassStmt& ast);
            virtual void operator()(ast::BreakStmt& ast);
            virtual void operator()(ast::ContinueStmt& ast);
            virtual void operator()(ast::ExprStmt& ast);
            virtual void operator()(ast::IfStmt& ast);
            virtual void operator()(ast::WhileStmt& ast);
            virtual void operator()(ast::ReturnStmt& ast);
            virtual void operator()(ast::FunctionDec& ast);
            virtual void operator()(ast::ModuleStmt& ast);

            virtual void operator()(ast::OpExpr& ast);
            virtual void operator()(ast::UnaryExpr& ast);
            virtual void operator()(ast::AssignExpr& ast);
            virtual void operator()(ast::NumeralExpr& ast);
            virtual void operator()(ast::StringExpr& ast);
            virtual void operator()(ast::YieldExpr& ast);
            virtual void operator()(ast::StarExpr& ast);
            virtual void operator()(ast::DoubleStarExpr& ast);

            virtual void operator()(ast::IdVar& ast);
            virtual void operator()(ast::FunctionVar& ast);
            virtual void operator()(ast::FieldVar& ast);
            virtual void operator()(ast::MethodVar& ast);

        protected:
            ast::Ast* cloned_ast_;
    };
} // namespace cloner

# include <cloner/ast-cloner.hxx>

#endif /* !CLONER_AST_CLONER_HH */
