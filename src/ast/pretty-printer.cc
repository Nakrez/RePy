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

    void PrettyPrinter::operator()(const BreakStmt&)
    {
        o_ << "break";
    }

    void PrettyPrinter::operator()(const ContinueStmt&)
    {
        o_ << "continue";
    }

    void PrettyPrinter::operator()(const OpExpr& e)
    {
        e.left_expr_get()->accept(*this);
        o_ << " " << e.op_to_string() << " ";
        e.right_expr_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const UnaryExpr& e)
    {
        o_ << e.op_to_string() << " ";
        e.expr_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const NumeralExpr& e)
    {
        o_ << e.value_get();
    }

    void PrettyPrinter::operator()(const StringExpr& e)
    {
        o_ << "\"" << e.str_get() << "\"";
    }
} // namespace ast
