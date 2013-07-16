#ifndef BUILTIN_BUILTIN_LIBRARY_HXX
# define BUILTIN_BUILTIN_LIBRARY_HXX

# include <builtin/builtin-library.hh>

namespace builtin
{
    // TODO : Find a way to have parameters that will build AssignExpr
    // to support builtin function that have default value for some parameters
    template<class ...Args>
    ast::ExprList* BuiltinLibrary::create_args(Args... args)
    {
        ast::ExprList* ret = new ast::ExprList(yy::location());

        std::vector<std::string> var = {args...};

        for (auto arg : var)
        {
            ret->push_back(new ast::IdVar(yy::location(), arg));
        }

        return ret;
    }

    template<class... Args>
    type::Function* BuiltinLibrary::create_types(type::Type* ret,
                                                 Args... args)
    {
        type::Function* f = new type::Function();

        std::vector<type::Type*> var = {args...};

        f->return_type_set(ret);

        for (auto arg : var)
        {
            f->args_type_add(arg);
        }

        return f;
    }

    inline bool BuiltinLibrary::is_builtin(const std::string& s) const
    {
        return builtin_.find(s) != builtin_.end();
    }

    inline std::string BuiltinLibrary::cpp_builtin(const std::string& s) const
    {
        return std::get<2>(builtin_.at(s));
    }
} // namespace builtin

#endif /* !BUILTIN_BUILTIN_LIBRARY_HXX */
