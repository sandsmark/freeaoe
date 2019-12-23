%%

#ifdef PARSER_TEST
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please pass a file as argument" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    ai::ScriptLoader parser(0);
    return parser.parse(in, std::cout);
}
#endif

void ai::ScriptParser::error(const location_type &loc, const std::string& message) {
    std::cerr << "parser error: " << message << " at line " << loc.begin.line << " to " << loc.end.line << std::endl;
}
