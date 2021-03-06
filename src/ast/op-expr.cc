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
                return "&";
            case BIT_OR:
                return "|";
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
            case IN:
                return "in";
            case IS:
                return "is";
            case NOT_IN:
                return "not in";
            case IS_NOT:
                return "is not";
        }

        return "";
    }

    std::string OpExpr::to_cpp() const
    {
        switch (op_)
        {
            case PLUS:
                return "repy::__add__";
            case MINUS:
                return "repy::__sub__";
            case MULT:
                return "repy::__mul__";
            case DIV:
                return "repy::__divmod__";
            case FDIV:
                return "repy::__floordiv__";
            case MOD:
                return "repy::__mod__";
            case POW:
                return "repy::__pow__";
            case RSHIFT:
                return "repy::__lshift__";
            case LSHIFT:
                return "repy::__rshift__";
            case XOR:
                return "repy::__xor__";
            case BIT_AND:
                return "repy::__and__";
            case BIT_OR:
                return "repy::__or__";
            case EQ:
                return "repy::__eq__";
            case NEQ:
                return "repy::__ne__";
            case GT:
                return "repy::__gt__";
            case GE:
                return "repy::__ge__";
            case LT:
                return "repy::__lt__";
            case LE:
                return "repy::__le__";
            default:
                assert(false && "Internal compiler error");
                break;
        }

        return "";
    }

    void OpExpr::set_left_expr(Expr* expr)
    {
        if (lexpr_ == nullptr)
        {
            lexpr_ = expr;
            return;
        }

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
