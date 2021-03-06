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

            const FunctionDec* def_get() const;
            FunctionDec* def_get();

            bool constructor_get() const;
            void constructor_set(bool c);

            void def_set(FunctionDec* d);
            void params_set(ExprList* p);

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Var* var_;
            ExprList* params_;
            FunctionDec* def_;
            bool constructor_;
    };
} // namespace ast

#endif /* !AST_FUNCTION_VAR_HH */
