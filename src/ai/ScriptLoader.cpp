#include "gen/enums.h"

#include "ScriptLoader.h"

#include "ScriptTokenizer.h"
#include "grammar.gen.tab.hpp"


int ai::ScriptLoader::parse(std::istream& in, std::ostream& out) {

    ai::ScriptTokenizer scanner {*this};
    ai::ScriptParser parser {*this, scanner};
    parser.set_debug_stream(out);
    parser.set_debug_level(4);

    int res = parser.parse();

    return res;
}
