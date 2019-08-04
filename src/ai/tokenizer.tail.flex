
"("                 RET_TOKEN(OpenParen)
")"                 RET_TOKEN(CloseParen)
"defrule"           RET_TOKEN(RuleStart)
"=>"                RET_TOKEN(ConditionActionSeparator)

"not"               RET_TOKEN(Not)
"or"                RET_TOKEN(Or)

"<"                 RET_TOKEN(RelOpLessThan)
"<="                RET_TOKEN(RelOpLessOrEqual)
">"                 RET_TOKEN(RelOpGreaterThan)
">="                RET_TOKEN(RelOpGreaterOrEqual)
"=="                RET_TOKEN(RelOpEqual)

"#load-if-defined"  RET_TOKEN(LoadIfDefined)
"#else"             RET_TOKEN(Else)
"#end-if"           RET_TOKEN(EndIf)

[\r\n]+

{symbolname}        RET_STRING(SymbolName)
{string}            RET_STRING(String)
{number}            RET_INT(Number)

%%
