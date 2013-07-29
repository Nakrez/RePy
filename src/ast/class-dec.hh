#ifndef AST_CLASS_DEC_HH
# define AST_CLASS_DEC_HH

# include <ast/stmt.hh>

# include <type/class.hh>

namespace ast
{
    class ClassDec : public Stmt
    {
        public:
            ClassDec(const yy::location& loc, const std::string& name,
                     ExprList* inherit, Stmt* def);
            virtual ~ClassDec();

            const std::string& name_get() const;
            std::string& name_get();

            const ExprList* inherit_get() const;
            ExprList* inherit_get();

            const Stmt* def_get() const;
            Stmt* def_get();

            const type::Class* type_get() const;
            type::Class* type_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        private:
            std::string name_;
            ExprList* inherit_;
            Stmt* def_;
            type::Class* type_;
    };
} // namespace ast

#endif /* !AST_CLASS_DEC_HH */
