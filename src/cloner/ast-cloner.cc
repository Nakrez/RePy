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

    void AstCloner::operator()(const ast::AstList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(const ast::StmtList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(const ast::ExprList& ast)
    {
        cloned_ast_ = clone_list(ast);
    }

    void AstCloner::operator()(const ast::PassStmt& ast)
    {
        cloned_ast_ = new ast::PassStmt(ast.location_get());
    }

    void AstCloner::operator()(const ast::BreakStmt& ast)
    {
        cloned_ast_ = new ast::BreakStmt(ast.location_get());
    }

    void AstCloner::operator()(const ast::ContinueStmt& ast)
    {
        cloned_ast_ = new ast::ContinueStmt(ast.location_get());
    }

    void AstCloner::operator()(const ast::ExprStmt& ast)
    {
        cloned_ast_ = new ast::ExprStmt(clone(ast.expr_get()));
    }

    void AstCloner::operator()(const ast::IfStmt& ast)
    {
        ast::Expr* cond = clone(ast.cond_get());
        ast::Stmt* true_stmt = clone(ast.true_stmt_get());
        ast::Stmt* else_stmt = clone(ast.else_stmt_get());

        cloned_ast_ = new ast::IfStmt(ast.location_get(), cond, true_stmt,
                                      else_stmt);
    }

    void AstCloner::operator()(const ast::WhileStmt& ast)
    {
        ast::Expr* cond = clone(ast.cond_get());
        ast::Stmt* loop = clone(ast.loop_get());

        cloned_ast_ = new ast::WhileStmt(ast.location_get(), cond, loop);
    }

    void AstCloner::operator()(const ast::ReturnStmt& ast)
    {
        ast::Expr* ret_value = clone(ast.ret_value_get());

        cloned_ast_ = new ast::ReturnStmt(ast.location_get(), ret_value);
    }

    void AstCloner::operator()(const ast::FunctionDec& ast)
    {
        ast::ExprList* args = nullptr;
        ast::Stmt* body = clone(ast.body_get());

        if (ast.args_get())
            args = clone_list(*ast.args_get());

        cloned_ast_ = new ast::FunctionDec(ast.location_get(), ast.name_get(),
                                           args, body);
    }

    void AstCloner::operator()(const ast::OpExpr& ast)
    {
        ast::Expr* lexpr = clone(ast.left_expr_get());
        ast::Expr* rexpr = clone(ast.right_expr_get());

        cloned_ast_ = new ast::OpExpr(ast.location_get(), lexpr, ast.op_get(),
                                      rexpr);
    }

    void AstCloner::operator()(const ast::UnaryExpr& ast)
    {
        ast::Expr* expr = clone(ast.expr_get());

        cloned_ast_ = new ast::UnaryExpr(ast.location_get(), ast.op_get(),
                                         expr);
    }

    void AstCloner::operator()(const ast::AssignExpr& ast)
    {
        ast::Expr* lvalue = clone(ast.lvalue_get());
        ast::Expr* rvalue = clone(ast.rvalue_get());

        cloned_ast_ = new ast::AssignExpr(ast.location_get(), lvalue, rvalue);
    }

    void AstCloner::operator()(const ast::NumeralExpr& ast)
    {
        cloned_ast_ = new ast::NumeralExpr(ast.location_get(),
                                           ast.value_get());
    }

    void AstCloner::operator()(const ast::StringExpr& ast)
    {
        cloned_ast_ = new ast::StringExpr(ast.location_get(), ast.str_get());
    }

    void AstCloner::operator()(const ast::YieldExpr& ast)
    {
        ast::Expr* ret_value = clone(ast.ret_value_get());

        cloned_ast_ = new ast::YieldExpr(ast.location_get(), ret_value);
    }

    void AstCloner::operator()(const ast::StarExpr& ast)
    {
        ast::Expr* e = clone(ast.expr_get());

        cloned_ast_ = new ast::StarExpr(ast.location_get(), e);
    }

    void AstCloner::operator()(const ast::DoubleStarExpr& ast)
    {
        ast::Expr* e = clone(ast.expr_get());

        cloned_ast_ = new ast::DoubleStarExpr(ast.location_get(), e);
    }

    void AstCloner::operator()(const ast::IdVar& ast)
    {
        cloned_ast_ = new ast::IdVar(ast.location_get(), ast.id_get());
    }

    void AstCloner::operator()(const ast::FunctionVar& ast)
    {
        ast::Var* var = clone(ast.var_get());
        ast::ExprList* params = nullptr;

        if (ast.params_get())
            params = clone_list(*ast.params_get());

        cloned_ast_ = new ast::FunctionVar(ast.location_get(), var, params);
    }
}
