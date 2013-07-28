#ifndef AST_METHOD_VAR_HH
# define AST_METHOD_VAR_HH

# include <ast/var.hh>
# include <ast/function-var.hh>
# include <ast/field-var.hh>

namespace ast
{
    class MethodVar : public Var
    {
        public:
            MethodVar(const yy::location& loc, FieldVar* field,
                      FunctionVar* call);
            virtual ~MethodVar();

            const std::string& name_get() const;
            std::string& name_get();

            const ExprList* params_get() const;
            ExprList* params_get();

            const FunctionVar* call_get() const;
            FunctionVar* call_get();

            const FieldVar* field_get() const;
            FieldVar* field_get();

            const Var* var_get() const;
            Var* var_get();

            const FunctionDec* def_get() const;
            FunctionDec* def_get();

            void def_set(FunctionDec* d);
            void params_set(ExprList* p);

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        private:
            FieldVar* field_;
            FunctionVar* call_;
    };
} // namespace ast

#endif /* !AST_METHOD_VAR_HH */
