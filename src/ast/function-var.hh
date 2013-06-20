#ifndef AST_FUNCTION_VAR_HH
# define AST_FUNCTION_VAR_HH

# include <ast/fwd.hh>
# include <ast/var.hh>

namespace ast
{
    class FunctionVar : public Var
    {
        public:
            FunctionVar(const yy::location& location,
                        Var* var,
                        ExprList* params);
            virtual ~FunctionVar();

            const Var* var_get() const;
            Var* var_get();

            const ExprList* params_get() const;
            ExprList* params_get();

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Var* var_;
            ExprList* params_;
    };
} // namespace ast

#endif /* !AST_FUNCTION_VAR_HH */
