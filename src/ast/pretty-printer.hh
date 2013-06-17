#ifndef AST_PRETTY_PRINTER_HH
# define AST_PRETTY_PRINTER_HH

# include <iostream>

# include <ast/default-visitor.hh>

namespace ast
{
    class PrettyPrinter : public DefaultConstVisitor
    {
        public:
            using DefaultConstVisitor::operator();

            PrettyPrinter(std::ostream& o);
            virtual ~PrettyPrinter();

            void operator()(const AstList& ast);
            void operator()(const StmtList& ast);

            void operator()(const PassStmt& ast);
            void operator()(const BreakStmt& ast);
        private:
            std::ostream& o_;
    };
} // namespace ast

#endif /* !AST_PRETTY_PRINTER_HH */
