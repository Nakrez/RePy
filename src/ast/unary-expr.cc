#include <ast/unary-expr.hh>

namespace ast
{
    UnaryExpr::UnaryExpr(const yy::location& location,
                         UnaryExpr::Operator op,
                         Expr* expr)
        : Expr(location)
        , expr_(expr)
        , op_(op)
    {}

    UnaryExpr::~UnaryExpr()
    {
        delete expr_;
    }

    const Expr* UnaryExpr::expr_get() const
    {
        return expr_;
    }

    Expr* UnaryExpr::expr_get()
    {
        return expr_;
    }

    UnaryExpr::Operator UnaryExpr::op_get() const
    {
        return op_;
    }

    std::string UnaryExpr::op_to_string() const
    {
        switch (op_)
        {
            case UNARY_PLUS:
                return "+";
            case UNARY_MINUS:
                return "-";
            case UNARY_COMPLEMENT:
                return "~";
            case UNARY_NOT:
                return "not";
        }

        return "";
    }

    void UnaryExpr::accept(Visitor& v)
    {
        v(*this);
    }

    void UnaryExpr::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
