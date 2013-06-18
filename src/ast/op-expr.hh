#ifndef AST_OP_EXPR_HH
# define AST_OP_EXPR_HH

# include <string>

# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class OpExpr : public Expr
    {
        enum Operator
        {
            PLUS,
            MINUS,
            MULT,
            DIV,
            FDIV,
            MOD,
            POW,
            RSHIFT,
            LSHIFT,
            XOR,
            BOOL_AND,
            BOOL_OR,
            BIT_AND,
            BIT_OR,
            EQ,
            NEQ,
            GT,
            GE,
            LT,
            LE
        };

        public:
            OpExpr(const yy::location& location,
                   Expr* lexpr,
                   OpExpr::Operator op,
                   Expr* rexpr);
            virtual ~OpExpr();

            const Expr* left_expr_get() const;
            Expr* left_expr_get();

            const Expr* right_expr_get() const;
            Expr* right_expr_get();

            OpExpr::Operator op_get() const;
            std::string op_to_string() const;

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Expr* lexpr_;
            Expr* rexpr_;
            OpExpr::Operator op_;
    };
} // namespace ast

#endif /* !AST_OP_EXPR_HH */
