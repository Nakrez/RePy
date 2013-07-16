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
            delete std::get<0>(b.second);
            delete std::get<1>(b.second);
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

        // FIXME : DIRTY
        if (var->id_get() == "print")
        {
            v.type_set(&type::Void::instance());
            return;
        }

        if (std::get<1>(builtin_.at(var->id_get()))->compatible_with(prototype))
            error << misc::Error::TYPE
                  << v.location_get() << ": builtin \"" << var->id_get()
                  << "\" type mismatch" << std::endl;

        v.type_set(std::get<1>(builtin_.at(var->id_get()))->return_type_get());
    }

    const ast::ExprList*
    BuiltinLibrary::args_get(const ast::FunctionVar& v) const
    {
        const ast::IdVar* var = dynamic_cast<const ast::IdVar*> (v.var_get());

        assert(var && "Internal compiler error");

        return std::get<0>(builtin_.at(var->id_get()));
    }

    void BuiltinLibrary::init()
    {
        builtin_["float"] = Builtin(create_args("x"),
                                    create_types(&type::Int::instance(),
                                                 &type::Polymorphic::instance()),
                                    "repy::__builtin_float");
        builtin_["input"] = Builtin(create_args("prompt"),
                                    create_types(&type::String::instance(),
                                                 &type::String::instance()),
                                    "repy::__builtin_input");
        builtin_["print"] = Builtin(nullptr, nullptr, "repy::__builtin_print");
        builtin_["str"] = Builtin(create_args("object"),
                                  create_types(&type::String::instance(),
                                               &type::Polymorphic::instance()),
                                  "repy::__builtin_str");
    }
} // namespace builtin
