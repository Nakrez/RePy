#include <ast/id-var.hh>
#include <cassert>

namespace ast
{
    IdVar::IdVar(const yy::location& location, const std::string& id)
        : Var(location)
        , id_(id)
        , def_(nullptr)
        , global_(false)
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

    const Ast* IdVar::def_get() const
    {
        return def_;
    }

    Ast* IdVar::def_get()
    {
        return def_;
    }

    void IdVar::def_set(Ast* s)
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

    bool IdVar::global_get() const
    {
        return global_;
    }

    void IdVar::global_set(bool g)
    {
        global_ = g;
    }
} // namespace ast
