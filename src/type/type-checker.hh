#ifndef TYPE_TYPE_CHECKER_HH
# define TYPE_TYPE_CHECKER_HH

# include <cassert>
# include <stack>

# include <misc/error.hh>

# include <ast/default-visitor.hh>

# include <type/void.hh>
# include <type/int.hh>
# include <type/string.hh>
# include <type/function.hh>
# include <type/polymorphic.hh>

namespace type
{
    class TypeChecker : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            TypeChecker();
            virtual ~TypeChecker();

            misc::Error& error_get();

            void type_check(ast::Expr* e1, ast::Expr* e2);
            void type_set(ast::Expr* e1, ast::Expr* e2);

            void operator()(ast::ReturnStmt& ast);
            void operator()(ast::FunctionDec& ast);
            void operator()(ast::FunctionVar& ast);
            void operator()(ast::AssignExpr& ast);
            void operator()(ast::OpExpr& ast);
            void operator()(ast::IdVar& ast);
            void operator()(ast::StringExpr& ast);
            void operator()(ast::NumeralExpr& ast);

        private:
            misc::Error error_;
            std::stack<ast::FunctionDec*> in_declaration_;
    };
} // namespace type

#endif /* !TYPE_TYPE_CHECKER_HH */
