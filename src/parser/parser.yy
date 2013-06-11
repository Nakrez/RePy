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

%token  END     0       "end_of_file"
        TOK_DEF         "def"

%%

program:
       ;

%%

void yy::tpy_parser::error(const yy::tpy_parser::location_type& l,
                           const std::string& m)
{
    driver.error_get() << misc::Error::PARSE
                       << l << ":" << m << std::endl;
}
