#ifndef AST_FWD_HH
# define AST_FWD_HH

namespace ast
{
    class Ast;
    class Stmt;

    class PassStmt;

    template <class T>
    class AnyList;

    typedef AnyList<Ast> AstList;
    typedef AnyList<Stmt> StmtList;
} // namespace ast

#endif /* !AST_FWD_HH */
