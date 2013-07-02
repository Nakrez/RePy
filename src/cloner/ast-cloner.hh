#ifndef CLONER_AST_CLONER_HH
# define CLONER_AST_CLONER_HH

# include <cassert>

# include <misc/error.hh>

# include <ast/default-visitor.hh>

namespace cloner
{
    class AstCloner : public ast::DefaultConstVisitor
    {
        public:
            using ast::DefaultConstVisitor::operator();

            AstCloner();
            virtual ~AstCloner();

            ast::Ast* cloned_ast_get();

            template <typename T>
            T* clone(const T* const t);

            template <typename T>
            T* clone(const T& t);

            template <typename T>
            ast::AnyList<T>* clone_list(const ast::AnyList<T>& l);

            virtual void operator()(const ast::AstList& ast);
            virtual void operator()(const ast::StmtList& ast);
            virtual void operator()(const ast::ExprList& ast);

            virtual void operator()(const ast::PassStmt& ast);
            virtual void operator()(const ast::BreakStmt& ast);
            virtual void operator()(const ast::ContinueStmt& ast);
            virtual void operator()(const ast::ExprStmt& ast);
            virtual void operator()(const ast::IfStmt& ast);
            virtual void operator()(const ast::WhileStmt& ast);
            virtual void operator()(const ast::ReturnStmt& ast);
            virtual void operator()(const ast::FunctionDec& ast);

            virtual void operator()(const ast::OpExpr& ast);
            virtual void operator()(const ast::UnaryExpr& ast);
            virtual void operator()(const ast::AssignExpr& ast);
            virtual void operator()(const ast::NumeralExpr& ast);
            virtual void operator()(const ast::StringExpr& ast);
            virtual void operator()(const ast::YieldExpr& ast);
            virtual void operator()(const ast::StarExpr& ast);
            virtual void operator()(const ast::DoubleStarExpr& ast);

            virtual void operator()(const ast::IdVar& ast);
            virtual void operator()(const ast::FunctionVar& ast);

        protected:
            ast::Ast* cloned_ast_;
    };
} // namespace cloner

# include <cloner/ast-cloner.hxx>

#endif /* !CLONER_AST_CLONER_HH */
