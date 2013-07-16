#include <misc/error.hh>

namespace misc
{
    Error::Error()
        : error_type_(NONE)
    {}

    Error::Error(const Error& error)
    {
        error_type_ = error.error_type_;
        msg_ << error.msg_get();
    }

    Error& Error::operator=(const Error& error)
    {
        error_type_ = error.error_type_;
        msg_ << error.msg_get();

        return *this;
    }

    Error& Error::operator<<(Error::error_type error)
    {
        if (error_type_ == NONE || error < error_type_)
            error_type_ = error;

        return *this;
    }

    Error& Error::operator<<(const std::string& str)
    {
        msg_ << str;

        return *this;
    }

    Error& Error::operator<<(std::ostream& (*fun)(std::ostream&))
    {
        msg_ << fun;

        return *this;
    }

    Error& Error::operator<<(const Error& error)
    {
        *this << error.error_type_;
        *this << error.msg_get();

        return *this;
    }

    Error::error_type Error::error_type_get() const
    {
        return error_type_;
    }

    std::string Error::msg_get() const
    {
        return msg_.str();
    }

    void Error::throw_if_needed()
    {
        if (error_type_ != NONE)
            throw *this;
    }
} // namespace misc
