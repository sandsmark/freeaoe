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

#include "core/Logger.h"
#include "core/Utility.h"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <utility>
#include <fstream>

#include <stdlib.h>

static const char *s_registryGroupAoK = R"(SOFTWARE\Microsoft\Microsoft Games\Age of Empires\2.0)";
static const char *s_registryGroupTC = R"(SOFTWARE\Microsoft\Microsoft Games\Age of Empires II: The Conquerors Expansion\1.0)";

static const char *s_registryKey = "InstallationDirectory";
#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)

// I think this was for mingw or something
#ifndef _MSC_VER
#define WINAPI_FAMILY_PARTITION
#endif

#include <atlbase.h>
#include <knownfolders.h>
#include <shlobj.h>
#include <codecvt>


static std::string getRegistryString(const char *regGroup, const char *key)
{
    CRegKey regKey;
    LONG ret = regKey.Open(HKEY_LOCAL_MACHINE, regGroup);

    if (ret != ERROR_SUCCESS) {
        WARN << "Failed to open registry group " << regGroup;
        return std::string();
    }

    char outString[1024];
    ULONG outStringSize = 1024;

    ret = regKey.QueryStringValue(key, outString, &outStringSize);
    regKey.Close();

    if (ret != ERROR_SUCCESS) {
        WARN << "Failed to get key " << key << " from " << regGroup;
        return std::string();
    }

    return std::string(outString);
}
#else

#include <wordexp.h>

// Resolves ~ etc.
static std::string resolvePath(const char *path)
{
    if (!path) {
        return {};
    }

    wordexp_t expanded;
    wordexp(path, &expanded, 0);
    std::string resolved(expanded.we_wordv[0]);
    wordfree(&expanded);

    return resolved;
}

std::string Config::winePath()
{
    const std::string prefixPath = resolvePath(getenv("WINEPREFIX"));
    const std::string defaultPath = resolvePath("~/.wine");

    if (std::filesystem::exists(prefixPath)) {
        return prefixPath;
    }

    if (std::filesystem::exists(defaultPath)) {
        return defaultPath;
    }

    return {};
}

// Probably not the most efficient
static std::string resolvePathCaseInsensitive(const std::string &inputPath, const std::string &basePath = "/")
{
    if (!std::filesystem::exists(basePath)) {
        return {};
    }

    if (std::filesystem::exists(basePath + '/' + inputPath)) {
        return basePath + '/' + inputPath;
    }

    const std::vector<std::string> pathParts = util::stringSplit(inputPath, '/');
    std::string compareFilename = util::toLowercase(pathParts[0]);

    std::string correct;
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(basePath)) {
        std::string candidate = entry.path().filename().string();
        if (util::toLowercase(candidate) == compareFilename) {
            correct = candidate;
            break;
        }
    }

    if (correct.empty()) {
        WARN << "Failed to resolve" << basePath << inputPath;
        return {};
    }

    if (pathParts.size() > 1) {
        return resolvePathCaseInsensitive(inputPath.substr(correct.size() + 1), basePath + '/' + correct);
    }

    return basePath + '/' + correct;
}

// Dumb parsing of the wine registry file
static std::string getRegistryString(const std::string &regGroup, const std::string &key)
{
    std::string regPath = Config::winePath() + "/system.reg";
    if (regPath.empty()) {
        DBG << "failed to find wine folder";
        return {};
    }

    std::ifstream file(regPath);

    if (!file.is_open()) {
        DBG << "Failed to open" << regPath;
        return {};
    }

    std::string groupString = '[' + util::stringReplace(regGroup, "\\", "\\\\") + ']';
    groupString = util::toLowercase(groupString);

    std::string keyString = '"' + util::toLowercase(key) + '"';

    std::string line;
    bool isInCorrectGroup = false;

    std::string path;
    while (std::getline(file, line)) {
        line = util::trimString(line);

        if (line.empty()) {
            continue;
        }

        if (line[0] == '[') {
            if (util::toLowercase(line).starts_with(groupString)) {
                isInCorrectGroup = true;
            } else {
                isInCorrectGroup = false;
            }

            continue;
        }

        if (!isInCorrectGroup) {
            continue;
        }

        if (!util::toLowercase(line).starts_with(keyString)) {
            continue;
        }

        size_t splitPos = line.find('=');
        if (splitPos == std::string::npos) {
            WARN << "Invalid line" << line;
            continue;
        }

        path = util::trimString(line.substr(splitPos + 1));
        path = util::stringReplace(path, "\"", "");

        break;
    }

    if (path.empty()) {
        return {};
    }

    path = util::stringReplace(path, "\\", "/");
    path = util::stringReplace(path, "//", "/");
    if (path.empty()) {
        WARN << "invalid path";
        return {};
    }

    if (util::toLowercase(path).starts_with("C:")) {
        path = path.substr(2);
    }

    path = Config::winePath() + "/drive_c" + path;

    DBG << "Found game path" << path;

    return resolvePathCaseInsensitive(util::toLowercase(path));
}
#endif

void Config::printUsage(const std::string &programName)
{
    WARN << "Usage:" << programName << "[options]";
    WARN << "Options:";

    for (const auto &[name, option] : m_allowedOptions) {
        static_assert(std::is_same<decltype(name), const std::string>()); // fuck auto
        static_assert(std::is_same<decltype(option), const ConfigOption>()); // fuck auto x2

        std::cout << std::setw(25) << std::left;
        std::cout << ("  --" + name + "=value");
        std::cout << option.description << std::endl;

    }
}


//------------------------------------------------------------------------------
bool Config::parseOptions(int argc, char **argv)
{
    parseConfigFile(m_filePath);

    std::unordered_map<std::string, std::string> configuredOptions = m_options;

    for (int i=1; i<argc; i++) {
        std::string argument = argv[i];
        if (argument.starts_with("--")) {
            printUsage(argv[0]);
            return false;
        }

        // strip the --
        if (!parseOption(argument.substr(2))) {
            printUsage(argv[0]);
            return false;
        }
    }

    if (m_options["game-path"].empty()) {
        m_options["game-path"] = getRegistryString(s_registryGroupTC, s_registryKey);
    }
    if (m_options["game-path"].empty()) {
        m_options["game-path"] = getRegistryString(s_registryGroupAoK, s_registryKey);
    }
#if defined(DEFAULT_DATA_PATH)
    if (m_options["game-path"].empty()) {
        m_options["game-path"] = DEFAULT_DATA_PATH;
    }
#endif

    if (m_options != configuredOptions) {
        writeConfigFile(m_filePath);
    }



    return true;
}

void Config::setAllowedOptions(const std::vector<Config::ConfigOption> &options)
{
    m_allowedOptions.clear();
    for (const ConfigOption &option : options) {
        m_allowedOptions[option.name] = option;
    }
}


std::string Config::getValue(const std::string &name)
{
    // TODO separate getters, it's a bit dumb with all this generic shit for basically just one
    if (name == "game-path") {
        std::filesystem::path path(m_options[name]);
        return path.generic_string();
    }

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
            if (!std::filesystem::exists(testPath)) {
                continue;
            }
            if (!std::filesystem::is_directory(testPath)) {
                continue;
            }

            m_filePath = testPath;
            break;
        }
    }
    m_filePath += "/";
#elif defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    m_filePath = std::filesystem::current_path().string();
    m_filePath += "/";
#endif
    m_filePath += applicationName + ".cfg";
}

bool Config::parseOption(const std::string &option)
{
    if (option.empty()) {
        return true;
    }

    size_t splitPos = option.find('=');
    if (splitPos == std::string::npos) {
        WARN << "Invalid line in config:" << option;
        return false;
    }

    std::string name = option.substr(0, splitPos);
    std::string value = option.substr(splitPos + 1);
    if (!checkOption(name, value)) {
        WARN << "Invalid option in config: " << option;
        return false;
    }

    return true;
}

void Config::parseConfigFile(const std::string &path)
{
    DBG << "parsing config file" << path;
    if (!std::filesystem::exists(path)) {
        return;
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        WARN << "Failed to open config file";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseOption(line);
    }
}

void Config::writeConfigFile(const std::string &path)
{
    DBG << "storing config";
    std::ofstream file(path);
    if (!file.is_open()) {
        WARN << "Failed to open config file" << path;
        return;
    }

    for (const auto &[name, value] : m_options) {
        static_assert(std::is_same<decltype(name), const std::string>()); // fuck auto
        static_assert(std::is_same<decltype(value), const std::string>()); // fuck auto x2

        if (!m_allowedOptions[name].saved) {
            continue;
        }

        file << name << "=" << value << "\n";
    }
}

bool Config::checkOption(const std::string &name, const std::string &value)
{
    DBG << "checking" << name << value;
    if (m_allowedOptions.find(name) == m_allowedOptions.end()) {
        WARN << "Unknown option" << name;
        return false;
    }

    m_options[name] = value;
    return true;
}
