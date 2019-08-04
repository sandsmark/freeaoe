%option case-insensitive
%option noyywrap
%option yylineno

%{
    //#include "ScriptLoader.h"
    //#include "ScriptTokenizer.h"
    #include "grammar.gen.tab.h"
    //#include "location.hh"

    //static ai::location loc;

    //#define YY_USER_ACTION loc.step(); loc.columns(yyleng);

    //#undef  YY_DECL
    //#define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex(ai::ScriptLoader &driver)

    //#define yyterminate() return ai::ScriptParser::make_ScriptEnd(loc);

    //#define RET_TOKEN(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, loc);
    //#define RET_STRING(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, yytext, loc);
    //#define RET_INT(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, atoi(yytext), loc); 

    #define RET_TOKEN(token_name) printf("%s\n", yytext); return token_name;
    #define RET_STRING(token_name) printf("%s\n", yytext); yylval.string = yytext; return String;
    #define RET_INT(token_name) printf("%s\n", yytext); yylval.number = atoi(yytext); return Number; 
%}



symbolname  [a-zA-Z]+[a-zA-Z-]*
string      \"[^"\r\n]*\"
number      [0-9]+
comment     ;.*
blank   [ \t]+

%%

{comment}
{blank}
