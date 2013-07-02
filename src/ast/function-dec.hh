#ifndef AST_FUNCTION_DEC_HH
# define AST_FUNCTION_DEC_HH

# include <string>
# include <list>

# include <ast/fwd.hh>
# include <ast/typed.hh>

# include <type/function.hh>
# include <type/polymorphic.hh>

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

            const type::Function* type_get() const;
            type::Function* type_get();

            void type_set(type::Function* t);

            const std::list<type::Function*>& to_generate_get() const;
            std::list<type::Function*>& to_generate_get();

            void to_generate_add(type::Function* f);
            void to_generate_set(const std::list<type::Function*>& l);

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            std::string name_;
            ExprList* args_;
            Stmt* body_;
            type::Function* type_;
            std::list<type::Function*> to_generate_;
    };
} // namespace ast

#endif /* !AST_FUNCTION_DEC_HH */
