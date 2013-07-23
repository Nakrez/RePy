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
    class IfStmt;
    class WhileStmt;
    class ReturnStmt;
    class FunctionDec;
    class ClassDec;
    class ModuleStmt;

    class Expr;
    class OpExpr;
    class UnaryExpr;
    class AssignExpr;
    class NumeralExpr;
    class StringExpr;
    class YieldExpr;
    class StarExpr;
    class DoubleStarExpr;

    class Var;
    class IdVar;
    class FunctionVar;

    template <class T>
    class AnyList;

    typedef AnyList<Ast> AstList;
    typedef AnyList<Stmt> StmtList;
    typedef AnyList<Expr> ExprList;
} // namespace ast

#endif /* !AST_FWD_HH */
