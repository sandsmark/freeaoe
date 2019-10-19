#!/bin/bash -e

######## TODO: rewrite this in c++ or something other sane

mkdir -p gen
rm -f gen/rules
rm -f gen/tokens.flex
rm -f gen/tokens.y
rm -f gen/enums.h
rm -f gen/parser-types.y
rm -f gen/union.y

printf "#pragma once\n\nnamespace ai {\n\n" >> gen/enums.h


ALL_TYPES="    fact\n"
LVAL_ENUMS=""
PARSER_TYPES=""
UNION_MEMBERS=""
while read -r -a LINE; do

    TYPE="${LINE[0]}"
    TYPE="${TYPE#"<"}" # chop off <
    TYPE="${TYPE%">"}" # chop off > at the end
    TYPE=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"$TYPE")

    LINE=("${LINE[@]:1}")
    RULEMATCHES=""
    ENUMS=""
    TOKENLIST=""
    for i in "${!LINE[@]}"; do
        TOKEN="${LINE[$i]}"

        if [[ "${TOKEN:0:1}" = "#" ]]; then
            break
        fi

        if [[ "${TOKEN}" = "%Number%" ]]; then
            if [[ "${i}" -lt 1 ]]; then
                RULEMATCHES+="    Number"
            else
                RULEMATCHES+="  | Number"
            fi
            continue
        fi
        RE='^[0-9].*?$'
        if [[ ! ${TOKEN} =~ $RE ]]; then
            TOKEN="${TOKEN}"
            #TOKEN="${TYPE}${TOKEN}"
        fi

        RE='^[a-zA-Z0-9-]+$'
        if [[ ! ${TOKEN} =~ $RE ]]; then
            continue
        fi
        NAME=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"$TOKEN")
        TOKENNAME="${TYPE}${NAME}"

        echo "\"${TOKEN}\"    { RET_TOKEN(${TOKENNAME}) }" >> gen/tokens.flex

        TOKENLIST+=" ${TOKENNAME}"
        if [[ "${i}" -lt 1 ]]; then
            RULEMATCHES+="    ${TOKENNAME}"
        else
            RULEMATCHES+="  | ${TOKENNAME}"
        fi
        RULEMATCHES+="  { \$\$ = ${TYPE}::${NAME}; }\n"
        #RULEMATCHES+="  { \$\$ = ${TYPE}::${NAME}; }\n"
        ENUMS+="    ${NAME},\n"
        LVAL_ENUMS+="    ${NAME},\n"
    done

    # Can't be arsed to do this properly
    if [[ "$TYPE" = "Age" ]]; then
        RULEMATCHES+="    | BuildingCastle { \$\$ = Age::CastleAge; } \n"
    fi

    if [[ -n "${RULEMATCHES}" ]]; then
        printf "${TYPE}:" | tr '[:upper:]' '[:lower:]' >> gen/rules
        printf "\n${RULEMATCHES}\n" >> gen/rules
    fi

    if [[ -n "${TOKENLIST}" ]]; then
        echo "%token${TOKENLIST}" >> gen/tokens.y
    fi
    if [[ -n "${ENUMS}" ]]; then
        #echo "enum class ${TYPE} {" >> gen/enums.h
        printf "enum class ${TYPE} {\n" >> gen/enums.h
        printf "${ENUMS}" >> gen/enums.h
        printf "};\n" >> gen/enums.h
    fi

    TYPELOWERCASE=$(tr '[:upper:]' '[:lower:]' <<<"$TYPE")
    if [[ -z "${ALL_TYPES}" ]]; then
        ALL_TYPES+="    ${TYPELOWERCASE}\n"
    else
        ALL_TYPES+="  | ${TYPELOWERCASE}\n"
    fi
    PARSER_TYPES+="%%type <${TYPE}> ${TYPELOWERCASE}\n"
    UNION_MEMBERS+="    ${TYPE} ${TYPELOWERCASE};\n"
done < lists/parameters.list

#printf "\nsymbolname:\n${ALL_TYPES}\n    " >> gen/rules

printf "enum class ParameterType {\n${LVAL_ENUMS}\n};\n" >> gen/enums.h

LVAL_ENUMS=""
ALL_ACTIONS=""
LAST_ACTION=""
while read -r -a LINE; do
    ACTION="${LINE[0]}"
    STRING="${ACTION}"
    ACTION=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"${ACTION}")

    ACTIONLOWERCASE=$(tr '[:upper:]' '[:lower:]' <<<"$ACTION")
    LINE=("${LINE[@]:1}")
    #RULEMATCHES=""
    if [[ "${LAST_ACTION}" = "${ACTION}" ]]; then
        RULEMATCHES="    |  ${ACTION}"
    else
        RULEMATCHES="${ACTIONLOWERCASE}:\n    ${ACTION}"
    fi
    ENUMS=""
    TOKENLIST=""
    for i in "${!LINE[@]}"; do
        TOKEN="${LINE[$i]}"

        if [[ "${TOKEN:0:1}" = "#" ]]; then
            break
        fi

        TOKEN="${TOKEN#"<"}" # chop off <
        TOKEN="${TOKEN%">"}" # chop off > at the end

        RE='^[a-zA-Z-]+$'
        if [[ ! ${TOKEN} =~ $RE ]]; then
            continue
        fi
        NAME=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"$TOKEN")
        TOKENNAME=$(tr '[:upper:]' '[:lower:]' <<<"$NAME")
        if [[ "${TOKENNAME}" = "string" ]]; then
            TOKENNAME="String"
        fi
        if [[ "${TOKENNAME}" = "number" ]]; then
            TOKENNAME="Number"
        fi

        RULEMATCHES+=" ${TOKENNAME}"
    done

    RULEMATCHES+=" { \$\$ = driver.createAction("
    # I'm too lazy to do this properly, so sue me
    if [[ "${#LINE[@]}" -eq "0" ]]; then
        RULEMATCHES+="\$1"
    elif [[ "${#LINE[@]}" -eq "1" ]]; then
        RULEMATCHES+="\$1, \$2"
    elif [[ "${#LINE[@]}" -eq "2" ]]; then
        RULEMATCHES+="\$1, \$2, \$3"
    elif [[ "${#LINE[@]}" -eq "3" ]]; then
        RULEMATCHES+="\$1, \$2, \$3, \$4"
    elif [[ "${#LINE[@]}" -eq "4" ]]; then
        RULEMATCHES+="\$1, \$2, \$3, \$4, \$5"
    fi
    RULEMATCHES+="); }\n"


    if [[ "$ACTION" != "$LAST_ACTION" ]]; then
        echo "\"${STRING}\"    { RET_TOKEN_ENUM(${ACTION}, ActionType::${ACTION}) }" >> gen/tokens.flex

        if [[ -z "${ALL_ACTIONS}" ]]; then
            ALL_ACTIONS+="    ${ACTIONLOWERCASE}\n"
        else
            ALL_ACTIONS+="  | ${ACTIONLOWERCASE}\n"
        fi

        LVAL_ENUMS+="    ${ACTION},\n"
        PARSER_TYPES+="%%type <ActionType> ${ACTION}\n"
        PARSER_TYPES+="%%type <std::shared_ptr<ai::Action>> ${ACTIONLOWERCASE}\n"
    fi

    echo "%token ${ACTION}" >> gen/tokens.y
    if [[ -n "${RULEMATCHES}" ]]; then
        printf "\n${RULEMATCHES}"  >> gen/rules
    fi

    LAST_ACTION="${ACTION}"
done < lists/actions.list

printf "\n"  >> gen/rules

printf "\naction:\n${ALL_ACTIONS}\n" >> gen/rules

printf "enum class ActionType {\n${LVAL_ENUMS}\n};\n" >> gen/enums.h

LVAL_ENUMS=""
ALL_FACTS=""
LAST_FACT=""
while read -r -a LINE; do
    FACT="${LINE[0]}"
    STRING="${FACT}"

    if [[ "$FACT" = "true" ]]; then
        FACT="trueval"
    fi
    if [[ "$FACT" = "false" ]]; then
        FACT="falseval"
    fi

    FACT=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"${FACT}")


    FACTLOWERCASE=$(tr '[:upper:]' '[:lower:]' <<<"$FACT")
    LINE=("${LINE[@]:1}")
    #RULEMATCHES=""

    if [[ "$FACT" = "$LAST_FACT" ]]; then
        RULEMATCHES="    | ${FACT}"
    else
        RULEMATCHES="\n${FACTLOWERCASE}:\n    ${FACT}"
    fi

    ENUMS=""
    TOKENLIST=""

    for i in "${!LINE[@]}"; do
        TOKEN="${LINE[$i]}"

        if [[ "${TOKEN:0:1}" = "#" ]]; then
            break
        fi

        TOKEN="${TOKEN#"<"}" # chop off <
        TOKEN="${TOKEN%">"}" # chop off > at the end

        RE='^[a-zA-Z-]+$'
        if [[ ! ${TOKEN} =~ $RE ]]; then
            continue
        fi
        NAME=$(sed -r 's/(^|-)(\w)/\U\2/g' <<<"$TOKEN")
        TOKENNAME=$(tr '[:upper:]' '[:lower:]' <<<"$NAME")
        if [[ "${TOKENNAME}" = "string" ]]; then
            TOKENNAME="String"
        fi
        if [[ "${TOKENNAME}" = "number" ]]; then
            TOKENNAME="Number"
        fi


        RULEMATCHES+=" ${TOKENNAME}"
    done

    if [[ "$FACT" != "$LAST_FACT" ]]; then
        echo "\"${STRING}\"    { RET_TOKEN_ENUM(${FACT}, "Fact::${FACT}") }" >> gen/tokens.flex

        if [[ -z "${ALL_FACTS}" ]]; then
            ALL_FACTS+="     ${FACTLOWERCASE}\n"
        else
            ALL_FACTS+="   | ${FACTLOWERCASE}\n"
        fi

        LVAL_ENUMS+="    ${FACT},\n"
        PARSER_TYPES+="%%type <Fact> ${FACT}\n"
        PARSER_TYPES+="%%type <std::shared_ptr<ai::Condition>> ${FACTLOWERCASE}\n"
    fi
    RULEMATCHES+=" { \$\$ = driver.createCondition("
    # I'm too lazy to do this properly, so sue me
    if [[ "${#LINE[@]}" -eq "0" ]]; then
        RULEMATCHES+="\$1"
    elif [[ "${#LINE[@]}" -eq "1" ]]; then
        RULEMATCHES+="\$1, \$2"
    elif [[ "${#LINE[@]}" -eq "2" ]]; then
        RULEMATCHES+="\$1, \$2, \$3"
    elif [[ "${#LINE[@]}" -eq "3" ]]; then
        RULEMATCHES+="\$1, \$2, \$3, \$4"
    elif [[ "${#LINE[@]}" -eq "4" ]]; then
        RULEMATCHES+="\$1, \$2, \$3, \$4, \$5"
    fi
    RULEMATCHES+="); }\n"
    #    RULEMATCHES+=" { \$\$ = AiRule::createCondition("
    #    # I'm too lazy to do this properly, so sue me
    #    if [[ "${#LINE[@]}" -eq "1" ]]; then
    #        RULEMATCHES+="\$1"
    #    elif [[ "${#LINE[@]}" -eq "2" ]]; then
    #        RULEMATCHES+="\$1, \$2"
    #    elif [[ "${#LINE[@]}" -eq "3" ]]; then
    #        RULEMATCHES+="\$1, \$2, \$3"
    #    elif [[ "${#LINE[@]}" -eq "4" ]]; then
    #        RULEMATCHES+="\$1, \$2, \$3, \$4"
    #    elif [[ "${#LINE[@]}" -eq "5" ]]; then
    #        RULEMATCHES+="\$1, \$2, \$3, \$4, \$5"
    #    fi
    #    RULEMATCHES+="); }\n"

    echo "%token ${FACT}" >> gen/tokens.y
    if [[ -n "${RULEMATCHES}" ]]; then
        printf "${RULEMATCHES}"  >> gen/rules
    fi
    LAST_FACT="${FACT}"
    #PARSER_TYPES+="%%type <${TYPE}> ${TYPELOWERCASE}\n"
done < lists/facts.list

printf "\nfact:\n${ALL_FACTS}\n" >> gen/rules

printf "enum class Fact {\n${LVAL_ENUMS}\n};\n" >> gen/enums.h
printf "\n}// namespace ai\n" >> gen/enums.h

printf "$PARSER_TYPES" >> gen/parser-types.y
printf "%%union {\n    int number;\n    const char *string;\n${UNION_MEMBERS}}\n" >> gen/union.y


#rm -f grammar.gen.ypp && cat parser.head.y <(sort -u < gen/tokens.y) gen/union.y gen/parser-types.y parser.mid.y gen/rules  parser.tail.y > grammar.gen.ypp
rm -f grammar.gen.ypp && cat parser.head.y <(sort -u < gen/tokens.y)  gen/parser-types.y parser.mid.y gen/rules  parser.tail.y > grammar.gen.ypp
rm -f tokenizer.gen.flex && cat tokenizer.head.flex gen/tokens.flex tokenizer.tail.flex > tokenizer.gen.flex

flex++ -Ca --debug -+  tokenizer.gen.flex  && bison --language=C++  --defines --debug -v -d grammar.gen.ypp
clang++  -Wall -Wextra -pedantic -Wno-unused-parameter -std=gnu++17 -I.. grammar.gen.tab.cpp lex.yy.cc ScriptLoader.cpp AiScript.cpp AiRule.cpp ../core/Logger.cpp ../global/EventListener.cpp ../global/EventManager.cpp && ./a.out < SAMPLEAI.PER
