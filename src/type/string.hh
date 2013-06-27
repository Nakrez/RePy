#ifndef TYPE_STRING_HH
# define TYPE_STRING_HH

# include <type/type.hh>

namespace type
{
    class String : public Type
    {
        String(const String&) = delete;
        String& operator=(const String&) = delete;

        public:
            static String& instance();

            virtual bool compatible_with(const Type& t);
            virtual std::ostream& dump(std::ostream& o) const;

        private:
            String() = default;
    };
} // namespace type

#endif /* !TYPE_STRING_HH */
