%%

aiscript:
    /* Empty */
    | rules ScriptEnd { printf("got script\n"); }
;

rules:
    rule { printf("got single rule\n"); }
    | rule rules { /*printf("got multiple rules\n");*/ }

rule:
    OpenParen RuleStart conditions ConditionActionSeparator actions CloseParen { printf("got rule\n====\n\n"); }

conditions:
    condition { $$ = $1; /* printf("got single condition\n");*/ }
    | condition conditions { $$ = driver.createAndCondition($1, $2); } /*printf("got multiple conditions\n");*/ }

condition:
    OpenParen conditiontype CloseParen { /*printf("condition\n");*/ }

conditiontype:
    Not condition { /*printf("got negated condition\n");*/ }
    | Or condition condition { $$ = driver.createOrCondition($2, $3); /*printf("got multiple or conditions\n"); */ }
    | fact { $$ = $1; /*printf("got fact\n"); */ }


actions:
    singleaction {  /*printf("got single action\n");*/ }
    | singleaction actions {  /*printf("got multiple actions\n");*/ }

singleaction:
      OpenParen action CloseParen { $$ = $2; /*printf("got action without arguments\n");*/ }

