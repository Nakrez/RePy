#include <ast/pretty-printer.hh>
#include <ast/all.hh>

namespace ast
{
    PrettyPrinter::PrettyPrinter(std::ostream& o)
        : o_(o)
    {}

    PrettyPrinter::~PrettyPrinter()
    {}

    void PrettyPrinter::operator()(const AstList& ast)
    {
        for (auto e : ast.list_get())
        {
            e->accept(*this);
        }

        o_ << std::endl;
    }

    void PrettyPrinter::operator()(const StmtList& ast)
    {
        for (auto e : ast.list_get())
        {
            e->accept(*this);
            o_ << " ; ";
        }

        o_ << std::endl;
    }

    void PrettyPrinter::operator()(const PassStmt&)
    {
        o_ << "pass";
    }
} // namespace ast
