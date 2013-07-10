#ifndef BUILTIN_BUILTIN_LIBRARY_HH
# define BUILTIN_BUILTIN_LIBRARY_HH

# include <map>
# include <string>

# include <ast/all.hh>

# include <type/function.hh>
# include <type/string.hh>
# include <type/polymorphic.hh>

namespace builtin
{
    class BuiltinLibrary
    {
        BuiltinLibrary(const BuiltinLibrary&) = delete;
        BuiltinLibrary& operator=(const BuiltinLibrary&) = delete;

        public:
            typedef std::pair<ast::ExprList*, type::Function*> Builtin;

            static BuiltinLibrary& instance();

            bool is_builtin(const std::string& s) const;

        protected:
            std::map<std::string, Builtin> builtin_;

        private:
            BuiltinLibrary();
            ~BuiltinLibrary();

            void init();

            template<class... Args>
            ast::ExprList* create_args(Args... args);

            template<class... Args>
            type::Function* create_types(type::Type* ret, Args... args);
    };
} // namespace builtin

# include <builtin/builtin-library.hxx>

#endif /* !BUILTIN_BUILTIN_LIBRARY_HH */