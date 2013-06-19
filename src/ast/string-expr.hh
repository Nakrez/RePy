#ifndef AST_STRING_EXPR_HH
# define AST_STRING_EXPR_HH

# include <string>

# include <ast/expr.hh>
# include <ast/visitor.hh>

namespace ast
{
    class StringExpr : public Expr
    {
        public:
            StringExpr(const yy::location& location, const std::string& str);
            virtual ~StringExpr();

            void append(const std::string& str);

            const std::string& str_get() const;

            void accept(Visitor& v);
            void accept(ConstVisitor& v) const;

        protected:
            std::string str_;
    };
} // namespace ast

#endif /* !AST_STRING_EXPR_HH */
