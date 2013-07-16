#ifndef TYPE_TUPLE_HH
# define TYPE_TUPLE_HH

# include <type/type.hh>

namespace type
{
    class Tuple : public Type
    {
        Tuple(const Tuple&) = delete;
        Tuple& operator=(const Tuple&) = delete;

        public:
            static Tuple& instance();

            virtual std::ostream& dump(std::ostream& o) const;

            virtual std::string cpp_type() const;

        private:
            Tuple() = default;
    };
} // namespace type

#endif /* !TYPE_TUPLE_HH */
