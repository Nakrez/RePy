#ifndef BIND_BINDER_HH
# define BIND_BINDER_HH

# include <string>
# include <stack>

# include <misc/error.hh>
# include <misc/scoped-map.hh>

# include <ast/default-visitor.hh>
# include <ast/all.hh>

namespace bind
{
    class Binder : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();
            // Imported operators :
            // void operator()(ExprStmt& ast);
            // void operator()(NumeralExpr& ast);
            // void operator()(StringExpr& ast);
            // void operator()(PassStmt& ast);
            // void operator()(AstList& ast);
            // void operator()(StmtList& ast);
            // void operator()(ExprList& ast);
            // void operator()(IfStmt& ast);
            // void operator()(ReturnStmt& ast);
            // void operator()(OpExpr& ast);
            // void operator()(UnaryExpr& ast);
            // void operator()(YieldExpr& ast);
            // void operator()(ast::FunctionVar& ast);

            Binder();
            virtual ~Binder();

            misc::Error& error_get();

            void operator()(ast::WhileStmt& ast);
            void operator()(ast::BreakStmt& ast);
            void operator()(ast::ContinueStmt& ast);

            void operator()(ast::FunctionDec& ast);

            void operator()(ast::AssignExpr& ast);
            void operator()(ast::IdVar& ast);

        private:
            misc::ScopedMap<std::string, ast::Stmt*> scope_map_;
            std::stack<ast::Stmt*> loop_stack_;
            misc::Error error_;
    };
} // namespace bind

#endif /* !BIND_BINDER_HH */