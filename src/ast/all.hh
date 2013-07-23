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
# include <ast/class-dec.hh>
# include <ast/module-stmt.hh>

// Expression
# include <ast/expr.hh>
# include <ast/unary-expr.hh>
# include <ast/op-expr.hh>
# include <ast/assign-expr.hh>
# include <ast/numeral-expr.hh>
# include <ast/string-expr.hh>
# include <ast/yield-expr.hh>
# include <ast/star-expr.hh>
# include <ast/double-star-expr.hh>

// Var
# include <ast/var.hh>
# include <ast/id-var.hh>
# include <ast/function-var.hh>
# include <ast/field-var.hh>

#endif /* !AST_ALL_HH */
