#ifndef TYPE_POLYMORPHIC_HH
# define TYPE_POLYMORPHIC_HH

# include <type/type.hh>

namespace type
{
    class Polymorphic : public Type
    {
        Polymorphic(const Polymorphic&) = delete;
        Polymorphic& operator=(const Polymorphic&) = delete;

        public:
            static Polymorphic& instance();

            virtual bool compatible_with(const Type& t);
            virtual std::ostream& dump(std::ostream& o) const;

        private:
            Polymorphic() = default;
    };
} // namespace type

#endif /* !POLYMORPHIC_HH */
