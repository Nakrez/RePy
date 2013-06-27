#ifndef AST_TYPED_HH
# define AST_TYPED_HH

# include <type/type.hh>

namespace ast
{
    class Typed
    {
        public:
            Typed();
            ~Typed();

            const type::Type* type_get() const;
            type::Type* type_get();

            void type_set(type::Type* type);

        protected:
            type::Type* type_;
    };
} // namespace ast

#endif /* !AST_TYPED_HH */
