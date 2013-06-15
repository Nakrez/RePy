%require "2.4"
%skeleton "glr.cc"

%code requires
{
#include <string>
#include <iostream>

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
        TOK_IDENTIFIER      "identifier"
        TOK_NUMBER          "number"
        TOK_SEMICOLON       ";"
        TOK_COMA            ","
        TOK_COLON           ":"
        TOK_RBRACKET        "("
        TOK_LBRACKET        ")"
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
        TOK_LE              "<="
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

%%

program:
       | input_file
       ;

input_file: "newline"
          | stmt
          | input_file stmt
          | input_file "newline"
          ;

funcdef: "def" "identifier" parameters ":" suite
       | "def" "idenfifier" parameters ":" suite
       ;

parameters: "(" ")"
          | "(" typedargslist ")"
          ;

typedargslist: tfpdef tfpdef_test_list
             | tfpdef "=" test tfpdef_test_list
             | tfpdef tfpdef_test_list ","
             | tfpdef "=" test tfpdef_test_list ","

             | tfpdef tfpdef_test_list "," "*" tfpdef_test_list
             | tfpdef tfpdef_test_list "," "*" tfpdef tfpdef_test_list
             | tfpdef tfpdef_test_list "," "*" tfpdef_test_list "," "**" tfpdef
             | tfpdef tfpdef_test_list "," "*" tfpdef tfpdef_test_list "," "**" tfpdef

             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef_test_list
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef tfpdef_test_list
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef_test_list "," "**" tfpdef
             | tfpdef "=" test tfpdef_test_list "," "*" tfpdef tfpdef_test_list "," "**" tfpdef

             | tfpdef tfpdef_test_list "," "**" tfpdef
             | tfpdef "=" test tfpdef_test_list "," "**" tfpdef

             | "*" tfpdef_test_list
             | "*" tfpdef tfpdef_test_list
             | "*" tfpdef_test_list "," "**" tfpdef
             | "*" tfpdef tfpdef_test_list "," "**" tfpdef

             | "**" tfpdef

tfpdef_test_list:
                | tfpdef_test_list_internal
                ;

tfpdef_test_list_internal: "," tfpdef
                         | "," tfpdef "=" test
                         | tfpdef_test_list_internal "," tfpdef "=" test
                         | tfpdef_test_list_internal "," tfpdef
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

tfpdef: "identifier" ":" test
      ;

vfpdef: "identifier"
      ;

stmt: simple_stmt
    | compound_stmt
    ;

simple_stmt:
          small_stm_list "newline"
          | small_stm_list ";" "newline"
          ;

small_stm_list:
          small_stmt
          | simple_stmt ";" small_stmt
          ;

small_stmt : expr_stmt
           | del_stmt
           | pass_stmt
           | flow_stmt
           | import_stmt
           | global_stmt
           | nonlocal_stmt
           | assert_stmt
           ;

expr_stmt: testlist_star_expr augassign yield_expr
         | testlist_star_expr augassign testlist
         | testlist_star_expr expr_simple_assign
         | testlist_star_expr
         ;

testlist_star_expr: test_or_star
                  | test_or_star ","
                  | test_or_star test_star_list
                  | test_or_star test_star_list ","
                  ;

expr_simple_assign: "=" yield_expr
                  | "=" testlist_star_expr
                  | expr_simple_assign "=" yield_expr
                  | expr_simple_assign "=" testlist_star_expr
                  ;

augassign: "+="
         | "-="
         | "*="
         | "/="
         | "%="
         | "&="
         | "|="
         | "^="
         | "<<="
         | ">>="
         | "**="
         | "//="
         ;

del_stmt: "del" exprlist
        ;

pass_stmt: "pass"
         ;

flow_stmt: break_stmt
         | continue_stmt
         | return_stmt
         | raise_stmt
         | yield_stmt
         ;

break_stmt: "break"
          ;

continue_stmt: "continue"
             ;

return_stmt: "return"
           | "return" testlist
           ;

yield_stmt: yield_expr
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

compound_stmt: if_stmt
             | while_stmt
             | for_stmt
             | try_stmt
             | with_stmt
             | funcdef
             | classdef
             /*| decorated*/
             ;

if_stmt: "if" test ":" suite
       | "if" test ":" suite elif_list
       | "if" test ":" suite else_stmt
       | "if" test ":" suite elif_list else_stmt
       ;

elif_list: "elif" test ":" suite
         | elif_list "elif" test ":" suite
         ;

else_stmt: "else" ":" suite
         ;

while_stmt: "while" test ":" suite
          | "while" test ":" suite "else" ":" suite
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
     | "newline" "indent" stmt_list "dedent"
     ;

stmt_list: stmt
         | stmt_list stmt
         ;

dot_list: "."
        | "..."
        | dot_list "."
        | dot_list "..."
        ;

testlist: testlist_list
        | testlist_list ","
        ;

test: or_test
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

or_test: and_test
       | and_test or_test_list
       ;

or_test_list: "or" and_test
            | or_test_list "or" and_test
            ;

and_test: not_test
        | not_test and_test_list
        ;

and_test_list: "and" not_test
             | and_test_list "and" not_test
             ;

not_test: "not" not_test
        | comparaison
        ;

comparaison: expr
           | expr comparaison_list
           ;

comparaison_list: comp_op expr
                | comparaison_list comp_op expr
                ;

comp_op: "<"
       | ">"
       | "=="
       | ">="
       | "<="
       | "!="
       | "in"
       | "not" "in"
       | "is"
       | "is" "not"
       ;

star_expr: "*" expr
         ;

expr: xor_expr
    | xor_expr bor_list
    ;

bor_list: "|" xor_expr
        | bor_list "|" xor_expr
        ;

xor_expr: and_expr
        | xor_expr_list
        ;

xor_expr_list: "^" and_expr
             | xor_expr_list "^" and_expr
             ;

and_expr: shift_expr
        | shift_expr and_expr_list
        ;

and_expr_list: "&" shift_expr
             | and_expr_list "&" shift_expr
             ;

shift_expr: arith_expr
          | arith_expr shift_expr_list
          ;

shift_expr_list: "<<" arith_expr
               | ">>" arith_expr
               | shift_expr_list "<<" arith_expr
               | shift_expr_list ">>" arith_expr
               ;

arith_expr: term
          | term arith_expr_list
          ;

arith_expr_list: "+" term
               | "-" term
               | arith_expr_list "+" term
               | arith_expr_list "-" term
               ;

term: factor
    | factor term_list
    ;

term_content: "*" factor
            | "/" factor
            | "%" factor
            | "//" factor
            ;

term_list: term_content
         | term_list term_content
         ;

factor: power
      | "+" factor
      | "-" factor
      | "~" factor
      ;

power: atom
     | atom "**" factor
     | atom trailer_list
     | atom trailer_list "**" factor
     ;

trailer_list: trailer
            | trailer_list trailer
            ;

atom: "(" yield_expr ")"
    | "(" testlist_comp ")"
    | "[" testlist_comp "]"
    | "{" dictorsetmaker "}"
    | "identifier"
    | "number"
    | string_list
    | "..."
    | "none"
    | "true"
    | "false"
    ;

string_list: "string"
           | string_list "string"
           ;

testlist_comp: test_or_star comp_for_test_star
             ;

comp_for_test_star: comp_for
                  | comp_for ","
                  | test_star_list
                  | test_star_list ","
                  ;

test_star_list: "," test
              | "," star_expr
              | test_star_list "," test
              | test_star_list "," star_expr
              ;

test_or_star: test
            | star_expr
            ;

testlist_list: test
             | testlist_list "," test
             ;

trailer: "(" ")"
       | "(" arglist ")"
       | "[" subscriptlist "]"
       | "." "identifier"
       ;

subscriptlist: subscript
             | subscript ";"
             | "subscript" subscript_list
             | "subscript" subscript_list ";"
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
       | argument ","
       | argument_coma_last_list argument
       | argument_coma_last_list argument ","

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
                       | argument_coma_last_list argument ","
                       ;

argument_coma_first_list: "," argument
                        | argument_coma_first_list "," argument
                        ;

argument: test
        | test comp_for
        | test "=" test
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

yield_expr: "yield"
          | "yield" yield_arg
          ;

yield_arg: "from" test
         | testlist
         ;
%%

void yy::tpy_parser::error(const yy::tpy_parser::location_type& l,
                           const std::string& m)
{
    driver.error_get() << misc::Error::PARSE
                       << l << ":" << m << std::endl;
}
