#ifndef AST_ID_VAR_HH
# define AST_ID_VAR_HH

# include <string>

# include <ast/var.hh>
# include <ast/visitor.hh>

namespace ast
{
    class IdVar : public Var
    {
        public:
            IdVar(const yy::location& location, const std::string& id);
            virtual ~IdVar();

            const std::string& id_get() const;
            std::string& id_get();

            const Ast* def_get() const;
            Ast* def_get();

            void def_set(Ast* s);

            bool global_get() const;
            void global_set(bool g);

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            std::string id_;
            Ast* def_;
            bool global_;
    };
} // namespace ast

#endif /* !AST_ID_VAR_HH */
