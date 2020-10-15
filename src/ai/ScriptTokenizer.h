#pragma once



#undef YY_DECL
#define YY_DECL ai::ScriptParser::symbol_type ai::ScriptTokenizer::yylex()

#include <iostream>

#ifndef yyFlexLexerOnce
#include "FlexLexer.h"
#endif

#include "grammar.gen.tab.hpp"

namespace ai {
    class ScriptParser;
    class ScriptLoader;

    class ScriptTokenizer : public yyFlexLexer {
    public:
        ScriptTokenizer(std::istream &in) : yyFlexLexer(in, std::cout) {}
        virtual ~ScriptTokenizer() {}
        ai::ScriptParser::symbol_type yylex(ai::ScriptLoader &_driver);
        int yylex() override { assert(false); return 0; }
    };
}
