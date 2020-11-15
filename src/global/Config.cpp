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

#include <genie/util/Utility.h>

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

static std::string locateSteamVersion()
{
    char *xdgDataHome = getenv("XDG_DATA_HOME");
    std::string dataHome;
    if (xdgDataHome && strlen(xdgDataHome) && std::filesystem::exists(xdgDataHome)) {
        dataHome = xdgDataHome;
    } else {
        dataHome = "~/.local/share";
    }
    dataHome = resolvePath(dataHome.c_str()); // handles XDG_DATA_HOME containing ~
    dataHome += "/"; // Justin Case
    const std::string ret = genie::util::resolvePathCaseInsensitive("Steam/steamapps///common//Age2HD/", dataHome);
    if (!ret.empty()) {
        DBG << "Located steam version at" << ret;
    }
    return ret;
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
    std::cout << "Usage: " << programName << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;

    for (const std::pair<const std::string, OptionDefinition> &nameAndDefinition : m_knownOptions) {
        const std::string &name = nameAndDefinition.first;
        const OptionDefinition &option = nameAndDefinition.second;

        std::cout << std::setw(25) << std::left;
        std::cout << ("  --" + name + (option.argumentType != NoArgument ? "=value" : ""));
        std::cout << option.description << std::endl;

    }
}


//------------------------------------------------------------------------------
bool Config::parseOptions(int argc, char **argv)
{
    parseConfigFile(m_filePath);

    std::unordered_map<OptionType, std::string> configuredOptions = m_values;

    for (int i=1; i<argc; i++) {
        std::string argument = argv[i];
        if (argument == "--help") {
            printUsage(argv[0]);
            return false;
        }

        if (!argument.starts_with("--")) {
            printUsage(argv[0]);
            return false;
        }

        // strip the --
        if (!parseOption(argument.substr(2))) {
            printUsage(argv[0]);
            return false;
        }
    }

    if (getValue(GamePath).empty()) {
        setValue(GamePath, getRegistryString(s_registryGroupTC, s_registryKey));
    }
    if (getValue(GamePath).empty()) {
        setValue(GamePath, getRegistryString(s_registryGroupAoK, s_registryKey));
    }
#if defined(__linux__)
    if (getValue(GamePath).empty()) {
        setValue(GamePath, locateSteamVersion());
    }
#endif
#if defined(DEFAULT_DATA_PATH)
    if (getValue(GamePath).empty()) {
        setValue(GamePath, getRegistryString(DEFAULT_DATA_PATH);
    }
#endif

    if (m_values != configuredOptions) {
        writeConfigFile(m_filePath);
    }

    return true;
}

void Config::setKnownOptions(const std::vector<Config::OptionDefinition> &options)
{
    m_knownOptions.clear();
    for (const OptionDefinition &option : options) {
        m_knownOptions[option.name] = option;
    }
}

bool Config::isOptionSet(const Config::OptionType option)
{
    return (m_values.find(option) != m_values.end());
}


std::string Config::getValue(const OptionType option)
{
    // TODO separate getters, it's a bit dumb with all this generic shit for basically just one
    std::unordered_map<OptionType, std::string>::const_iterator it = m_values.find(option);
    if (it == m_values.end() || it->second.empty()) {
        if (option == Language) { // always return a valid one
            return "en";
        }
        DBG << "Unconfigured option" << option;
        return "";
    }
    if (option == GamePath) {
        const std::filesystem::path path(it->second);
        if (!std::filesystem::exists(path) || path == path.root_path()) {
            return {};
        }
        return path.generic_string();
    }
    return it->second;
}

void Config::setValue(const OptionType option, const std::string &value)
{
    if (option == GamePath) {
        std::string path = genie::util::resolvePathCaseInsensitive(value);
        if (!path.empty()) {
            m_values[option] = path;
        }
    } else {
        if (option == Language) {
            if (value.length() != 2) {
                WARN << "I think all language lengths should be 2, you're on your own";
            }
            if (value == "_common") { // don't be clever
                WARN << "Nope";
                return;
            }
            std::unordered_set<std::string> knownValid = {
                "br", "de", "en", "es", "fr", "it", "jp", "ko", "nl", "ru", "zh",
            };
            if (!knownValid.count(value)) {
                WARN << value << "is not a language I've seen in AoE2HD, setting anyways";
            }
        }

        m_values[option] = value;

        writeConfigFile(m_filePath);
    }

    emit(option);
}

//------------------------------------------------------------------------------
Config::Config(const std::string &applicationName)
{
    setKnownOptions({
            { Config::GamePath, "game-path", "Path to AoE installation with data files", Config::HasArgument, Config::Stored },
            { Config::ScenarioFile, "scenario-file", "Path to scenario file to load", Config::HasArgument, Config::NotStored },
            { Config::SinglePlayer, "single-player", "Launch a simple test map", Config::NoArgument, Config::NotStored },
            { Config::GameSample, "game-sample", "Game samples to load", Config::HasArgument, Config::NotStored },
            { Config::PrintHelp, "help", "Show usage", Config::NoArgument, Config::NotStored },
            { Config::SoundVolume, "sound-volume", "Sound volume", Config::HasArgument, Config::Stored },
            { Config::MusicVolume, "music-volume", "Music volume", Config::HasArgument, Config::Stored },
            { Config::Language, "language", "Language, e. g. 'en' or 'jp', only for HD so far", Config::HasArgument, Config::Stored },


            // Not actually parsed here (need it earlier to enable it), just so it knows about it
            { Config::EnableDebug, "debug", "Print all debug output", Config::NoArgument, Config::NotStored },
        });

#ifndef NDEBUG
    for (int opt=0; opt<OptionsCount; opt++) {
        bool found = false;
        // really inefficient, so sue me
        for (const std::pair<const std::string, OptionDefinition> &def : m_knownOptions) {
            if (def.second.id == opt) {
                found = true;
                break;
            }
        }
        if (found) {
            continue;
        }
        WARN << "Missing definition for option" << opt;
    }
#endif

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

Config &Config::Inst()
{
    static Config instance("freeaoe");

    return instance;
}

bool Config::parseOption(const std::string &option)
{
    if (option.empty()) {
        return true;
    }

    std::string name;
    std::string value;

    size_t splitPos = option.find('=');
    if (splitPos != std::string::npos) {
        name = option.substr(0, splitPos);
        value = option.substr(splitPos + 1);
    } else {
        name = option;
    }


    std::unordered_map<std::string, OptionDefinition>::const_iterator it = m_knownOptions.find(name);
    if (it == m_knownOptions.end()) {
        WARN << "Unknown option" << name;
        return false;
    }

    if (it->second.argumentType != NoArgument && value.empty()) {
        WARN << "Missing argument for" << name;
        return false;
    }

    setValue(it->second.id, value);

    emit(it->second.id);

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
    if (testMode) {
        return;
    }

    DBG << "storing config";
    std::ofstream file(path);
    if (!file.is_open()) {
        WARN << "Failed to open config file" << path;
        return;
    }

    for (const std::pair<const std::string, OptionDefinition> &nameAndDefinition : m_knownOptions) {
        const std::string &name = nameAndDefinition.first;
        const OptionDefinition &option = nameAndDefinition.second;

        if (option.saved == NotStored) {
            continue;
        }

        const std::string &value = m_values[option.id];

        file << name << "=" << value << "\n";
    }
}
