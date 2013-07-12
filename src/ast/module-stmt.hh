#ifndef AST_MODULE_STMT_HH
# define AST_MODULE_STMT_HH

# include <ast/stmt.hh>

namespace ast
{
    class ModuleStmt : public Stmt
    {
        public:
            ModuleStmt(const yy::location& loc,
                       const std::string& name,
                       AstList* content);
            virtual ~ModuleStmt();

            const AstList* content_get() const;
            AstList* content_get();

            const std::string& name_get() const;
            std::string& name_get();

            void accept(Visitor& v);
            void accept(ConstVisitor& v) const;

        protected:
            std::string name_;
            AstList* content_;
    };
} // namespace ast

#endif /* !AST_MODULE_STMT_HH */
