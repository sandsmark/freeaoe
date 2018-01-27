/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Config.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <experimental/filesystem>


#if defined(_WINDOWS)
#include <Shlobj.h>
#endif

using namespace std::experimental;

void Config::printUsage(const std::string &programName)
{
    std::cerr << "Usage: " << programName << " [options]" << std::endl;
    std::cerr << "Options:" << std::endl;

    for (const auto &[name, description] : m_allowedOptions) {
        static_assert(std::is_same<decltype(name), const std::string>()); // fuck auto
        static_assert(std::is_same<decltype(description), const std::string>()); // fuck auto x2

        std::cerr << std::setw(25) << std::left;
        std::cerr << ("  --" + name + "=value");
        std::cerr << description << std::endl;

    }

    return;
}

//------------------------------------------------------------------------------
bool Config::parseOptions(int argc, char **argv)
{
    parseConfigFile(m_filePath);

    std::unordered_map<std::string, std::string> configuredOptions = m_options;

    for (int i=1; i<argc; i++) {
        std::string argument = argv[i];
        if (argument.find("--") != 0) {
            printUsage(argv[0]);
            return false;
        }

        // strip the --
        if (!parseOption(argument.substr(2))) {
            printUsage(argv[0]);
            return false;
        }
    }

    if (m_options != configuredOptions) {
        writeConfigFile(m_filePath);
    }

    return true;
}

void Config::setAllowedOptions(const std::unordered_map<std::string, std::string> options)
{
    m_allowedOptions = options;
}

const std::string Config::getValue(const std::string &name)
{
    return m_options[name];
}

void Config::setValue(const std::string &name, const std::string &value)
{
    m_options[name] = value;

    writeConfigFile(m_filePath);
}

//------------------------------------------------------------------------------
Config::Config(const std::string &applicationName)
{
#if defined(__linux__)
    char *rawPath = getenv("XDG_CONFIG_HOME");
    if (rawPath) {
        m_filePath = std::string(rawPath);
    }
    if (m_filePath.empty()) {
        rawPath = getenv("HOME");
        if (rawPath) {
            m_filePath = getenv("HOME");
            m_filePath += "/.config";
        }
    } else if (m_filePath.find(':') != std::string::npos) {
        std::istringstream stream(m_filePath);
        std::string testPath;
        while (std::getline(stream, testPath, ':')) {
            if (!filesystem::exists(testPath)) {
                continue;
            } if (!filesystem::is_directory(testPath)) {
                continue;
            }

            m_filePath = testPath;
            break;
        }
    }
    m_filePath += "/";
#elif defined(_WINDOWS)
    //FIXME: don't really windows, and not tested
    PWSTR rawPath = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &rawPath);
    if (FAILED(hr)) {
        std::cerr << "Failed to get user configuration path!" << std::endl;
        return std::string();
    }
    if (rawPath) {
        path = rawPath;
        path += "\\";
    }
    CoTaskMemFree(rawPath);
#endif

    m_filePath += applicationName + ".cfg";
}

bool Config::parseOption(const std::string &option)
{
    if (option.empty()) {
        return true;
    }

    size_t splitPos = option.find("=");
    if (splitPos == std::string::npos) {
        std::cerr << "Invalid line in config: " << option << std::endl;
        return false;
    }

    std::string name = option.substr(0, splitPos);
    std::string value = option.substr(splitPos + 1);
    if (!checkOption(name, value)) {
        std::cerr << "Invalid option in config: " << option << std::endl;
        return false;
    }

    return true;
}

void Config::parseConfigFile(const std::string &path)
{
    std::cout << "parsing config file  " << path << std::endl;
    if (!filesystem::exists(path)) {
        return;
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseOption(line);
    }
}

void Config::writeConfigFile(const std::string &path)
{
    std::cout << "storing config" << std::endl;
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file " << path << std::endl;
        return;
    }

    for (const auto &[name, value] : m_options) {
        static_assert(std::is_same<decltype(name), const std::string>()); // fuck auto
        static_assert(std::is_same<decltype(value), const std::string>()); // fuck auto x2

        file << name << "=" << value << "\n";
    }
}

bool Config::checkOption(const std::string &name, const std::string &value)
{
    std::cout << "checking " << name << " " << value << std::endl;
    if (m_allowedOptions.find(name) == m_allowedOptions.end()) {
        std::cerr << "Unknown option " << name << std::endl;
        return false;
    }

    m_options[name] = value;
    return true;
}
