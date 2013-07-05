#include <builtin/builtin-library.hh>

namespace builtin
{
    BuiltinLibrary::BuiltinLibrary()
    {}

    BuiltinLibrary::~BuiltinLibrary()
    {
        for (auto b : builtin_)
        {
            delete b.second.first;
            delete b.second.second;
        }
    }

    BuiltinLibrary& BuiltinLibrary::instance()
    {
        static BuiltinLibrary lib;

        return lib;
    }
} // namespace builtin
