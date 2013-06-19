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

        o_ << misc::iendl;
    }

    void PrettyPrinter::operator()(const StmtList& ast)
    {
        auto beg = ast.list_get().begin();
        auto end = ast.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                o_ << " ; ";

            (*it)->accept(*this);
        }

        o_ << misc::iendl;
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

    void PrettyPrinter::operator()(const IfStmt& ast)
    {
        o_ << "if ";

        ast.cond_get()->accept(*this);

        o_ << ":" << misc::indentendl;

        ast.true_stmt_get()->accept(*this);

        o_ << misc::dedentendl;

        if (ast.else_stmt_get())
        {
            if (dynamic_cast<const ast::IfStmt*> (ast.else_stmt_get()))
                o_ << "el";
            else
                o_ << "else:" << misc::indentendl;

            ast.else_stmt_get()->accept(*this);
            o_ << misc::dedent;
        }
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
