%require "2.4"
%skeleton "glr.cc"

%code requires
{
#include <string>
#include <iostream>
#include <ast/all.hh>

    namespace parser
    {
        class Driver;
    }
}

%define parser_class_name "tpy_parser"
%debug
%defines
%verbose
%error-verbose
%glr-parser
%locations

%parse-param { parser::Driver& driver }
%lex-param   { parser::Driver& driver }
%pure-parser

%union
{
    double num_val;
    std::string* str_val;

    ast::Ast* ast_val;
    ast::AstList* ast_list;

    ast::Stmt* stmt_val;
    ast::StmtList* stmt_list;

    ast::IfStmt* if_val;

    ast::Expr* expr_val;
    ast::AssignExpr* assexpr_val;

    ast::ExprList* expr_list_val;

    ast::OpExpr* op_expr_val;
    ast::OpExpr::Operator op_val;

    ast::StringExpr* str_expr_val;

    ast::Var* var_val;
}

%code
{
#include <parser/driver.hh>
}

%token  END     0           "end_of_file"
        TOK_INDENT          "indent"
        TOK_DEDENT          "dedent"
        TOK_NEWLINE         "newline"
        TOK_FALSE           "false"
        TOK_NONE            "none"
        TOK_TRUE            "true"
        TOK_AND             "and"
        TOK_AS              "as"
        TOK_ASSERT          "assert"
        TOK_BREAK           "break"
        TOK_CLASS           "class"
        TOK_CONTINUE        "continue"
        TOK_DEF             "def"
        TOK_DEL             "del"
        TOK_ELIF            "elif"
        TOK_ELSE            "else"
        TOK_EXCEPT          "except"
        TOK_FINALLY         "finally"
        TOK_FOR             "for"
        TOK_FROM            "from"
        TOK_GLOBAL          "global"
        TOK_IF              "if"
        TOK_IMPORT          "import"
        TOK_IN              "in"
        TOK_IS              "is"
        TOK_LAMBDA          "lambda"
        TOK_NONLOCAL        "nonlocal"
        TOK_NOT             "not"
        TOK_OR              "or"
        TOK_PASS            "pass"
        TOK_RAISE           "raise"
        TOK_RETURN          "return"
        TOK_TRY             "try"
        TOK_WHILE           "while"
        TOK_WITH            "with"
        TOK_YIELD           "yield"
        TOK_DOT             "."
        TOK_SEMICOLON       ";"
        TOK_COMA            ","
        TOK_COLON           ":"
        TOK_RPAR            "("
        TOK_LPAR            ")"
        TOK_RBRACKET        "["
        TOK_LBRACKET        "]"
        TOK_RBRACE          "{"
        TOK_LBRACE          "}"
        TOK_ASSIGN          "="
        TOK_PLUS_ASSIGN     "+="
        TOK_MINUS_ASSIGN    "-="
        TOK_MUL_ASSIGN      "*="
        TOK_DIV_ASSIGN      "/="
        TOK_MOD_ASSIGN      "%="
        TOK_AND_ASSIGN      "&="
        TOK_OR_ASSIGN       "|="
        TOK_XOR_ASSIGN      "^="
        TOK_LSHIFT_ASSIGN   "<<="
        TOK_RSHIFT_ASSIGN   ">>="
        TOK_POW_ASSIGN      "**="
        TOK_FDIV_ASSIGN     "//="
        TOK_LT              "<"
        TOK_GT              ">"
        TOK_EQ              "=="
        TOK_GE              ">="
        TOK_LE              "<="a
        TOK_NE              "!="
        TOK_PLUS            "+"
        TOK_MINUS           "-"
        TOK_MUL             "*"
        TOK_DIV             "/"
        TOK_MOD             "%"
        TOK_FDIV            "//"
        TOK_POW             "**"
        TOK_BOR             "|"
        TOK_XOR             "^"
        TOK_BAND            "&"
        TOK_COMPL           "~"
        TOK_LSHIFT          "<<"
        TOK_RSHIFT          ">>"

%token<str_val>
        TOK_STRING          "string"
        TOK_IDENTIFIER      "identifier"

%token<num_val>
        TOK_NUMBER          "number"

%type<ast_list> input_file

%type<stmt_list> small_stm_list stmt_list
%type<stmt_val> small_stmt pass_stmt flow_stmt break_stmt continue_stmt
                expr_stmt stmt simple_stmt suite compound_stmt if_stmt
                else_stmt while_stmt funcdef return_stmt yield_stmt
%type<if_val>   elif_list

%type<expr_val> test_or_star test testlist_star_expr or_test and_test not_test
                comparaison expr xor_expr and_expr shift_expr arith_expr
                term factor power atom argument yield_expr yield_arg
%type<expr_list_val> arglist argument_coma_last_list typedargslist
                     tfpdef_test_list tfpdef_test_list_internal parameters
                     testlist testlist_list

%type<str_expr_val> string_list

%type<op_expr_val>  or_test_list and_test_list comparaison_list bor_list
                    xor_expr_list and_expr_list shift_expr_list arith_expr_list
                    term_list term_content

%type<op_val> comp_op augassign

%type<assexpr_val> expr_simple_assign

%type<var_val> trailer trailer_list tfpdef

%%

program:
       | input_file
       {
        std::string name = std::string(basename(driver.file_get().c_str()));
        std::replace(name.begin(), name.end(), '-', '_');
        driver.ast_set(new ast::ModuleStmt(@1, name.substr(0, name.size() - 3),
                                           $1));
       }
       ;

input_file: stmt
          {
            $$ = new ast::AstList(@1);
            $$->push_back($1);
          }
          | input_file stmt
          {
            $$ = $1;
            $$->push_back($2);
          }
          ;

funcdef: "def" "identifier" parameters ":" suite
       {
        $$ = new ast::FunctionDec(@1, *$2, $3, $5);
        delete $2;
       }
       ;

parameters: "(" ")" { $$ = nullptr; }
          | "(" typedargslist ")" { $$ = $2; }
          ;

typedargslist: tfpdef tfpdef_test_list
             {
                $$ = $2;
                $$->push_front($1);
             }
             | tfpdef "=" test tfpdef_test_list
             {
                $$ = $4;
                $$->push_front(new ast::AssignExpr(@1, $1, $3));
             }
             | tfpdef tfpdef_test_list ","
             {
                $$ = $2;
                $$->push_front($1);
             }
             | tfpdef "=" test tfpdef_test_list ","
             {
                $$ = $4;
                $$->push_front(new ast::AssignExpr(@1, $1, $3));
             }
             | tfpdef tfpdef_test_list "," "*" tfpdef_test_list
             | tfpdef tfpdef_test_list "," "*" tfpdef tfpdef_test_list
             {
                $$ = $2;
                $$->push_front($1);
                $$->push_back(new ast::StarExpr(@4, $5));
                $$->splice($6);
             }
             | tfpdef tfpdef_test_list "," "*" tfpdef_test_list "," "**" tfpdef
             | tfpdef tfpdef_test_list "," "*" tfpdef tfpdef_test_list "," "**" tfpdef
             {
                $$ = $2;
                $$->push_front($1);
                $$->push_back(new ast::StarExpr(@4, $5));
                $$->splice($6);
                $$->push_back(new ast::DoubleStarExpr(@8, $9));
             }
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef_test_list
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef tfpdef_test_list
             {
                $$ = $4;
                $$->push_front(new ast::AssignExpr(@1, $1, $3));
                $$->push_back(new ast::StarExpr(@6, $7));
                $$->splice($8);
             }
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef_test_list "," "**" tfpdef
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef tfpdef_test_list "," "**" tfpdef
             {
                $$ = $4;
                $$->push_front(new ast::AssignExpr(@1, $1, $3));
                $$->push_back(new ast::StarExpr(@6, $7));
                $$->splice($8);
                $$->push_back(new ast::DoubleStarExpr(@10, $11));
             }
             | tfpdef tfpdef_test_list "," "**" tfpdef
             {
                $$ = $2;
                $$->push_front($1);
                $$->push_back(new ast::DoubleStarExpr(@4, $5));
             }
             | tfpdef "=" test tfpdef_test_list "," "**" tfpdef
             {
                $$ = $4;
                $$->push_front(new ast::AssignExpr(@1, $1, $3));
                $$->push_back(new ast::DoubleStarExpr(@6, $7));
             }
             | "*" tfpdef_test_list
             | "*" tfpdef tfpdef_test_list
             {
                $$ = $3;
                $$->push_front(new ast::StarExpr(@1, $2));
             }
             | "*" tfpdef_test_list "," "**" tfpdef
             | "*" tfpdef tfpdef_test_list "," "**" tfpdef
             {
                $$ = $3;
                $$->push_front(new ast::StarExpr(@1, $2));
                $$->push_back(new ast::DoubleStarExpr(@5, $6));
             }
             | "**" tfpdef
             {
                $$ = new ast::ExprList(@$);
                $$->push_front(new ast::DoubleStarExpr(@1, $2));
             }

tfpdef_test_list: { $$ = new ast::ExprList(@$); }
                | tfpdef_test_list_internal { $$ = $1; }
                ;

tfpdef_test_list_internal: "," tfpdef
                         {
                            $$ = new ast::ExprList(@1);
                            $$->push_back($2);
                         }
                         | "," tfpdef "=" test
                         {
                            $$ = new ast::ExprList(@1);
                            $$->push_back(new ast::AssignExpr(@2, $2, $4));
                         }
                         | tfpdef_test_list_internal "," tfpdef "=" test
                         {
                            $$ = $1;
                            $$->push_back(new ast::AssignExpr(@3, $3, $5));
                         }
                         | tfpdef_test_list_internal "," tfpdef
                         {
                            $$ = $1;
                            $$->push_back($3);
                         }
                         ;

varargslist: vfpdef vfpdef_test_list
           | vfpdef "=" test vfpdef_test_list
           | vfpdef vfpdef_test_list ","
           | vfpdef "=" test vfpdef_test_list ","

           | vfpdef vfpdef_test_list "," "*" vfpdef_test_list
           | vfpdef vfpdef_test_list "," "*" vfpdef vfpdef_test_list
           | vfpdef vfpdef_test_list "," "*" vfpdef_test_list "," "**" vfpdef
           | vfpdef vfpdef_test_list "," "*" vfpdef vfpdef_test_list "," "**" vfpdef

           | vfpdef "=" test vfpdef_test_list "," "*" vfpdef_test_list
           | vfpdef "=" test vfpdef_test_list "," "*" vfpdef vfpdef_test_list
           | vfpdef "=" test vfpdef_test_list "," "*" vfpdef_test_list "," "**" vfpdef
           | vfpdef "=" test vfpdef_test_list "," "*" vfpdef vfpdef_test_list "," "**" vfpdef

           | vfpdef vfpdef_test_list "," "**" vfpdef
           | vfpdef "=" test vfpdef_test_list "," "**" vfpdef

           | "*" vfpdef_test_list
           | "*" vfpdef vfpdef_test_list
           | "*" vfpdef_test_list "," "**" vfpdef
           | "*" vfpdef vfpdef_test_list "," "**" vfpdef

           | "**" vfpdef
           ;

vfpdef_test_list:
                | vfpdef_test_list_internal
                ;

vfpdef_test_list_internal: "," vfpdef
                         | "," vfpdef "=" test
                         | vfpdef_test_list_internal "," vfpdef "=" test
                         | vfpdef_test_list_internal "," vfpdef
                         ;

tfpdef: "identifier"
      {
        $$ = new ast::IdVar(@1, *$1);
        delete $1;
      }
      | "identifier" ":" test
      ;

vfpdef: "identifier"
      ;

stmt: simple_stmt { $$ = $1; }
    | compound_stmt { $$ = $1; }
    ;

simple_stmt:
          small_stm_list "newline" { $$ = $1; }
          | small_stm_list ";" "newline" { $$ = $1; }
          ;

small_stm_list:
          small_stmt
          {
            $$ = new ast::StmtList(@1);
            $$->push_back($1);
          }
          | small_stm_list ";" small_stmt
          {
            $$ = $1;
            $$->push_back($3);
          }
          ;

small_stmt : expr_stmt { $$ = $1; }
           | del_stmt
           | pass_stmt { $$ = $1; }
           | flow_stmt { $$ = $1; }
           | import_stmt
           | global_stmt
           | nonlocal_stmt
           | assert_stmt
           ;

expr_stmt: testlist_star_expr augassign yield_expr { exit(20); }
         /* FIXME: Originally test was testlist */
         | testlist_star_expr augassign test
         {
            /* We use a little cloner because future rvalue cant be the same
            as lvalue */
            cloner::AstCloner cloner;
            cloner.visit($1);

            ast::Expr* e = nullptr;
            ast::Expr* lexpr = dynamic_cast<ast::Expr*> (cloner.cloned_ast_get());

            e = new ast::AssignExpr(@1, $1, new ast::OpExpr(@2, lexpr, $2, $3));

            $$ = new ast::ExprStmt(e);
         }
         | testlist_star_expr expr_simple_assign
         {
            $$ = new ast::ExprStmt($2);
            $2->lvalue_set($1);
         }
         | testlist_star_expr { $$ = new ast::ExprStmt($1); }
         ;

testlist_star_expr: test_or_star { $$ = $1; }
                  | test_or_star ","
                  | test_or_star test_star_list
                  | test_or_star test_star_list ","
                  ;

expr_simple_assign: "=" yield_expr
                  | "=" testlist_star_expr
                  { $$ = new ast::AssignExpr(@1, nullptr, $2); }
                  | expr_simple_assign "=" yield_expr
                  | expr_simple_assign "=" testlist_star_expr
                  { $$ = new ast::AssignExpr(@1, $1, $3); }
                  ;

augassign: "+=" { $$ = ast::OpExpr::PLUS; }
         | "-=" { $$ = ast::OpExpr::MINUS; }
         | "*=" { $$ = ast::OpExpr::MULT; }
         | "/=" { $$ = ast::OpExpr::DIV; }
         | "%=" { $$ = ast::OpExpr::MOD; }
         | "&=" { $$ = ast::OpExpr::BIT_AND; }
         | "|=" { $$ = ast::OpExpr::BIT_OR; }
         | "^=" { $$ = ast::OpExpr::XOR; }
         | "<<=" { $$ = ast::OpExpr::LSHIFT; }
         | ">>=" { $$ = ast::OpExpr::RSHIFT; }
         | "**=" { $$ = ast::OpExpr::POW; }
         | "//=" { $$ = ast::OpExpr::FDIV; }
         ;

del_stmt: "del" exprlist
        ;

pass_stmt: "pass" { $$ = new ast::PassStmt(@1); }
         ;

flow_stmt: break_stmt { $$ = $1; }
         | continue_stmt { $$ = $1; }
         | return_stmt { $$ = $1; }
         | raise_stmt
         | yield_stmt { $$ = $1; }
         ;

break_stmt: "break" { $$ = new ast::BreakStmt(@1); }
          ;

continue_stmt: "continue" { $$ = new ast::ContinueStmt(@1); }
             ;

return_stmt: "return" { $$ = new ast::ReturnStmt(@1, nullptr); }
           /*| "return" testlist { $$ = new ast::ReturnStmt(@1, $2); }*/
           | "return" test { $$ = new ast::ReturnStmt(@1, $2); }
           ;

yield_stmt: yield_expr { $$ = new ast::ExprStmt($1); }
          ;

raise_stmt: "raise"
          | "raise" test
          | "raise" test "from" test
          ;

import_stmt: import_name
           | import_from
           ;

import_name: "import" dotted_as_names
           ;

import_from: "from" dotted_name import_part
           | "from" dot_list dotted_name import_part
           | "from" dot_list import_part
           ;

import_part: "import" "*"
           | "import" "(" import_as_names ")"
           | "import" import_as_names
           ;

import_as_name: "identifier"
              | "identifier" "as" "identifier"
              ;

dotted_as_name: dotted_name
              | dotted_name "as" "identifier"
              ;

import_as_names: import_as_name
               | import_as_name ","
               | import_as_name import_as_name_list
               | import_as_name import_as_name_list ","
               ;

import_as_name_list: "," import_as_name
                   | import_as_name_list "," import_as_name
                   ;

dotted_as_names: dotted_as_name
               | dotted_as_name dotted_as_name_list
               ;

dotted_as_name_list: "," dotted_as_name
                   | dotted_as_name_list "," dotted_as_name
                   ;

dotted_name: "identifier"
           | dotted_name "." "identifier"
           ;

coma_name: "identifier"
         | coma_name "," "identifier"
         ;

global_stmt: "global" coma_name
           ;

nonlocal_stmt: "nonlocal" coma_name
             ;

assert_stmt: "assert" test
           | "assert" test "," test
           ;

compound_stmt: if_stmt { $$ = $1; }
             | while_stmt { $$ = $1; }
             | for_stmt
             | try_stmt
             | with_stmt
             | funcdef
             | classdef
             /*| decorated*/
             ;

if_stmt: "if" test ":" suite { $$ = new ast::IfStmt(@1, $2, $4, nullptr); }
       | "if" test ":" suite elif_list { $$ = new ast::IfStmt(@1, $2, $4, $5); }
       | "if" test ":" suite else_stmt { $$ = new ast::IfStmt(@1, $2, $4, $5); }
       | "if" test ":" suite elif_list else_stmt
       {
        $$ = new ast::IfStmt(@1, $2, $4, $5);
        $5->set_else_stmt($6);
       }
       ;

elif_list: "elif" test ":" suite { $$ = new ast::IfStmt(@1, $2, $4, nullptr); }
         | elif_list "elif" test ":" suite
         {
            $$ = $1;
            $1->set_else_stmt(new ast::IfStmt(@1, $3, $5, nullptr));
         }
         ;

else_stmt: "else" ":" suite { $$ = $3; }
         ;

while_stmt: "while" test ":" suite { $$ = new ast::WhileStmt(@1, $2, $4); }
          | "while" test ":" suite "else" ":" suite
          {
            $$ = new ast::IfStmt(@1, $2, new ast::WhileStmt(@1, $2, $4), $7);
          }
          ;

for_stmt: "for" exprlist "in" testlist ":" suite
        | "for" exprlist "in" testlist ":" suite "else" ":" suite
        ;

try_stmt: "try" ":" suite except_stmt
        | "try" "finally" ":" suite
        ;

except_stmt: except_list
           | except_list "else" ":" suite
           | except_list "finally" ":" suite
           | except_list "else" ":" suite "finally" ":" suite
           ;

except_list: except_clause ":" suite
           | except_list except_clause ":" suite
           ;

with_stmt: "with" with_item ":" suite
         | "with" with_item with_item_list ":" suite
         ;

with_item_list: "," with_item
              | with_item_list "," with_item
              ;

with_item: test
         | test "as" expr
         ;

except_clause: "except"
             | "except" test
             | "except" test "as" "identifier"
             ;

suite: simple_stmt
     {
        $$ = $1;
     }
     | "newline" "indent" stmt_list "dedent"
     {
        $$ = $3;
     }
     ;

stmt_list: stmt
         {
            if (dynamic_cast<ast::StmtList*> ($1))
                $$ = dynamic_cast<ast::StmtList*> ($1);
            else
            {
                $$ = new ast::StmtList(@1);
                $$->push_back($1);
            }
         }
         | stmt_list stmt
         {
            $$ = $1;

            if (dynamic_cast<ast::StmtList*> ($2))
                $1->splice(dynamic_cast<ast::StmtList*> ($2));
            else
                $1->push_back($2);
         }
         ;

dot_list: "."
        | "..."
        | dot_list "."
        | dot_list "..."
        ;

testlist: testlist_list { $$ = $1; }
        | testlist_list "," { $$ = $1; }
        ;

test: or_test { $$ = $1; }
    | or_test "if" or_test "else" test
    | lambdef
    ;

test_nocond: or_test
           | lambdef_nocond
           ;

lambdef: "lambda" ":" test
       | "lambda" varargslist ":" test
       ;

lambdef_nocond: "lambda" ":" test_nocond
              | "lambda" varargslist ":" test_nocond
              ;

or_test: and_test { $$ = $1; }
       | and_test or_test_list
       {
        $$ = $2;
        $2->set_left_expr($1);
       }
       ;

or_test_list: "or" and_test
            {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::BOOL_OR,
                                     $2);
            }
            | or_test_list "or" and_test
            {
                $$ = new ast::OpExpr(@1,
                                     $1,
                                     ast::OpExpr::Operator::BOOL_OR,
                                     $3);
            }
            ;

and_test: not_test { $$ = $1; }
        | not_test and_test_list
        {
            $$ = $2;
            $2->set_left_expr($1);
        }
        ;

and_test_list: "and" not_test
             {
                 $$ = new ast::OpExpr(@1,
                                      nullptr,
                                      ast::OpExpr::Operator::BOOL_AND,
                                      $2);
             }
             | and_test_list "and" not_test
             {
                 $$ = new ast::OpExpr(@1,
                                      $1,
                                      ast::OpExpr::Operator::BOOL_AND,
                                      $3);
             }
             ;

not_test: "not" not_test {
                            $$ = new ast::UnaryExpr(@1,
                                                    ast::UnaryExpr::UNARY_NOT,
                                                    $2);
                         }
        | comparaison { $$ = $1; }
        ;

comparaison: expr { $$ = $1; }
           | expr comparaison_list
           {
            $$ = $2;
            $2->set_left_expr($1);
           }
           ;

comparaison_list: comp_op expr { $$ = new ast::OpExpr(@1, nullptr, $1, $2); }
                | comparaison_list comp_op expr
                { $$ = new ast::OpExpr(@1, $1, $2, $3); }
                ;

comp_op: "<" { $$ = ast::OpExpr::Operator::LT; }
       | ">" { $$ = ast::OpExpr::Operator::GT; }
       | "==" { $$ = ast::OpExpr::Operator::EQ; }
       | ">=" { $$ = ast::OpExpr::Operator::GE; }
       | "<=" { $$ = ast::OpExpr::Operator::LE; }
       | "!=" { $$ = ast::OpExpr::Operator::NEQ; }
       | "in" { $$ = ast::OpExpr::Operator::IN; }
       | "not" "in" { $$ = ast::OpExpr::Operator::NOT_IN; }
       | "is" { $$ = ast::OpExpr::Operator::IS; }
       | "is" "not" { $$ = ast::OpExpr::Operator::IS_NOT; }
       ;

star_expr: "*" expr
         ;

expr: xor_expr { $$ = $1; }
    | xor_expr bor_list
    {
        $$ = $2;
        $2->set_left_expr($1);
    }
    ;

bor_list: "|" xor_expr
        {
            $$ = new ast::OpExpr(@1,
                                 nullptr,
                                 ast::OpExpr::Operator::BIT_OR,
                                 $2);
        }
        | bor_list "|" xor_expr
        {
            $$ = new ast::OpExpr(@1,
                                 $1,
                                 ast::OpExpr::Operator::BIT_OR,
                                 $3);
        }
        ;

xor_expr: and_expr { $$ = $1; }
        | and_expr xor_expr_list
        {
            $$ = $2;
            $2->set_left_expr($1);
        }
        ;

xor_expr_list: "^" and_expr
             {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::XOR,
                                     $2);
             }
             | xor_expr_list "^" and_expr
             {
                $$ = new ast::OpExpr(@1,
                                     $1,
                                     ast::OpExpr::Operator::XOR,
                                     $3);
             }
             ;

and_expr: shift_expr { $$ = $1; }
        | shift_expr and_expr_list
        {
            $$ = $2;
            $2->set_left_expr($1);
        }
        ;

and_expr_list: "&" shift_expr
             {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::BIT_AND,
                                     $2);
             }
             | and_expr_list "&" shift_expr
             {
                $$ = new ast::OpExpr(@1,
                                     $1,
                                     ast::OpExpr::Operator::BIT_AND,
                                     $3);
             }
             ;

shift_expr: arith_expr { $$ = $1; }
          | arith_expr shift_expr_list
          {
            $$ = $2;
            $2->set_left_expr($1);
          }
          ;

shift_expr_list: "<<" arith_expr
               {
                 $$ = new ast::OpExpr(@1,
                                      nullptr,
                                      ast::OpExpr::Operator::LSHIFT,
                                      $2);
               }
               | ">>" arith_expr
               {
                 $$ = new ast::OpExpr(@1,
                                      nullptr,
                                      ast::OpExpr::Operator::RSHIFT,
                                      $2);
               }
               | shift_expr_list "<<" arith_expr
               {
                $$ = new ast::OpExpr(@1,
                                     $1,
                                     ast::OpExpr::Operator::LSHIFT,
                                     $3);
               }
               | shift_expr_list ">>" arith_expr
               {
                $$ = new ast::OpExpr(@1,
                                     $1,
                                     ast::OpExpr::Operator::RSHIFT,
                                     $3);
               }
               ;

arith_expr: term { $$ = $1; }
          | term arith_expr_list
          {
            $$ = $2;
            $2->set_left_expr($1);
          }
          ;

arith_expr_list: "+" term
               {
                 $$ = new ast::OpExpr(@1,
                                      nullptr,
                                      ast::OpExpr::Operator::PLUS,
                                      $2);
               }
               | "-" term
               {
                 $$ = new ast::OpExpr(@1,
                                      nullptr,
                                      ast::OpExpr::Operator::MINUS,
                                      $2);
               }
               | arith_expr_list "+" term
               {
                 $$ = new ast::OpExpr(@1,
                                      $1,
                                      ast::OpExpr::Operator::PLUS,
                                      $3);
               }
               | arith_expr_list "-" term
               {
                 $$ = new ast::OpExpr(@1,
                                      $1,
                                      ast::OpExpr::Operator::MINUS,
                                      $3);
               }
               ;

term: factor { $$ = $1; }
    | factor term_list
    {
        $$ = $2;
        $2->set_left_expr($1);
    }
    ;

term_content: "*" factor
            {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::MULT,
                                     $2);
            }
            | "/" factor
            {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::DIV,
                                     $2);
            }
            | "%" factor
            {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::MOD,
                                     $2);
            }
            | "//" factor
            {
                $$ = new ast::OpExpr(@1,
                                     nullptr,
                                     ast::OpExpr::Operator::FDIV,
                                     $2);
            }
            ;

term_list: term_content { $$ = $1; }
         | term_list term_content
         {
            $$ = $2;
            $2->set_left_expr($1);
         }
         ;

factor: power { $$ = $1; }
      | "+" factor { $$ = new ast::UnaryExpr(@1, ast::UnaryExpr::UNARY_PLUS, $2); }
      | "-" factor { $$ = new ast::UnaryExpr(@1, ast::UnaryExpr::UNARY_MINUS, $2); }
      | "~" factor { $$ = new ast::UnaryExpr(@1, ast::UnaryExpr::UNARY_COMPLEMENT, $2); }
      ;

power: atom { $$ = $1; }
     | atom "**" factor
     {
        $$ = new ast::OpExpr(@1,
                             $1,
                             ast::OpExpr::Operator::POW,
                             $3);
     }

     | atom trailer_list
     {
        ast::Var* v = dynamic_cast<ast::Var*> ($1);

        if (v)
            $2->add_component(v);
        else
            driver.error_get() << misc::Error::PARSE
                               << @1 << ": Syntax error" << std::endl;

        $$ = $2;
     }
     | atom trailer_list "**" factor
     ;

trailer_list: trailer { $$ = $1; }
            | trailer_list trailer
            {
                $$ = $2;
                $$->add_component($1);
            }
            ;

atom: "(" ")"
    | "(" yield_expr ")"
    | "(" testlist_comp ")"
    | "[" "]"
    | "[" testlist_comp "]"
    | "{" "}"
    | "{" dictorsetmaker "}"
    | "identifier" { $$ = new ast::IdVar(@1, std::string(*$1)); delete $1; }
    | "number" { $$ = new ast::NumeralExpr(@1, $1); }
    | string_list { $$ = $1; }
    | "..."
    | "none"
    | "true" { $$ = new ast::NumeralExpr(@1, 1); }
    | "false" { $$ = new ast::NumeralExpr(@1, 0); }
    ;

string_list: "string"
           {
            $$ = new ast::StringExpr(@1, std::string(*$1));
            delete $1;
           }
           | string_list "string"
           {
            $$ = $1;
            $1->append(std::string(*$2));
            delete $2;
           }
           ;

testlist_comp: test_or_star comp_for_test_star
             ;

comp_for_test_star: comp_for
                  | test_star_list_comp
                  ;

test_star_list_comp:
                   | ","
                   | test_star_list_comp_internal
                   | test_star_list_comp_internal ","
                   ;

test_star_list_comp_internal: "," test
                            | "," star_expr
                            | test_star_list "," test
                            | test_star_list "," star_expr
                            ;

test_star_list: "," test
              | "," star_expr
              | test_star_list "," test
              | test_star_list "," star_expr
              ;

test_or_star: test { $$ = $1; }
            | star_expr
            ;

testlist_list: test
             {
                $$ = new ast::ExprList(@1);
                $$->push_back($1);
             }
             | testlist_list "," test
             {
                $$ = $1;
                $1->push_back($3);
             }
             ;

trailer: "(" ")"
       { $$ = new ast::FunctionVar(@1, nullptr, nullptr); }
       | "(" arglist ")"
       { $$ = new ast::FunctionVar(@1, nullptr, $2); }
       | "[" subscriptlist "]"
       | "." "identifier"
       ;

subscriptlist: subscript
             | subscript ","
             | "subscript" subscript_list
             | "subscript" subscript_list ","
             ;

subscript_list: "," subscript
              | subscript "," subscript
              ;

subscript: test
         | ":"
         | test ":"
         | ":" test
         | ":" sliceop
         | test ":" test
         | test ":" sliceop
         | ":" test sliceop
         | test ":" test sliceop
         ;

sliceop: ":"
       | ":" test
       ;

exprlist: expr
        | star_expr
        | expr ","
        | star_expr ","
        | expr expr_star_list
        | star_expr expr_star_list
        | expr expr_star_list ","
        | star_expr expr_star_list ","
        ;

expr_star_list: "," expr
              | "," star_expr
              | expr_star_list "," expr
              | expr_star_list "," star_expr
              ;

dictorsetmaker: test ":" test comp_for
              | test ":" test
              | test ":" test ","
              | test ":" test list_test_test
              | test ":" test list_test_test ","
              | test comp_for
              | test
              | test ","
              | test coma_test_list
              | test coma_test_list ","
              ;

list_test_test: "," test ":" test
              | list_test_test "," test ":" test
              ;

coma_test_list: "," test
              | coma_test_list "," test
              ;

classdef: "class" "identifier" ":" suite
        | "class" "identifier" "(" ")" ":" suite
        | "class" "identifier" "(" arglist ")" suite
        ;

arglist: argument
       {
        $$ = new ast::ExprList(@1);
        $$->push_back($1);
       }
       | argument ","
       {
        $$ = new ast::ExprList(@1);
        $$->push_back($1);
       }
       | argument_coma_last_list argument
       {
        $$ = $1;
        $$->push_back($2);
       }
       | argument_coma_last_list argument ","
       {
        $$ = $1;
        $$->push_back($2);
       }
       | "*" test
       | "*" test argument_coma_first_list
       | "*" test argument_coma_first_list "," "**" test
       | "*" test "," "**" test
       | argument_coma_last_list "*" test
       | argument_coma_last_list "*" test argument_coma_first_list
       | argument_coma_last_list "*" test argument_coma_first_list "," "**" test
       | argument_coma_last_list "*" test "," "**" test

       | argument_coma_last_list "**" test
       | "**" test
       ;

argument_coma_last_list: argument ","
                       {
                        $$ = new ast::ExprList(@1);
                        $$->push_back($1);
                       }
                       | argument_coma_last_list argument ","
                       {
                        $$ = $1;
                        $$->push_back($2);
                       }
                       ;

argument_coma_first_list: "," argument
                        | argument_coma_first_list "," argument
                        ;

argument: test { $$ = $1; }
        | test comp_for
        | test "=" test { $$ = new ast::AssignExpr(@1, $1, $3); }
        ;

comp_iter: comp_for
         | comp_if
         ;

comp_for: "for" exprlist "in" or_test
        | "for" exprlist "in" or_test comp_iter
        ;

comp_if: "if" test_nocond
       | "if" test_nocond comp_iter
       ;

yield_expr: "yield" { $$ = new ast::YieldExpr(@1, nullptr); }
          | "yield" yield_arg { $$ = new ast::YieldExpr(@1, $2); }
          ;

yield_arg: "from" test
         | testlist { $$ = $1; }
         ;
%%

void yy::tpy_parser::error(const yy::tpy_parser::location_type& l,
                           const std::string& m)
{
    driver.error_get() << misc::Error::PARSE
                       << l << ":" << m << std::endl;
}
