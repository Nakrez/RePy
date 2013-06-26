#include <bind/binder.hh>

namespace bind
{
    Binder::Binder()
        : scope_map_(misc::ScopedMap<std::string, ast::Stmt*>(nullptr))
    {}

    Binder::~Binder()
    {}

    misc::Error& Binder::error_get()
    {
        return error_;
    }

    void Binder::operator()(ast::WhileStmt& ast)
    {
        loop_stack_.push(&ast);

        // Parser already avoid break/continue in condition
        ast.cond_get()->accept(*this);
        ast.loop_get()->accept(*this);

        loop_stack_.pop();
    }

    void Binder::operator()(ast::BreakStmt& ast)
    {
        if (loop_stack_.empty())
            error_ << misc::Error::BIND
                   << ast.location_get() << ": break outside any loop"
                   << std::endl;
        else
            ast.in_loop_set(loop_stack_.top());
    }

    void Binder::operator()(ast::ContinueStmt& ast)
    {}

    void Binder::operator()(ast::FunctionDec& ast)
    {}

    void Binder::operator()(ast::IdVar& ast)
    {}

    void Binder::operator()(ast::FunctionVar& ast)
    {}
} // namespace bind
