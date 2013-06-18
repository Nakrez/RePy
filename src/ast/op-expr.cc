#include <ast/op-expr.hh>

namespace ast
{
    OpExpr::OpExpr(const yy::location& location,
                   Expr* lexpr,
                   OpExpr::Operator op,
                   Expr* rexpr)
        : Expr(location)
        , lexpr_(lexpr)
        , rexpr_(rexpr)
        , op_(op)
    {}

    OpExpr::~OpExpr()
    {
        delete lexpr_;
        delete rexpr_;
    }

    const Expr* OpExpr::left_expr_get() const
    {
        return lexpr_;
    }

    Expr* OpExpr::left_expr_get()
    {
        return lexpr_;
    }

    const Expr* OpExpr::right_expr_get() const
    {
        return rexpr_;
    }

    Expr* OpExpr::right_expr_get()
    {
        return rexpr_;
    }

    OpExpr::Operator OpExpr::op_get() const
    {
        return op_;
    }

    std::string OpExpr::op_to_string() const
    {
        switch (op_)
        {
            case PLUS:
                return "+";
            case MINUS:
                return "-";
            case MULT:
                return "*";
            case DIV:
                return "/";
            case FDIV:
                return "//";
            case MOD:
                return "%";
            case POW:
                return "**";
            case RSHIFT:
                return ">>";
            case LSHIFT:
                return "<<";
            case XOR:
                return "^";
            case BOOL_AND:
                return "and";
            case BOOL_OR:
                return "or";
            case BIT_AND:
                return "and";
            case BIT_OR:
                return "or";
            case EQ:
                return "==";
            case NEQ:
                return "!=";
            case GT:
                return ">";
            case GE:
                return ">=";
            case LT:
                return "<";
            case LE:
                return "<=";
        }

        return "";
    }

    void OpExpr::set_left_expr(Expr* expr)
    {
        if (lexpr_ == nullptr)
            lexpr_ = expr;

        OpExpr* e = dynamic_cast<OpExpr*> (lexpr_);

        if (e)
            e->set_left_expr(expr);
    }

    void OpExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void OpExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
