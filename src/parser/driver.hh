#ifndef PARSER_DRIVER_HH
# define PARSER_DRIVER_HH

# include <stack>
# include <string>

# include <misc/error.hh>

# include <parser/parser.hh>

# include <ast/fwd.hh>

# include <cloner/ast-cloner.hh>

# define YY_DECL                                        \
    yy::tpy_parser::token_type yylex(                   \
            yy::tpy_parser::semantic_type* yylval,      \
            yy::tpy_parser::location_type* yylloc,      \
            parser::Driver& driver)

YY_DECL;

struct yy_buffer_state;

namespace parser
{
    class Driver
    {
        public:
            Driver();
            ~Driver();

            misc::Error& error_get();

            ast::Ast* parse_file(const std::string& filename);

            void ast_set(ast::Ast* ast);
            const std::string& file_get() const;

        private:
            void scan_begin();
            void scan_end();

        private:
            std::stack<yy_buffer_state*> states_;
            std::string file_;
            misc::Error error_;
            ast::Ast* ast_;
    };
}

#endif /* !PARSER_DRIVER_HH */
