#include <cloner/ast-cloner.hh>
#include <ast/all.hh>

namespace cloner
{
    AstCloner::AstCloner()
        : cloned_ast_(nullptr)
    {}

    AstCloner::~AstCloner()
    {}

    ast::Ast* AstCloner::cloned_ast_get()
    {
        return cloned_ast_;
    }

    void AstCloner::operator()(ast::AstList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(ast::StmtList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(ast::ExprList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(ast::PassStmt& ast)
    {
        cloned_ast_ = new ast::PassStmt(ast.location_get());
    }

    void AstCloner::operator()(ast::BreakStmt& ast)
    {
        cloned_ast_ = new ast::BreakStmt(ast.location_get());
    }

    void AstCloner::operator()(ast::ContinueStmt& ast)
    {
        cloned_ast_ = new ast::ContinueStmt(ast.location_get());
    }

    void AstCloner::operator()(ast::ExprStmt& ast)
    {
        cloned_ast_ = new ast::ExprStmt(clone(ast.expr_get()));
    }

    void AstCloner::operator()(ast::IfStmt& ast)
    {
        ast::Expr* cond = clone(ast.cond_get());
        ast::Stmt* true_stmt = clone(ast.true_stmt_get());
        ast::Stmt* else_stmt = clone(ast.else_stmt_get());

        cloned_ast_ = new ast::IfStmt(ast.location_get(), cond, true_stmt,
                                      else_stmt);
    }

    void AstCloner::operator()(ast::WhileStmt& ast)
    {
        ast::Expr* cond = clone(ast.cond_get());
        ast::Stmt* loop = clone(ast.loop_get());

        cloned_ast_ = new ast::WhileStmt(ast.location_get(), cond, loop);
    }

    void AstCloner::operator()(ast::ReturnStmt& ast)
    {
        ast::Expr* ret_value = clone(ast.ret_value_get());

        cloned_ast_ = new ast::ReturnStmt(ast.location_get(), ret_value);
    }

    void AstCloner::operator()(ast::FunctionDec& ast)
    {
        ast::ExprList* args = nullptr;
        ast::Stmt* body = clone(ast.body_get());

        if (ast.args_get())
            args = clone_list(*ast.args_get());

        ast::FunctionDec* f = new ast::FunctionDec(ast.location_get(),
                                                   ast.name_get(), args, body);

        f->type_set(ast.type_get());
        f->to_generate_set(ast.to_generate_get());

        cloned_ast_ = f;
    }

    void AstCloner::operator()(ast::ModuleStmt& ast)
    {
        ast::AstList* content = clone(ast.content_get());

        cloned_ast_ = new ast::ModuleStmt(ast.location_get(), ast.name_get(),
                                          content);
    }

    void AstCloner::operator()(ast::OpExpr& ast)
    {
        ast::Expr* lexpr = clone(ast.left_expr_get());
        ast::Expr* rexpr = clone(ast.right_expr_get());

        ast::OpExpr* e = new ast::OpExpr(ast.location_get(), lexpr,
                                         ast.op_get(), rexpr);

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::UnaryExpr& ast)
    {
        ast::Expr* expr = clone(ast.expr_get());

        ast::UnaryExpr* e = new ast::UnaryExpr(ast.location_get(),
                                               ast.op_get(), expr);

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::AssignExpr& ast)
    {
        ast::Expr* lvalue = clone(ast.lvalue_get());
        ast::Expr* rvalue = clone(ast.rvalue_get());

        ast::AssignExpr* e = new ast::AssignExpr(ast.location_get(), lvalue,
                                                 rvalue);

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::NumeralExpr& ast)
    {
        ast::NumeralExpr* e = new ast::NumeralExpr(ast.location_get(),
                                                   ast.value_get());

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::StringExpr& ast)
    {
        ast::StringExpr* e = new ast::StringExpr(ast.location_get(),
                                                 ast.str_get());

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::YieldExpr& ast)
    {
        ast::Expr* ret_value = clone(ast.ret_value_get());

        ast::YieldExpr* e = new ast::YieldExpr(ast.location_get(), ret_value);

        e->type_set(ast.type_get());

        cloned_ast_ = e;
    }

    void AstCloner::operator()(ast::StarExpr& ast)
    {
        ast::Expr* e = clone(ast.expr_get());

        ast::StarExpr* se = new ast::StarExpr(ast.location_get(), e);

        se->type_set(ast.type_get());

        cloned_ast_ = se;
    }

    void AstCloner::operator()(ast::DoubleStarExpr& ast)
    {
        ast::Expr* e = clone(ast.expr_get());

        ast::DoubleStarExpr* de = new ast::DoubleStarExpr(ast.location_get(),
                                                         e);

        de->type_set(ast.type_get());

        cloned_ast_ = de;
    }

    void AstCloner::operator()(ast::IdVar& ast)
    {
        ast::IdVar* v = new ast::IdVar(ast.location_get(), ast.id_get());

        v->type_set(ast.type_get());
        v->global_set(ast.global_get());

        cloned_ast_ = v;
    }

    void AstCloner::operator()(ast::FunctionVar& ast)
    {
        ast::Var* var = clone(ast.var_get());
        ast::ExprList* params = nullptr;

        if (ast.params_get())
            params = clone_list(*ast.params_get());

        ast::FunctionVar* v = new ast::FunctionVar(ast.location_get(), var,
                                                   params);

        v->type_set(ast.type_get());

        cloned_ast_ = v;
    }
}
