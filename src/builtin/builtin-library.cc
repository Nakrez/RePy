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

    void BuiltinLibrary::type_check(ast::FunctionVar& v, misc::Error& error)
    {

    }

    const ast::ExprList*
    BuiltinLibrary::args_get(const ast::FunctionVar& v) const
    {
        const ast::IdVar* var = dynamic_cast<const ast::IdVar*> (v.var_get());

        assert(var && "Internal compiler error");

        return builtin_.at(var->id_get()).first;
    }

    void BuiltinLibrary::init()
    {
        builtin_["str"] = Builtin(create_args("object"),
                                  create_types(&type::String::instance(),
                                               &type::Polymorphic::instance()));
    }
} // namespace builtin
