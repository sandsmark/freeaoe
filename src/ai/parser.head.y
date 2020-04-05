%{
    #include "gen/enums.h"
%}

%skeleton "lalr1.cc"
%require  "3.4"

%defines
%define api.namespace { ai }
%define api.parser.class {ScriptParser}
%define api.value.type variant
%define api.token.constructor
%define parse.assert true
%define parse.error verbose
%locations


%param {ai::ScriptLoader &driver}
%parse-param {ai::ScriptTokenizer &scanner}

%code requires {
    #include "gen/enums.h"
    #include "AiRule.h"
    #include "AiScript.h"
    #include <memory>

    namespace ai {
        class ScriptTokenizer;
        class ScriptLoader;
    }

    #ifndef YYDEBUG
        #define YYDEBUG 1
    #endif

    #define YY_NULLPTR nullptr
}


%{
    #include <cassert>
    #include <fstream>
    #include <iostream>

    #include "ScriptLoader.h"
    #include "ScriptTokenizer.h"

    #include "grammar.gen.tab.hpp"
    #include "location.hh"

    #undef yylex
    #define yylex scanner.yylex
%}

//%destructor { free($$); $$ = NULL; } String SymbolName;


%token<int> Number
%token<std::string> String
%token<std::string> SymbolName

%token OpenParen CloseParen
%token RuleStart ConditionActionSeparator

//%token LessThan LessOrEqual GreaterThan GreaterOrEqual Equal Not Or
%token Not Or

%token LoadIfDefined Else EndIf

%token Space NewLine

%token ScriptEnd 0 "end of script"

%start aiscript

%type <std::shared_ptr<ai::Condition>> conditiontype
%type <std::shared_ptr<ai::Condition>> condition
%type <std::vector<std::shared_ptr<ai::Condition>>> conditions // TODO create vectors
%type <std::shared_ptr<ai::Condition>> fact
%type <std::shared_ptr<ai::Action>> singleaction
%type <std::shared_ptr<ai::Action>> action
%type <std::vector<std::shared_ptr<ai::Action>>> actions // TODO: create vectors
%type <std::shared_ptr<ai::AiRule>> rule
%type <std::vector<std::shared_ptr<ai::AiRule>>> rules
