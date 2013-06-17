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

        private:
            std::ostream& o_;
    };
} // namespace ast

#endif /* !AST_PRETTY_PRINTER_HH */
