#include <ast/id-var.hh>
#include <cassert>

namespace ast
{
    IdVar::IdVar(const yy::location& location, const std::string& id)
        : Var(location)
        , id_(id)
        , def_(nullptr)
    {}

    IdVar::~IdVar()
    {}

    const std::string& IdVar::id_get() const
    {
        return id_;
    }

    std::string& IdVar::id_get()
    {
        return id_;
    }

    const Stmt* IdVar::def_get() const
    {
        return def_;
    }

    Stmt* IdVar::def_get()
    {
        return def_;
    }

    void IdVar::def_set(Stmt* s)
    {
        def_ = s;
    }

    void IdVar::add_component(Var*)
    {
        assert(false && "Internal compiler error : unreachable part");
    }

    void IdVar::accept(Visitor& v)
    {
        v(*this);
    }

    void IdVar::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
