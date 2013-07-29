#ifndef TYPE_TYPE_HH
# define TYPE_TYPE_HH

# include <ostream>

namespace type
{
    class Type
    {
        public:
            Type();
            virtual ~Type();

            /// @brief Check if the type if compatible with @a t
            virtual bool compatible_with(const Type& t);

            /// @brief print a type onto a stream
            virtual std::ostream& dump(std::ostream& o) const = 0;

            /// @brief String corresponding to C++ type
            virtual std::string cpp_type() const;
    };

    std::ostream& operator<<(std::ostream& o, const type::Type& type);
} // namespace type

#endif /* !TYPE_TYPE_HH */
