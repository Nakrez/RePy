#include <ast/class-dec.hh>
#include <ast/any-list.hh>

namespace ast
{
    ClassDec::ClassDec(const yy::location& loc, const std::string& name,
                       ExprList* inherit, Stmt* def)
        : Stmt(loc)
        , name_(name)
        , inherit_(inherit)
        , def_(def)
        , type_class_(new type::Class(name))
    {}

    ClassDec::~ClassDec()
    {
        delete inherit_;
        delete def_;
    }

    const std::string& ClassDec::name_get() const
    {
        return name_;
    }

    std::string& ClassDec::name_get()
    {
        return name_;
    }

    const ExprList* ClassDec::inherit_get() const
    {
        return inherit_;
    }

    ExprList* ClassDec::inherit_get()
    {
        return inherit_;
    }

    const Stmt* ClassDec::def_get() const
    {
        return def_;
    }

    Stmt* ClassDec::def_get()
    {
        return def_;
    }

    const type::Class* ClassDec::type_class_get() const
    {
        return type_class_;
    }

    type::Class* ClassDec::type_class_get()
    {
        return type_class_;
    }

    void ClassDec::type_class_set(type::Class* c)
    {
        delete type_class_;
        type_class_ = c;
    }

    void ClassDec::accept(Visitor& v)
    {
        v(*this);
    }

    void ClassDec::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
