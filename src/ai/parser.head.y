%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
extern int yyparse(void);
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int number;
	const char *string;
}

%destructor { free($$); $$ = NULL; } String SymbolName;


%token<number> Number
%token<string> String
%token<string> SymbolName

%token OpenParen CloseParen
%token RuleStart ConditionActionSeparator

//%token LessThan LessOrEqual GreaterThan GreaterOrEqual Equal Not Or
%token Not Or

%token LoadIfDefined Else EndIf

%token Space NewLine

%start aiscript
