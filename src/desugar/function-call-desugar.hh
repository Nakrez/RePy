#ifndef DESUGAR_FUNCTION_CALL_DESUGAR_HH
# define DESUGAR_FUNCTION_CALL_DESUGAR_HH

# include <cloner/ast-cloner.hh>

namespace desugar
{
    class FunctionCallDesugar : public cloner::AstCloner
    {
        public:
            using cloner::AstCloner::operator();

            FunctionCallDesugar();
            virtual ~FunctionCallDesugar();

            void operator()(ast::FunctionVar& ast);
    };
} // namespace desugar

#endif /* !DESUGAR_FUNCTION_CALL_DESUGAR_HH */
