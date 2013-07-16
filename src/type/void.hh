#ifndef TYPE_VOID_HH
# define TYPE_VOID_HH

# include <type/type.hh>

namespace type
{
    class Void : public Type
    {
        Void(const Void&) = delete;
        Void& operator=(const Void&) = delete;

        public:
            static Void& instance();

            virtual std::ostream& dump(std::ostream& o) const;

            virtual std::string cpp_type() const;

        private:
            Void() = default;
    };
} // namespace type

#endif /* !TYPE_VOID_HH */
