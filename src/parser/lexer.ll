%{
#include <parser/driver.hh>
#include <parser/parser.hh>

# undef yywrap
# define yywrap() 1
# define yyterminate() return token::END
%}

%option nounput noyywrap noinput batch stack noyy_top_state

%{
# define YY_USER_ACTION yylloc->columns(yyleng);
%}

%%
%{
    yylloc->step();
%}

%{
    typedef yy::tpy_parser::token token;
%}

"def"   { return token::TOK_DEF; }

.       { driver.error_get() << misc::Error::SCAN
                             << "Unknown char : " << yytext
                             << std::endl;
        }
%%

namespace parser
{
    void Driver::scan_begin()
    {
        static bool first = true;
        if (first)
        {
            first = false;
            // Reclaim all the memory allocated by Flex.
            std::atexit ((void (*) ()) yylex_destroy);
        }

        states_.push (YY_CURRENT_BUFFER);

        if (this->file_.empty() || this->file_ == "-")
            yyin = stdin;
        else if (!(yyin = fopen(this->file_.c_str(), "r")))
        {
            std::cerr << "cannot open " << this->file_ << std::endl;
            exit(EXIT_FAILURE);
        }
        yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
    }

    void Driver::scan_end()
    {
        if (yyin)
            fclose (yyin);
        yy_delete_buffer (YY_CURRENT_BUFFER);
        yy_switch_to_buffer (states_.top ());
        states_.pop ();
    }
}
