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
            virtual bool compatible_with(const Type& t) = 0;

            /// @brief print a type onto a stream
            virtual bool dump(std::ostream& o) = 0;
    };
} // namespace type

#endif /* !TYPE_TYPE_HH */
