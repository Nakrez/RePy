#ifndef MISC_ERROR_HH
# define MISC_ERROR_HH

# include <iostream>
# include <sstream>

namespace misc
{
    class Error
    {
        public:
            enum error_type
            {
                NONE = 0,
                SCAN = 2,
                PARSE,
                BIND,
                TYPE
            };

            Error();
            Error(const Error& error);

            Error& operator=(const Error& error);

            template<typename T> Error& operator<<(const T& param);

            Error& operator<<(Error::error_type error);
            Error& operator<<(const std::string& str);
            Error& operator<<(std::ostream& (*fun)(std::ostream&));
            Error& operator<<(const Error& error);

            Error::error_type error_type_get() const;
            std::string msg_get() const;

            void throw_if_needed();

        private:
            error_type error_type_;
            std::stringstream msg_;
    };
} // namespace misc

# include <misc/error.hxx>

#endif /* !MISC_ERROR_HH */
