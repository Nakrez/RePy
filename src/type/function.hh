#ifndef TYPE_FUNCTION_HH
# define TYPE_FUNCTION_HH

# include <list>
# include <cassert>

# include <type/type.hh>

namespace type
{
    class Function : public Type
    {
        public:
            Function();
            ~Function();

            const Type* return_type_get() const;
            Type* return_type_get();

            const std::list<Type*>& args_get() const;
            std::list<Type*>& args_get();

            void return_type_set(Type* t);
            void args_type_add(Type* t);

            virtual bool compatible_with(const Type& t);
            virtual std::ostream& dump(std::ostream& o) const;

            virtual std::string cpp_type() const;

        protected:
            Type* return_type_;
            std::list<Type*> args_type_;
    };
} // namespace type

#endif /* !TYPE_FUNCTION_HH */
