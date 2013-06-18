#ifndef AST_FWD_HH
# define AST_FWD_HH

namespace ast
{
    class Ast;

    class Stmt;
    class PassStmt;
    class BreakStmt;
    class ContinueStmt;
    class ExprStmt;

    class Expr;
    class OpExpr;
    class UnaryExpr;
    class NumeralExpr;

    template <class T>
    class AnyList;

    typedef AnyList<Ast> AstList;
    typedef AnyList<Stmt> StmtList;
} // namespace ast

#endif /* !AST_FWD_HH */
