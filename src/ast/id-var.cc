#include <ast/id-var.hh>

namespace ast
{
    IdVar::IdVar(const yy::location& location, const std::string& id)
        : Var(location)
        , id_(id)
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

    void IdVar::accept(Visitor& v)
    {
        v(*this);
    }

    void IdVar::accept(ConstVisitor& v) const
    {
        v(*this);
    }
} // namespace ast
