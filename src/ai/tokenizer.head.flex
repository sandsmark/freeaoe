%{
    #include "gen/enums.h"
%}
%option case-insensitive
%option noyywrap
%option yylineno
%option c++
%option yyclass="ai::ScriptTokenizer"
%{
    #include "ScriptLoader.h"
    #include "ScriptTokenizer.h"
    #include "grammar.gen.tab.hpp"
    #include "location.hh"

    static ai::location loc;

    #define YY_USER_ACTION loc.step(); loc.columns(yyleng);

    #undef  YY_DECL
    #define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex(ai::ScriptLoader &driver)

    #define yyterminate() return ai::ScriptParser::make_ScriptEnd(loc);

    #define RET_TOKEN(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, loc);
    #define RET_TOKEN_ENUM(token_name, enum_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, ai::enum_name, loc);
    #define RET_STRING(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, yytext, loc);
    #define RET_INT(token_name) return ai::ScriptParser::symbol_type(ai::ScriptParser::token::token_name, atoi(yytext), loc);

%}


symbolname  [a-zA-Z]+[a-zA-Z-]*
string      \"[^"\r\n]*\"
number      [0-9]+
comment     ;.*
blank   [ \t]+

%%

{comment}
{blank}
