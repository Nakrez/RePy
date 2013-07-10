#include <builtin/builtin-library.hh>
#include <type/type-checker.hh>

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

    void BuiltinLibrary::type_check(ast::FunctionVar& v, misc::Error& error,
                                    type::TypeChecker& typec)
    {
        const ast::IdVar* var = dynamic_cast<const ast::IdVar*> (v.var_get());
        type::Function prototype;

        assert(var && "Internal compiler error");

        if (v.params_get())
        {
            for (auto p : v.params_get()->list_get())
            {
                p->accept(typec);

                prototype.args_type_add(p->type_get());
            }
        }

        if (!builtin_.at(var->id_get()).second->compatible_with(prototype))
            error << misc::Error::TYPE
                  << v.location_get() << ": builtin \"" << var->id_get()
                  << "\" type mismatch" << std::endl;

        v.type_set(builtin_.at(var->id_get()).second->return_type_get());
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
