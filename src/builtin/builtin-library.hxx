#ifndef BUILTIN_BUILTIN_LIBRARY_HXX
# define BUILTIN_BUILTIN_LIBRARY_HXX

# include <builtin/builtin-library.hh>

namespace builtin
{
    inline bool BuiltinLibrary::is_builtin(const std::string& s) const
    {
        return builtin_.find(s) != builtin_.end();
    }
} // namespace builtin

#endif /* !BUILTIN_BUILTIN_LIBRARY_HXX */
