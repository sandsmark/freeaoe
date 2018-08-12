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
#include "Logger.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_set>

#include <filesystem>

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
#define WINAPI_FAMILY_PARTITION
#include <atlbase.h>
#include <shlobj.h>
#include <codecvt>
#include <knownfolders.h>


static const char *s_registryGroupAoK = "SOFTWARE\\Microsoft\\Microsoft Games\\"
                                        "Age of Empires\\2.0";
static const char *s_registryGroupTC = "SOFTWARE\\Microsoft\\Microsoft Games\\"
                                        "Age of Empires II: The Conquerors Expansion\\1.0";

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
#endif

void Config::printUsage(const std::string &programName)
{
    WARN << "Usage:" << programName << "[options]";
    WARN << "Options:";

    for (const auto &[name, description] : m_allowedOptions) {
        static_assert(std::is_same<decltype(name), const std::string>()); // fuck auto
        static_assert(std::is_same<decltype(description), const std::string>()); // fuck auto x2

        std::cout << std::setw(25) << std::left;
        std::cout << ("  --" + name + "=value");
        std::cout << description << std::endl;

    }
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
#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    if (m_options["game-path"].empty()) {
        m_options["game-path"] = getRegistryString(s_registryGroupTC, "InstallationDirectory");
    }
    if (m_options["game-path"].empty()) {
        m_options["game-path"] = getRegistryString(s_registryGroupAoK, "InstallationDirectory");
    }
#endif

    if (m_options != configuredOptions) {
        writeConfigFile(m_filePath);
    }



    return true;
}

void Config::setAllowedOptions(const std::unordered_map<std::string, std::string> &options)
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
            if (!std::filesystem::exists(testPath)) {
                continue;
            } if (!std::filesystem::is_directory(testPath)) {
                continue;
            }

            m_filePath = testPath;
            break;
        }
    }
    m_filePath += "/";
#elif defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
    //FIXME: don't really windows, and not tested
    wchar_t *rawPath = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &rawPath);
    if (FAILED(hr)) {
        WARN << "Failed to get user configuration path!";
    }
    if (rawPath) {
        m_filePath = std::wstring_convert<
                std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(std::wstring(rawPath));
        m_filePath += std::string("\\");
        CoTaskMemFree(static_cast<void*>(rawPath));
    }
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
