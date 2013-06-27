#ifndef TYPE_INT_HH
# define TYPE_INT_HH

# include <type/type.hh>

namespace type
{
    class Int : public Type
    {
        Int(const Int&) = delete;
        Int& operator=(const Int&) = delete;

        public:
            static Type& instance();

            virtual bool compatible_with(const Type& t);
            virtual std::ostream& dump(std::ostream& o);

        private:
            Int() = default;
    };
} // namespace type

#endif /* !TYPE_INT_HH */
