#ifndef AST_BREAK_STMT_HH
# define AST_BREAK_STMT_HH

# include <ast/stmt.hh>

namespace ast
{
    class BreakStmt : public Stmt
    {
        public:
            BreakStmt(const yy::location& location);
            virtual ~BreakStmt();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;
    };
}

#endif /* !AST_BREAK_STMT_HH */
