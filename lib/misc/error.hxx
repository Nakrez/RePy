#ifndef MISC_ERROR_HXX
# define MISC_ERROR_HXX

# include <misc/error.hh>

namespace misc
{
    template<typename T>
    Error& Error::operator<<(const T& param)
    {
        msg_ << param;

        return *this;
    }
} // namespace misc

#endif /* !MISC_ERROR_HXX */
