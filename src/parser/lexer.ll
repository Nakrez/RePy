%{
#include <stack>
#include <parser/driver.hh>
#include <parser/parser.hh>

std::stack<int> indent_levels;
int cur_indent = 0;
char string_start;
bool empty = false;

# undef yywrap
# define yywrap() 1
# define yyterminate() return token::END

# define TAB_SIZE 8
%}

%option noyywrap noinput batch stack noyy_top_state

%{
# define YY_USER_ACTION yylloc->columns(yyleng);
# define YY_USER_INIT   indent_levels.push(0);      \
                        yy_push_state(indent);
%}

%x indent string escaped simple_comment multi_comment

%%
%{
    yylloc->step();
%}

%{
    typedef yy::tpy_parser::token token;
%}

<indent>" "     {
                    yylloc->step();
                    ++cur_indent;
                }
<indent>\t      {
                    cur_indent = (cur_indent + TAB_SIZE) & ~(TAB_SIZE + 1);
                }
<indent>\n      {
                    cur_indent = 0;
                    yylloc->lines();
                }
<indent>#       {
                    empty = true;
                    cur_indent = 0;
                    yy_pop_state();
                    yy_push_state(simple_comment);
                }
<indent>\"\"\"  {
                    cur_indent = 0;
                    yy_push_state(multi_comment);
                }
<indent>.       {
                    if (cur_indent == indent_levels.top())
                    {
                        unput(*yytext);
                        yy_pop_state();
                    }
                    else if (cur_indent > indent_levels.top())
                    {
                        indent_levels.push(cur_indent);
                        unput(*yytext);
                        yy_pop_state();
                        return token::TOK_INDENT;
                    }
                    else
                    {
                        indent_levels.pop();
                        if (cur_indent > indent_levels.top())
                        {
                            driver.error_get() << misc::Error::SCAN
                                               << *yylloc
                                               << ": indentation error"
                                               << std::endl;
                        }
                        else if (cur_indent == indent_levels.top())
                        {
                            unput(*yytext);
                            yy_pop_state();
                            return token::TOK_DEDENT;
                        }
                        else
                        {
                            unput(*yytext);
                            return token::TOK_DEDENT;
                        }
                    }
                }
<indent><<EOF>> {
                    if (indent_levels.top() == 0)
                        yyterminate();
                    else
                    {
                        indent_levels.pop();
                        return token::TOK_DEDENT;
                    }
                }

<string>\"      {
                    if (string_start == '"')
                    {
                        yy_pop_state();
                        return token::TOK_STRING;
                    }
                }
<string>'       {
                    if (string_start == '\'')
                    {
                        yy_pop_state();
                        return token::TOK_STRING;
                    }
                }
<string>\\      { yy_push_state(escaped); }
<string>.       { }

<escaped>\\    { yy_pop_state(); }
<escaped>\n    { yylloc->lines(); yy_pop_state(); }
<escaped>'     { yy_pop_state(); }
<escaped>\"    { yy_pop_state(); }
<escaped>a     { yy_pop_state(); }
<escaped>b     { yy_pop_state(); }
<escaped>f     { yy_pop_state(); }
<escaped>n     { yy_pop_state(); }
<escaped>r     { yy_pop_state(); }
<escaped>t     { yy_pop_state(); }
<escaped>v     { yy_pop_state(); }
<escaped>[0-7]{3}      { yy_pop_state(); }
<escaped>x[0-9A-F]{2}  { yy_pop_state(); }
<escaped>.     { driver.error_get() << misc::Error::SCAN
                                    << *yylloc << ":"
                                    << "Unknown escaped : " << yytext
                                    << std::endl;
        }

<simple_comment>.    { }
<simple_comment>\n   {
                        yy_pop_state();
                        yylloc->lines();
                        yy_push_state(indent);
                        if (!empty)
                            return token::TOK_NEWLINE;
                     }

<multi_comment>.     { }
<multi_comment>\"\"\" { yy_pop_state(); }
<multi_comment>\n     { yylloc->lines(); }

\"\"\"      { yy_push_state(multi_comment); }
"#"         {
                cur_indent = 0;
                yy_push_state(simple_comment);
                empty = false;
            }
\"          { string_start = '"'; yy_push_state(string); }
\'          { string_start = '\''; yy_push_state(string); }
"."         { return token::TOK_DOT; }
";"         { return token::TOK_SEMICOLON; }
","         { return token::TOK_COMA; }
,\n         { yylloc->lines(); return token::TOK_COMA; }
":"         { return token::TOK_COLON; }
"("         { return token::TOK_RPAR; }
")"         { return token::TOK_LPAR; }
"["         { return token::TOK_RBRACKET; }
"]"         { return token::TOK_LBRACKET; }
"{"         { return token::TOK_RBRACE; }
"}"         { return token::TOK_LBRACE; }
"="         { return token::TOK_ASSIGN; }
"+="        { return token::TOK_PLUS_ASSIGN; }
"-="        { return token::TOK_MINUS_ASSIGN; }
"*="        { return token::TOK_MUL_ASSIGN; }
"/="        { return token::TOK_DIV_ASSIGN; }
"%="        { return token::TOK_MOD_ASSIGN; }
"&="        { return token::TOK_AND_ASSIGN; }
"|="        { return token::TOK_OR_ASSIGN; }
"^="        { return token::TOK_XOR_ASSIGN; }
"<<="       { return token::TOK_LSHIFT_ASSIGN; }
">>="       { return token::TOK_RSHIFT_ASSIGN; }
"**="       { return token::TOK_POW_ASSIGN; }
"//="       { return token::TOK_FDIV_ASSIGN; }
"<"         { return token::TOK_LT; }
">"         { return token::TOK_GT; }
"=="        { return token::TOK_EQ; }
">="        { return token::TOK_GE; }
"<="        { return token::TOK_LE; }
"!="        { return token::TOK_NE; }
"<>"        { return token::TOK_NE; }

"+"         { return token::TOK_PLUS; }
"-"         { return token::TOK_MINUS; }
"*"         { return token::TOK_MUL; }
"/"         { return token::TOK_DIV; }
"%"         { return token::TOK_MOD; }
"//"        { return token::TOK_FDIV; }
"**"        { return token::TOK_POW; }
"|"         { return token::TOK_BOR; }
"^"         { return token::TOK_XOR; }
"&"         { return token::TOK_BAND; }
"~"         { return token::TOK_COMPL; }
"<<"        { return token::TOK_LSHIFT; }
">>"        { return token::TOK_RSHIFT; }

"False"     { return token::TOK_FALSE; }
"None"      { return token::TOK_NONE; }
"True"      { return token::TOK_TRUE; }
"and"       { return token::TOK_AND; }
-[ \t]*\n       { yylloc->lines(); return token::TOK_MINUS; }
and[ \t]*\n       { yylloc->lines(); return token::TOK_AND; }
or[ \t]*\n       { yylloc->lines(); return token::TOK_OR; }
\n[ \t]*and       { yylloc->lines(); return token::TOK_AND; }
\n[ \t]*or       { yylloc->lines(); return token::TOK_OR; }
"as"        { return token::TOK_AS; }
"assert"    { return token::TOK_ASSERT; }
"break"     { return token::TOK_BREAK; }
"class"     { return token::TOK_CLASS; }
"continue"  { return token::TOK_CONTINUE; }
"def"       { return token::TOK_DEF; }
"del"       { return token::TOK_DEL; }
"elif"      { return token::TOK_ELIF; }
"else"      { return token::TOK_ELSE; }
"except"    { return token::TOK_EXCEPT; }
"finally"   { return token::TOK_FINALLY; }
"for"       { return token::TOK_FOR; }
"from"      { return token::TOK_FROM; }
"global"    { return token::TOK_GLOBAL; }
"if"        { return token::TOK_IF; }
"import"    { return token::TOK_IMPORT; }
"in"        { return token::TOK_IN; }
"is"        { return token::TOK_IS; }
"lambda"    { return token::TOK_LAMBDA; }
"nonlocal"  { return token::TOK_NONLOCAL; }
"not"       { return token::TOK_NOT; }
"or"        { return token::TOK_OR; }
"pass"      { return token::TOK_PASS; }
"raise"     { return token::TOK_RAISE; }
"return"    { return token::TOK_RETURN; }
"try"       { return token::TOK_TRY; }
"while"     { return token::TOK_WHILE; }
"with"      { return token::TOK_WITH; }
"yield"     { return token::TOK_YIELD; }

[ \t]+          { }
\n              {
                    cur_indent = 0;
                    yylloc->lines();
                    yy_push_state(indent);
                    return token::TOK_NEWLINE;
                }

__[A-Za-z_][A-Za-z0-9_]*  { return token::TOK_IDENTIFIER; }
__[A-Za-z_][A-Za-z0-9_]*__  { return token::TOK_IDENTIFIER; }
_[A-Za-z_][A-Za-z0-9_]* { return token::TOK_IDENTIFIER; }
[A-Za-z_][A-Za-z0-9_]*  { return token::TOK_IDENTIFIER; }
[0-9]+                  {
                            yylval->num_val = atoi(yytext);
                            return token::TOK_NUMBER;
                        }

.       { driver.error_get() << misc::Error::SCAN
                             << *yylloc << ":" << "Unknown char : " << yytext
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
