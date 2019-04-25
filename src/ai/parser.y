%{

#include <string>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int number;
	char *string;
}

%destructor { delete $$; $$ = nullptr; } String SymbolName;


%token<number> Number
%token<string> String
%token<string> SymbolName

%token OpenParen CloseParen
%token RuleStart ConditionActionSeparator

%token LessThan LessOrEqual GreaterThan GreaterOrEqual Equal Not

%token LoadIfDefined Else EndIf

%token Space NewLine

%start aiscript

%%

aiscript:
    /* Empty */
    | rules { printf("got script\n"); }
;

rules:
    rule { printf("got single rule\n"); }
    | rule rules { printf("got multiple rules\n"); }

rule:
    OpenParen RuleStart conditions ConditionActionSeparator actions CloseParen { printf("got rule\n====\n\n"); }

conditions:
    condition { printf("got single condition\n"); }
    | condition conditions { printf("got multiple conditions\n"); }

condition:
    OpenParen Not condition CloseParen { printf("got negated condition\n"); }
    | OpenParen SymbolName CloseParen { printf("got condition with symbol '%s'\n", $2); }
    | OpenParen SymbolName SymbolName CloseParen { printf("got condition with two symbols '%s' %s\n", $2, $3); }
    | OpenParen SymbolName comparison Number CloseParen { printf("got condition with comparison %s %d\n", $2, $4); }
    | OpenParen SymbolName comparison SymbolName CloseParen { printf("got condition with comparison %s %s\n", $2, $4); }
    | OpenParen SymbolName SymbolName comparison SymbolName CloseParen { printf("got condition with comparison %s %s %s\n", $2, $3, $5); }
    | OpenParen SymbolName SymbolName comparison Number CloseParen { printf("got condition with comparison %s %s %d\n", $2, $3, $5); }


comparison:
    LessThan { printf("got lessthan\n"); }
    | LessOrEqual { printf("got lessorequal\n"); }
    | GreaterThan { printf("got greaterthan\n"); }
    | GreaterOrEqual { printf("got greaterorequal\n"); }
    | Equal { printf("got equals\n"); }

actions:
    action { printf("got single action\n"); }
    | action  actions { printf("got multiple actions\n"); }

action:
    OpenParen SymbolName CloseParen { printf("got action %s without arguments\n", $2); }
    | OpenParen SymbolName String CloseParen { printf("got action %s with string %s\n", $2, $3); }
    | OpenParen SymbolName SymbolName Number CloseParen { printf("got action %s with symbol %s and number %d\n", $2, $3, $4); }
    | OpenParen SymbolName SymbolName CloseParen { printf("got action %s with symbol %s\n", $2, $3); }
    | OpenParen SymbolName Number CloseParen { printf("got action %s with number %d\n", $2, $3); }


%%

int main() {
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
