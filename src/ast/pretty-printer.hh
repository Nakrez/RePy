#ifndef AST_PRETTY_PRINTER_HH
# define AST_PRETTY_PRINTER_HH

# include <iostream>
# include <sstream>

# include <typy.hh>

# include <misc/indent.hh>
# include <misc/mutable-ref.hh>

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
            void operator()(const ExprList& ast);

            void operator()(const PassStmt& ast);
            void operator()(const BreakStmt& ast);
            void operator()(const ContinueStmt& ast);
            void operator()(const IfStmt& ast);
            void operator()(const WhileStmt& ast);
            void operator()(const ReturnStmt& ast);
            void operator()(const FunctionDec& ast);

            void operator()(const OpExpr& ast);
            void operator()(const UnaryExpr& ast);
            void operator()(const AssignExpr& ast);
            void operator()(const NumeralExpr& ast);
            void operator()(const StringExpr& ast);
            void operator()(const YieldExpr& ast);

            void operator()(const IdVar& ast);
            void operator()(const FunctionVar& ast);

        private:
            misc::MutableRef<std::ostream> o_;
            std::stringstream bind_;
    };
} // namespace ast

#endif /* !AST_PRETTY_PRINTER_HH */
