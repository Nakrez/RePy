#ifndef AST_DEFAULT_VISITOR_HXX
# define AST_DEFAULT_VISITOR_HXX

# include <ast/default-visitor.hh>

namespace ast
{
    template <template <typename> class Const>
    GenDefaultVisitor<Const>::~GenDefaultVisitor()
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<AstList>::type& ast)
    {
        for (auto e : ast.list_get())
            e->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<StmtList>::type& ast)
    {
        for (auto e : ast.list_get())
            e->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<ExprList>::type& ast)
    {
        for (auto e : ast.list_get())
            e->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<PassStmt>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<BreakStmt>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<ContinueStmt>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<ExprStmt>::type& s)
    {
        s.expr_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<IfStmt>::type& s)
    {
        s.cond_get()->accept(*this);
        s.true_stmt_get()->accept(*this);

        if (s.else_stmt_get())
            s.else_stmt_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<WhileStmt>::type& s)
    {
        s.cond_get()->accept(*this);
        s.loop_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<ReturnStmt>::type& s)
    {
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<ModuleStmt>::type& s)
    {
        s.content_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<FunctionDec>::type& s)
    {
        if (s.args_get())
            s.args_get()->accept(*this);
        s.body_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<OpExpr>::type& e)
    {
        e.left_expr_get()->accept(*this);
        e.right_expr_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<UnaryExpr>::type& e)
    {
        e.expr_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<AssignExpr>::type& e)
    {
        e.lvalue_get()->accept(*this);
        e.rvalue_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<NumeralExpr>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<StringExpr>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<YieldExpr>::type& s)
    {
        if (s.ret_value_get())
            s.ret_value_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<StarExpr>::type& s)
    {
        s.expr_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<DoubleStarExpr>::type& s)
    {
        s.expr_get()->accept(*this);
    }

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<IdVar>::type&)
    {}

    template <template <typename> class Const>
    void
    GenDefaultVisitor<Const>::operator()(typename Const<FunctionVar>::type& v)
    {
        v.var_get()->accept(*this);

        if (v.params_get())
            v.params_get()->accept(*this);
    }
} // namespace ast

#endif /* !AST_DEFAULT_VISITOR_HXX */
