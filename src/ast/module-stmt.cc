#include <ast/module-stmt.hh>
#include <ast/all.hh>

namespace ast
{
    ModuleStmt::ModuleStmt(const yy::location& loc,
                           const std::string& name,
                           ast::AstList* content)
        : Stmt(loc)
        , name_(name)
        , content_(content)
    {}

    ModuleStmt::~ModuleStmt()
    {
        delete content_;
    }

    const AstList* ModuleStmt::content_get() const
    {
        return content_;
    }

    AstList* ModuleStmt::content_get()
    {
        return content_;
    }

    const std::string& ModuleStmt::name_get() const
    {
        return name_;
    }

    std::string& ModuleStmt::name_get()
    {
        return name_;
    }

    void ModuleStmt::accept(Visitor& v)
    {
        v(*this);
    }

    void ModuleStmt::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
