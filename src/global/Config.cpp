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

#include <fstream>
#include <iostream>
#include <iomanip>
#include <experimental/filesystem>

using namespace std::experimental;

#if defined(_WINDOWS)
#include <Shlobj.h>
#endif

//------------------------------------------------------------------------------
Config *Config::Inst()
{
    static Config config;
    return &config;
}

std::string Config::configPath()
{
    std::string path;
#if defined(__linux__)
    char *rawPath = getenv("XDG_CONFIG_HOME");
    if (rawPath) {
        path = std::string(rawPath);
    }
    if (path.empty()) {
        rawPath = getenv("HOME");
        if (rawPath) {
            path = getenv("HOME");
            path += "/.config";
        }
    } else if (path.find(':') != std::string::npos) {
        std::istringstream stream(path);
        std::string testPath;
        while (std::getline(stream, testPath, ':')) {
            if (!filesystem::exists(testPath)) {
                continue;
            } if (!filesystem::is_directory(testPath)) {
                continue;
            }

            path = testPath;
            break;
        }
    }
    path += "/";
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

    path += "freeaoe.cfg";

    return path;
}

void Config::printUsage(const std::string &programName)
{
    std::cerr << "Usage: " << programName << " [options]" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << std::setw(25) << std::left;
    std::cerr << "\t--game-path=path" << "Path to AoE installation with data files" << std::endl;
    std::cerr << std::setw(25) << std::left;
    std::cerr << "\t--scenario-file=path" << "Path to scenario file to load" << std::endl;

    return;
}

//------------------------------------------------------------------------------
bool Config::parseOptions(int argc, char **argv)
{
    parseConfigFile(configPath());
    const std::string pathBefore = m_gamePath;

    for (int i=1; i<argc; i++) {
        if (!parseOption(argv[i])) {
            printUsage(argv[0]);
            return false;
        }
    }

    if (!filesystem::exists(getDataPath())) {
        std::cerr << "No game path";
        printUsage(argv[0]);
        return false;
    }

    if (pathBefore != m_gamePath) {
        writeConfigFile(configPath());
    }

    return true;
}

//------------------------------------------------------------------------------
std::string Config::getGamePath()
{
    return m_gamePath;
}

//------------------------------------------------------------------------------
std::string Config::getDataPath()
{
    return m_gamePath + "/Data/";
}

//------------------------------------------------------------------------------
std::string Config::getScenarioFile()
{
    return m_scenarioFile;
}

//------------------------------------------------------------------------------
genie::GameVersion Config::getGameVersion() const
{
    return genie::GV_TC;
}

//------------------------------------------------------------------------------
Config::Config()
{
}

//------------------------------------------------------------------------------
Config::~Config()
{
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
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file " << path << std::endl;
        return;
    }
    if (!m_gamePath.empty()) {
        file << "game-path=" << m_gamePath << "\n";
    }
    if (!m_scenarioFile.empty()) {
        file << "scenario-file" << m_gamePath << "\n";
    }
}

bool Config::checkOption(const std::string &name, const std::string &value)
{
    if (name.find("game-path") != std::string::npos) {
        m_gamePath = value;
        return true;
    }
    if (name.find("scenario-file") != std::string::npos) {
        m_scenarioFile = value;
        return true;
    }

    std::cerr << "Unknown option " << name << std::endl;

    return false;
}
