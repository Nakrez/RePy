#ifndef AST_ANY_LIST_HH
# define AST_ANY_LIST_HH

# include <list>

# include <ast/all.hh>

namespace ast
{
    template <class T>
    class AnyList : public T
    {
        public:
            AnyList(const yy::location& location);
            virtual ~AnyList();

            const std::list<T*>& list_get() const;
            std::list<T*>& list_get();

            virtual void accept(Visitor& v);
            virtual void accept(ConstVisitor& v) const;

            void set_delete(bool d);

            void push_back(T* elem);
            void splice(AnyList<T>* list);

        protected:
            std::list<T*> list_;
            bool delete_;
    };
} // namespace ast

# include <ast/any-list.hxx>

#endif /* !ANY_LIST_HH */
