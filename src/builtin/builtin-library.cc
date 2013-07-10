#include <builtin/builtin-library.hh>

namespace builtin
{
    BuiltinLibrary::BuiltinLibrary()
    {
        init();
    }

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

    void BuiltinLibrary::init()
    {
        builtin_["str"] = Builtin(create_args("str"),
                                  create_types(&type::String::instance(),
                                               &type::Polymorphic::instance()));
    }
} // namespace builtin
