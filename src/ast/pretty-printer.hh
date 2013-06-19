#ifndef AST_PRETTY_PRINTER_HH
# define AST_PRETTY_PRINTER_HH

# include <iostream>

# include <misc/indent.hh>

# include <ast/default-visitor.hh>

namespace ast
{
    class PrettyPrinter : public DefaultConstVisitor
    {
        public:
            using DefaultConstVisitor::operator();
            // Imported operators :
            // void operator()(const ExprStmt& ast);

            PrettyPrinter(std::ostream& o);
            virtual ~PrettyPrinter();

            void operator()(const AstList& ast);
            void operator()(const StmtList& ast);

            void operator()(const PassStmt& ast);
            void operator()(const BreakStmt& ast);
            void operator()(const ContinueStmt& ast);
            void operator()(const IfStmt& ast);
            void operator()(const WhileStmt& ast);

            void operator()(const OpExpr& ast);
            void operator()(const UnaryExpr& ast);
            void operator()(const NumeralExpr& ast);
            void operator()(const StringExpr& ast);
        private:
            std::ostream& o_;
    };
} // namespace ast

#endif /* !AST_PRETTY_PRINTER_HH */
