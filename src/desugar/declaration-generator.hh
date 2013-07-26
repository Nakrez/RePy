#ifndef DESUGAR_DECLARATION_GENERATOR_HH
# define DESUGAR_DECLARATION_GENERATOR_HH

# include <ast/default-visitor.hh>
# include <ast/pretty-printer.hh>
# include <cloner/ast-cloner.hh>

namespace desugar
{
    class DeclarationGenerator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            DeclarationGenerator();
            virtual ~DeclarationGenerator();

            virtual void operator()(ast::FunctionDec& ast);

        private:
            ast::Expr* clone_part(ast::Ast* ast);

        private:
            cloner::AstCloner cloner_;
    };
} // namespace desugar

#endif /* !DESUGAR_DECLARATION_GENERATOR_HH */
