#ifndef AST_FIELD_VAR_HH
# define AST_FIELD_VAR_HH

# include <ast/var.hh>

namespace ast
{
    class FieldVar : public Var
    {
        public:
            FieldVar(const yy::location& loc, Var* var,
                     const std::string name);
            virtual ~FieldVar();

            const std::string& name_get() const;
            std::string& name_get();

            const Var* var_get() const;
            Var* var_get();

            const type::Type* type_get() const;
            type::Type* type_get();

            void type_set(type::Type* t);

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            Var* var_;
            std::string name_;
            type::Type* type_;
    };
} // namespace ast

#endif /* !AST_FIELD_VAR_HH */
