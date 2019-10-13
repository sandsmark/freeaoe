%%

int main() {
       ai::ScriptLoader parser;
       return parser.parse(std::cin, std::cout);
}

void ai::ScriptParser::error(const location_type &loc, const std::string& message) {
    std::cerr << "parser error: " << message << " at line " << loc.begin.line << " to " << loc.end.line << std::endl;
}
