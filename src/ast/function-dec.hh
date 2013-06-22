#ifndef AST_FUNCTION_DEC_HH
# define AST_FUNCTION_DEC_HH

# include <string>

# include <ast/fwd.hh>

namespace ast
{
    class FunctionDec : public Stmt
    {
        public:
            FunctionDec(const yy::location& location,
                        const std::string& name,
                        ExprList* args,
                        Stmt* body);
            virtual ~FunctionDec();

            const std::string& name_get() const;
            std::string& name_get();

            const ExprList* args_get() const;
            ExprList* args_get();

            const Stmt* body_get() const;
            Stmt* body_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            std::string name_;
            ExprList* args_;
            Stmt* body_;
    };
} // namespace ast

#endif /* !AST_FUNCTION_DEC_HH */
