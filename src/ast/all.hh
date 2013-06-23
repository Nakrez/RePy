#ifndef AST_ALL_HH
# define AST_ALL_HH

# include <ast/fwd.hh>

# include <ast/ast.hh>
# include <ast/any-list.hh>

// Statement
# include <ast/stmt.hh>
# include <ast/pass-stmt.hh>
# include <ast/break-stmt.hh>
# include <ast/continue-stmt.hh>
# include <ast/expr-stmt.hh>
# include <ast/if-stmt.hh>
# include <ast/while-stmt.hh>
# include <ast/return-stmt.hh>
# include <ast/function-dec.hh>

// Expression
# include <ast/expr.hh>
# include <ast/unary-expr.hh>
# include <ast/op-expr.hh>
# include <ast/assign-expr.hh>
# include <ast/numeral-expr.hh>
# include <ast/string-expr.hh>

// Var
# include <ast/var.hh>
# include <ast/id-var.hh>
# include <ast/function-var.hh>

#endif /* !AST_ALL_HH */
