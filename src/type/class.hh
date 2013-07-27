#ifndef TYPE_CLASS_HH
# define TYPE_CLASS_HH

# include <map>

# include <type/type.hh>

# include <ast/stmt.hh>

namespace type
{
    class Class : public Type
    {
        public:
            Class(const std::string& name);
            virtual ~Class();

            const std::string& name_get() const;

            ast::Stmt* component_get(const std::string& name);

            bool component_add(const std::string& name, ast::Stmt* dec);

            virtual std::ostream& dump(std::ostream& o) const;

            virtual std::string cpp_type() const;

        private:
            std::map<std::string, ast::Stmt*> content_;
            std::string name_;
    };
} // namepsace type

#endif /* !TYPE_CLASS_HH */
