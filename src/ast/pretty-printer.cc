#include <ast/pretty-printer.hh>
#include <ast/all.hh>

namespace ast
{
    PrettyPrinter::PrettyPrinter(std::ostream& o)
        : o_(o)
    {}

    PrettyPrinter::~PrettyPrinter()
    {}
} // namespace ast
