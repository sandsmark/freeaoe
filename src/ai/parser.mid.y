%%

aiscript:
    /* Empty */
    | rules ScriptEnd { driver.addScript($1); printf("got script\n"); }
;

rules:
    rule { std::vector<std::shared_ptr<ai::AiRule>> ret; ret.push_back($1); $$ = ret; printf("got single rule\n"); }
    | rule rules { $2.push_back($1); $$ = $2; /*printf("got multiple rules\n");*/ }

rule:
    OpenParen RuleStart conditions ConditionActionSeparator actions CloseParen { $$ = driver.createRule($3, $5); }

conditions:
    condition { std::vector<std::shared_ptr<ai::Condition>> ret; ret.push_back($1); $$ = ret; /* printf("got single condition\n");*/ }
    | condition conditions { $2.push_back($1); $$ = $2; } /*printf("got multiple conditions\n");*/

condition:
    OpenParen conditiontype CloseParen { $$ = $2; /*printf("condition\n");*/ }

conditiontype:
    Not condition { $$ = driver.createNotCondition($2); /*printf("got negated condition\n");*/ }
    | Or condition condition { $$ = driver.createOrCondition($2, $3); /*printf("got multiple or conditions\n"); */ }
    | fact { $$ = $1; /*printf("got fact\n"); */ }


actions:
    singleaction { std::vector<std::shared_ptr<ai::Action>> ret; ret.push_back($1); $$ = ret; /*printf("got single action\n");*/ }
    | singleaction actions { $2.push_back($1); $$ = $2; /*printf("got multiple actions\n");*/ }

singleaction:
      OpenParen action CloseParen { $$ = $2; /*printf("got action without arguments\n");*/ }

