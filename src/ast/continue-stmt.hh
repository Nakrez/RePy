#ifndef AST_CONTINUE_STMT_HH
# define AST_CONTINUE_STMT_HH

# include <ast/stmt.hh>
# include <ast/visitor.hh>

namespace ast
{
    class ContinueStmt : public Stmt
    {
        public:
            ContinueStmt(const yy::location& location);
            virtual ~ContinueStmt();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;
    };
} // namespace ast

#endif /* !AST_CONTINUE_STMT_HH */
