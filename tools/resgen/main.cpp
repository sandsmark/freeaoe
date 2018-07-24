#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <filesystem>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <datafile>" << std::endl;
        std::cerr << "Generates <datafile>_res.h and <datafile>_res.c" << std::endl;
        return 1;
    }

    // Get names
    const std::string inFilepath = argv[1];
    const std::string inFilename = std::filesystem::path(inFilepath).filename().string();
    if (inFilename.empty()) {
        std::cerr << "Passed invalid input file path " << inFilepath << std::endl;
        return 1;
    }

    // Open input
    std::ifstream inStream(inFilepath, std::ios::binary|std::ios::in);
    if (!inStream.is_open()) {
        std::cerr << "Failed to open " << inFilepath << " for reading" << std::endl;
        return 1;
    }

    // Open outputs
    const std::string hFilename = inFilename + ".h";
    std::ofstream hStream(hFilename);
    if (!hStream.is_open()) {
        std::cerr << "Failed to open " << hFilename << " for writing" << std::endl;
        return 1;
    }

    const std::string cFilename = inFilename + ".c";
    std::ofstream cStream(cFilename);
    if (!cStream.is_open()) {
        std::cerr << "Failed to open " << cFilename << " for writing" << std::endl;
        return 1;
    }

    std::string resname = "resource_" + std::regex_replace(inFilename, std::regex("[^A-Za-z0-9]+"), "_");

    // Generate .h
    hStream << "#pragma once" << std::endl << std::endl;
    hStream << "extern \"C\" const char " << resname << "_data[];" << std::endl;
    hStream << "static const size_t " << resname << "_size = " << std::filesystem::file_size(inFilepath) << ";" << std::endl;

    // Generate .c
    cStream << "const char " << resname << "_data[] = {" << std::endl;
    cStream << "    ";

    // Generate array
    cStream << std::hex;
    unsigned char c = inStream.get();
    while (inStream.good()) {
        cStream << "0x" << int(c);

        c = inStream.get();
        if (inStream.eof()) {
            break;
        }

        cStream << ",";

        if (inStream.tellg() % 10 == 0) {
            // Break lines
            cStream << std::endl;
            cStream << "    ";
        } else {
            cStream << " ";
        }
    }

    if (inStream.bad()) {
        std::cerr << "Fail when reading data" << std::endl;
        return 1;
    }

    cStream << std::dec;
    cStream << std::endl << "};" << std::endl;

    std::cout << "Generated " << hFilename << " and " << cFilename << " based on " << inFilename << std::endl;

    return 0;
}
