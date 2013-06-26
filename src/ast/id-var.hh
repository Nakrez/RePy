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

            const Stmt* def_get() const;
            Stmt* def_get();

            void def_set(Stmt* s);

            virtual void add_component(Var* v);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            std::string id_;
            Stmt* def_;
    };
} // namespace ast

#endif /* !AST_ID_VAR_HH */
