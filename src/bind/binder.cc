#include <bind/binder.hh>

namespace bind
{
    Binder::Binder()
        : scope_map_(misc::ScopedMap<std::string, ast::Ast*>(nullptr))
        , declaration_(false)
        , in_class_(false)
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

    void Binder::operator()(ast::ClassDec& ast)
    {
        bool old = in_class_;

        scope_map_.add(ast.name_get(), &ast);

        in_class_ = true;
        ast.def_get()->accept(*this);
        in_class_ = old;
    }

    void Binder::operator()(ast::FunctionDec& s)
    {
        if (!in_class_)
            scope_map_.add(s.name_get(), &s);

        scope_map_.scope_begin();

        if (s.args_get())
        {
            for (auto arg : s.args_get()->list_get())
            {
                ast::IdVar* var = dynamic_cast<ast::IdVar*> (arg);

                if (var)
                    scope_map_.add(var->id_get(), var);
                else
                {
                    declaration_ = true;
                    arg->accept(*this);
                    declaration_ = false;
                }
            }
        }

        s.body_get()->accept(*this);

        scope_map_.scope_end();
    }

    void Binder::operator()(ast::FunctionVar& ast)
    {
        ast::IdVar* v = dynamic_cast<ast::IdVar*> (ast.var_get());

        if (v)
        {
            ast::FunctionDec* d = nullptr;

            d = dynamic_cast<ast::FunctionDec*> (scope_map_.get(v->id_get()));

            if (d)
                ast.def_set(d);
            else if (!builtin::BuiltinLibrary::instance().is_builtin(v->id_get()))
            {
                // Check if the name match a class dec
                ast::ClassDec* c = dynamic_cast<ast::ClassDec*> (scope_map_.get(v->id_get()));

                if (!c)
                    error_ << misc::Error::BIND
                           << ast.location_get() << ": undeclared function "
                           << v->id_get() << std::endl;
            }
        }
        else
            assert(false
                   && "Function call from function result not yet supported");

        if (ast.params_get())
            ast.params_get()->accept(*this);
    }

    void Binder::operator()(ast::StarExpr& ast)
    {
        ast::IdVar* var = dynamic_cast<ast::IdVar*> (ast.expr_get());

        if (!var)
            error_ << misc::Error::BIND
                   << ast.location_get() << ": Invalid double star expr "
                   << var->id_get() << std::endl;
        else if (declaration_)
            scope_map_.add(var->id_get(), &ast);
        else if (!scope_map_.get(var->id_get()))
            error_ << misc::Error::BIND
                   << ast.location_get() << ": unknown identifier "
                   << var->id_get() << std::endl;
        else
        {
            ast.def_set(scope_map_.get(var->id_get()));
            var->def_set(scope_map_.get(var->id_get()));
        }
    }

    void Binder::operator()(ast::DoubleStarExpr& ast)
    {
        ast::IdVar* var = dynamic_cast<ast::IdVar*> (ast.expr_get());

        if (!var)
            error_ << misc::Error::BIND
                   << ast.location_get() << ": Invalid double star expr "
                   << var->id_get() << std::endl;
        else if (declaration_)
            scope_map_.add(var->id_get(), &ast);
        else if (!scope_map_.get(var->id_get()))
            error_ << misc::Error::BIND
                   << ast.location_get() << ": unknown identifier "
                   << var->id_get() << std::endl;
        else
        {
            ast.def_set(scope_map_.get(var->id_get()));
            var->def_set(scope_map_.get(var->id_get()));
        }
    }

    void Binder::operator()(ast::AssignExpr& e)
    {
        e.rvalue_get()->accept(*this);

        ast::IdVar* var = dynamic_cast<ast::IdVar*> (e.lvalue_get());

        if (!var)
            e.lvalue_get()->accept(*this);
        else
        {
            if (!scope_map_.get(var->id_get()))
                scope_map_.add(var->id_get(), &e);
            else
            {
                var->def_set(scope_map_.get(var->id_get()));
                e.def_set(scope_map_.get(var->id_get()));
            }
        }
    }

    void Binder::operator()(ast::IdVar& ast)
    {
        if (in_class_ && ast.id_get() == "self")
            return;

        if (!scope_map_.get(ast.id_get()))
            error_ << misc::Error::BIND
                   << ast.location_get() << ": unknown identifier "
                   << ast.id_get() << std::endl;
        else
        {
            ast.def_set(scope_map_.get(ast.id_get()));
        }
    }
} // namespace bind
