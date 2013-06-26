#include <ast/pretty-printer.hh>
#include <ast/all.hh>
#include <cassert>

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

        &o_ << misc::iendl;
    }

    void PrettyPrinter::operator()(const StmtList& ast)
    {
        auto beg = ast.list_get().begin();
        auto end = ast.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                &o_ << misc::iendl;

            (*it)->accept(*this);
        }

        &o_ << misc::iendl;
    }

    void PrettyPrinter::operator()(const ExprList& e)
    {
        auto beg = e.list_get().begin();
        auto end = e.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                &o_ << ",";

            (*it)->accept(*this);
        }
    }

    void PrettyPrinter::operator()(const PassStmt&)
    {
        &o_ << "pass";
    }

    void PrettyPrinter::operator()(const BreakStmt& s)
    {
        if (bind::print_bind)
            &o_ << "# break link to loop : " << s.in_loop_get() << misc::iendl;

        &o_ << "break";
    }

    void PrettyPrinter::operator()(const ContinueStmt& s)
    {
        if (bind::print_bind)
            &o_ << "# continue link to loop : " << s.in_loop_get()
               << misc::iendl;

        &o_ << "continue";
    }

    void PrettyPrinter::operator()(const IfStmt& ast)
    {
        &o_ << "if ";

        ast.cond_get()->accept(*this);

        &o_ << ":" << misc::indentendl;

        ast.true_stmt_get()->accept(*this);

        &o_ << misc::dedentendl;

        if (ast.else_stmt_get())
        {
            if (dynamic_cast<const ast::IfStmt*> (ast.else_stmt_get()))
                &o_ << "el";
            else
                &o_ << "else:" << misc::indentendl;

            ast.else_stmt_get()->accept(*this);
            &o_ << misc::dedent;
        }
    }

    void PrettyPrinter::operator()(const WhileStmt& s)
    {
        if (bind::print_bind)
            &o_ << "# while @ : " << &s << misc::iendl;
        &o_ << "while ";

        s.cond_get()->accept(*this);

        &o_ << ":" << misc::indentendl;

        s.loop_get()->accept(*this);

        &o_ << misc::dedentendl;
    }

    void PrettyPrinter::operator()(const ReturnStmt& s)
    {
        &o_ << "return ";
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const YieldExpr& s)
    {
        &o_ << "yield ";
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const FunctionDec& d)
    {
        if (bind::print_bind)
            &o_ << "# Function @ : " << &d << misc::iendl;

        &o_ << "def " << d.name_get() << "(";

        if (d.args_get())
        {
            auto beg = d.args_get()->list_get().begin();
            auto end = d.args_get()->list_get().end();

            for (auto it = beg; it != end; ++it)
            {
                if (it != beg)
                    &o_ << ",";

                (*it)->accept(*this);
            }
        }

        &o_ << "):" << misc::indentendl;

        d.body_get()->accept(*this);

        &o_ << misc::dedentendl;
    }

    void PrettyPrinter::operator()(const OpExpr& e)
    {
        e.left_expr_get()->accept(*this);
        &o_ << " " << e.op_to_string() << " ";
        e.right_expr_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const UnaryExpr& e)
    {
        &o_ << e.op_to_string() << " ";
        e.expr_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const AssignExpr& e)
    {
        e.lvalue_get()->accept(*this);
        &o_ << " = ";
        e.rvalue_get()->accept(*this);
    }

    void PrettyPrinter::operator()(const NumeralExpr& e)
    {
        &o_ << e.value_get();
    }

    void PrettyPrinter::operator()(const StringExpr& e)
    {
        &o_ << "\"" << e.str_get() << "\"";
    }

    void PrettyPrinter::operator()(const IdVar& e)
    {
        if (bind::print_bind)
            bind_ << e.id_get() << " @ " << e.def_get() << misc::iendl;

        &o_ << e.id_get();
    }

    void PrettyPrinter::operator()(const FunctionVar& v)
    {
        misc::MutableRef<std::ostream> temp(&o_);
        std::stringstream fun;
        misc::MutableRef<std::ostream> ref(fun);

        std::swap(ref, o_);

        v.var_get()->accept(*this);

        &o_ << "(";

        if (v.params_get())
        {
            auto beg = v.params_get()->list_get().begin();
            auto end = v.params_get()->list_get().end();

            for (auto it = beg; it != end; ++it)
            {
                if (it != beg)
                    &o_ << ",";

                (*it)->accept(*this);
            }
        }

        &o_ << ")";

        if (bind::print_bind)
        {
            &temp << "# " << bind_.str();
            bind_.str("");
            bind_.clear();
        }

        &temp << fun.str();
        std::swap(o_, temp);
    }
} // namespace ast
