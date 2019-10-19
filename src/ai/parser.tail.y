%%

#ifdef PARSER_TEST
int main() {
       ai::ScriptLoader parser(nullptr);
       return parser.parse(std::cin, std::cout);
}
#endif

void ai::ScriptParser::error(const location_type &loc, const std::string& message) {
    std::cerr << "parser error: " << message << " at line " << loc.begin.line << " to " << loc.end.line << std::endl;
}
