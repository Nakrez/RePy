#ifndef TYPE_TYPE_CHECKER_HH
# define TYPE_TYPE_CHECKER_HH

# include <cassert>
# include <stack>
# include <map>

# include <misc/error.hh>

# include <ast/default-visitor.hh>
# include <ast/pretty-printer.hh>

# include <type/void.hh>
# include <type/int.hh>
# include <type/string.hh>
# include <type/function.hh>
# include <type/polymorphic.hh>

# include <builtin/builtin-library.hh>

# include <cloner/ast-cloner.hh>

namespace type
{
    class TypeChecker : public ast::DefaultVisitor
    {
        typedef std::pair<ast::Expr*, bool> parameter;

        public:
            using ast::DefaultVisitor::operator();

            TypeChecker();
            virtual ~TypeChecker();

            misc::Error& error_get();

            void type_check(ast::Expr* e1, ast::Expr* e2);
            void type_set(ast::Expr* e1, ast::Expr* e2);
            Type* type_call(ast::FunctionDec* d, Function* type);

            virtual void operator()(ast::ReturnStmt& ast);
            virtual void operator()(ast::FunctionDec& ast);
            virtual void operator()(ast::ClassDec& ast);
            virtual void operator()(ast::FunctionVar& ast);
            virtual void operator()(ast::AssignExpr& ast);
            virtual void operator()(ast::OpExpr& ast);
            virtual void operator()(ast::IdVar& ast);
            virtual void operator()(ast::FieldVar& ast);
            virtual void operator()(ast::StringExpr& ast);
            virtual void operator()(ast::NumeralExpr& ast);

        private:
            // Type callable expression (FunctionVar, MethodVar)
            template <class T>
            void type_callable(T& e);

            template <class T>
            ast::ExprList* generate_prototype(T& dec);

            const std::string& name_get(const ast::Expr* e);

            void build_mapping(const ast::ExprList* args,
                               std::map<std::string, parameter>& args_map,
                               std::vector<std::string>& order);

            void build_call(const ast::ExprList* args,
                            std::map<std::string, parameter>& args_map,
                            std::vector<std::string>& order);

            ast::ExprList*
            generate_list(const yy::location& loc,
                          std::map<std::string, parameter>& args_map,
                          std::vector<std::string>& order);

            ast::Expr* clone(ast::Ast* ast);

        private:
            misc::Error error_;
            type::Class* current_class_;
            std::stack<ast::FunctionDec*> in_declaration_;
            std::map<std::string, type::Class*> declared_class_;
    };
} // namespace type

# include <type/type-checker.hxx>

#endif /* !TYPE_TYPE_CHECKER_HH */
