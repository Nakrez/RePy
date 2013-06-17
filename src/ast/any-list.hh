#ifndef AST_ANY_LIST_HH
# define AST_ANY_LIST_HH

# include <list>

# include <ast/all.hh>

namespace ast
{
    template <class T>
    class AnyList : public Ast
    {
        public:
            AnyList(const yy::location& location);
            virtual ~AnyList();

            const std::list<T*>& list_get() const;
            std::list<T*>& list_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

        protected:
            std::list<T*> list_;
    };
} // namespace ast

# include <ast/any-list.hxx>

#endif /* !ANY_LIST_HH */
