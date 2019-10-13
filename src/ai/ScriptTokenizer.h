#pragma once



#undef YY_DECL
#define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex()

#include <iostream>

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include "grammar.gen.tab.hpp"
#include "location.hh"

namespace ai {

    // forward declare to avoid an include
    class ScriptLoader;

    class ScriptTokenizer : public yyFlexLexer {
    public:
        ScriptTokenizer(ai::ScriptLoader &driver) : yyFlexLexer(std::cin, std::cout), _driver(driver) {}
        virtual ~ScriptTokenizer() {}
        ai::ScriptParser::symbol_type yylex(ai::ScriptLoader &_driver);
    private:
        ai::ScriptLoader &_driver;
    };
}
