#include <ast/pretty-printer.hh>
#include <ast/all.hh>
#include <cassert>

namespace ast
{
    PrettyPrinter::PrettyPrinter(std::ostream& o)
        : o_(o)
        , running_(nullptr)
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
                o_ << misc::iendl;

            (*it)->accept(*this);
        }

        o_ << misc::iendl;
    }

    void PrettyPrinter::operator()(const ExprList& e)
    {
        auto beg = e.list_get().begin();
        auto end = e.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                o_ << ",";

            (*it)->accept(*this);
        }
    }

    void PrettyPrinter::operator()(const PassStmt&)
    {
        o_ << "pass";
    }

    void PrettyPrinter::operator()(const BreakStmt& s)
    {
        o_ << "break";

        if (bind::print_bind)
            o_ << " \"\"\"" << s.in_loop_get() << "\"\"\" ";
    }

    void PrettyPrinter::operator()(const ContinueStmt& s)
    {
        o_ << "continue";

        if (bind::print_bind)
            o_ << " \"\"\"" << s.in_loop_get() << "\"\"\" ";
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

    void PrettyPrinter::operator()(const WhileStmt& s)
    {
        o_ << "while ";

        if (bind::print_bind)
            o_ << "\"\"\"" << &s << "\"\"\" ";

        s.cond_get()->accept(*this);

        o_ << ":" << misc::indentendl;

        s.loop_get()->accept(*this);

        o_ << misc::dedentendl;
    }

    void PrettyPrinter::operator()(const ReturnStmt& s)
    {
        o_ << "return ";
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const YieldExpr& s)
    {
        o_ << "yield ";
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const FunctionDec& d)
    {
        o_ << "def " << d.name_get();

        if (bind::print_bind)
            o_ << " \"\"\"" << &d << "\"\"\" ";

        o_ << "(";

        if (d.args_get())
        {
            auto beg = d.args_get()->list_get().begin();
            auto end = d.args_get()->list_get().end();

            for (auto it = beg; it != end; ++it)
            {
                if (it != beg)
                    o_ << ",";

                (*it)->accept(*this);
            }
        }

        o_ << "):" << misc::indentendl;

        d.body_get()->accept(*this);

        o_ << misc::dedentendl;
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

    void PrettyPrinter::operator()(const AssignExpr& e)
    {
        running_ = &e;

        e.lvalue_get()->accept(*this);
        o_ << " = ";
        e.rvalue_get()->accept(*this);

        running_ = nullptr;
    }

    void PrettyPrinter::operator()(const NumeralExpr& e)
    {
        o_ << e.value_get();
    }

    void PrettyPrinter::operator()(const StringExpr& e)
    {
        o_ << "\"" << e.str_get() << "\"";
    }

    void PrettyPrinter::operator()(const IdVar& e)
    {
        o_ << e.id_get();

        if (bind::print_bind)
        {
            if (e.def_get())
                o_ << " \"\"\"" << e.def_get() << "\"\"\" ";
            else if (running_)
                o_ << " \"\"\"" << running_ << "\"\"\" ";
            else
                o_ << " \"\"\"" << &e << "\"\"\" ";
        }
    }

    void PrettyPrinter::operator()(const FunctionVar& v)
    {
        v.var_get()->accept(*this);

        o_ << "(";

        if (v.params_get())
        {
            auto beg = v.params_get()->list_get().begin();
            auto end = v.params_get()->list_get().end();

            for (auto it = beg; it != end; ++it)
            {
                if (it != beg)
                    o_ << ",";

                (*it)->accept(*this);
            }
        }

        o_ << ")";
    }
} // namespace ast
