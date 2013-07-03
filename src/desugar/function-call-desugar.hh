#ifndef DESUGAR_FUNCTION_CALL_DESUGAR_HH
# define DESUGAR_FUNCTION_CALL_DESUGAR_HH

# include <map>

# include <misc/error.hh>

# include <cloner/ast-cloner.hh>

namespace desugar
{
    class FunctionCallDesugar : public cloner::AstCloner
    {
        typedef std::pair<ast::Expr*, bool> parameter;

        public:
            using cloner::AstCloner::operator();

            FunctionCallDesugar();
            virtual ~FunctionCallDesugar();

            misc::Error& error_get();

            void operator()(ast::FunctionVar& ast);

        protected:
            misc::Error error_;

        private:
            void build_mapping(const ast::ExprList* args,
                               std::map<std::string, parameter>& args_map,
                               std::vector<std::string>& order);

            void build_call(const ast::ExprList* args,
                            std::map<std::string, parameter>& args_map,
                            std::vector<std::string>& order);

            ast::ExprList*
            generate_call(const yy::location& loc,
                          std::map<std::string, parameter>& args_map,
                          std::vector<std::string>& order);

            const std::string& name_get(const ast::Expr* e);
    };
} // namespace desugar

#endif /* !DESUGAR_FUNCTION_CALL_DESUGAR_HH */
