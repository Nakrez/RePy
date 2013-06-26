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

            const Stmt* in_loop_get() const;
            Stmt* in_loop_get();

            void in_loop_set(Stmt* l);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        private:
            Stmt* in_loop_;
    };
} // namespace ast

#endif /* !AST_CONTINUE_STMT_HH */
