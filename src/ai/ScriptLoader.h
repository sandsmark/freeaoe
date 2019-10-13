#pragma once

#include <string>
#include <map>
#include <iostream>

namespace ai {

class ScriptLoader {
    public:
        ScriptLoader() {};
        virtual ~ScriptLoader() {};

        int parse(std::istream& in, std::ostream& out);
};

}

