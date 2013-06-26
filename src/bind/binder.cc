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

        scope_map_.scope_begin();

        // Parser already avoid break/continue in condition
        ast.cond_get()->accept(*this);
        ast.loop_get()->accept(*this);

        scope_map_.scope_end();

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
    {
        if (loop_stack_.empty())
            error_ << misc::Error::BIND
                   << ast.location_get() << ": continue outside any loop"
                   << std::endl;
        else
            ast.in_loop_set(loop_stack_.top());
    }

    void Binder::operator()(ast::FunctionDec& s)
    {
        scope_map_.add(s.name_get(), &s);

        scope_map_.scope_begin();

        if (s.args_get())
            s.args_get()->accept(*this);

        s.body_get()->accept(*this);

        scope_map_.scope_end();
    }

    void Binder::operator()(ast::AssignExpr& ast)
    {}

    void Binder::operator()(ast::IdVar& ast)
    {
        if (!scope_map_.get(ast.id_get()))
            error_ << misc::Error::BIND
                   << ast.location_get() << ": unknown identifier "
                   << ast.id_get() << std::endl;
        else
            ast.def_set(scope_map_.get(ast.id_get()));
    }
} // namespace bind