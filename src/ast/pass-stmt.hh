#ifndef AST_PASS_STMT_HH
# define AST_PASS_STMT_HH

# include <ast/stmt.hh>
# include <ast/visitor.hh>

namespace ast
{
    class PassStmt : public Stmt
    {
        public:
            PassStmt(const yy::location& location);
            virtual ~PassStmt();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;
    };
} // namespace ast

#endif /* !AST_PASS_STMT_HH */
