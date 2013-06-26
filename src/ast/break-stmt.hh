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

            const Stmt* in_loop_get() const;
            Stmt* in_loop_get();

            void in_loop_set(Stmt* loop);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        private:
            Stmt* in_loop_;
    };
}

#endif /* !AST_BREAK_STMT_HH */
