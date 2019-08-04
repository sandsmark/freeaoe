%option case-insensitive
%option noyywrap

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "parser.tab.h"

%}

symbolname  [a-zA-Z]+[a-zA-Z-]*
string      \"[^"\r\n]*\"
number      [0-9]+
comment     ;.*

%%

{comment}

"("                 { printf(" - open paren\n"); return OpenParen; }
")"                 { printf(" - close paren\n"); return CloseParen; }
"defrule"           { printf(" - defrule\n"); return RuleStart; }
"=>"                { printf(" - conditionactionseparator\n"); return ConditionActionSeparator; }

"not"                 { return Not; }
"or"                 { return Or; }

"<"                 { return LessThan; }
"less-than"         { return LessThan; }

"<="                { return LessOrEqual; }
"less-or-equal"     { return LessOrEqual; }

">"                 { return GreaterThan; }
"greater-than"      { return GreaterThan; }

">="                { return GreaterOrEqual; }
"greater-or-equal"  { return GreaterOrEqual; }

"=="                { return Equal; }
"equal"             { return Equal; }

"#load-if-defined"  { return LoadIfDefined; }
"#else"             { return Else; }
"#end-if"           { return EndIf; }

[\r\n]+

{symbolname}        { printf(" - symbol name %s\n", yytext); yylval.string = yytext; return SymbolName; }
{string}            { printf(" - string %s\n", yytext); yylval.string = yytext; return String; }
{number}            { printf(" - number %s\n", yytext); yylval.number = atoi(yytext); return Number; }

%%
