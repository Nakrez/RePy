#ifndef DESUGAR_FUNCTION_DEC_DESUGAR_HH
# define DESUGAR_FUNCTION_DEC_DESUGAR_HH

# include <cloner/ast-cloner.hh>

namespace desugar
{
    class FunctionDecDesugar : public cloner::AstCloner
    {
        public:
            using cloner::AstCloner::operator();

            FunctionDecDesugar();
            virtual ~FunctionDecDesugar();

            void operator()(ast::FunctionDec& ast);
    };
} // namespace desugar

#endif /* !DESUGAR_FUNCTION_DEC_DESUGAR_HH */
