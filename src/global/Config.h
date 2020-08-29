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

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

//
class Config
{
public:
    enum OptionType {
        GamePath,
        GameSample,
        SinglePlayer,
        ScenarioFile,
    };

    enum StorePolicy {
        NotStored = 0,
        Stored = 1
    };

    struct OptionDefinition {
        OptionType id;
        std::string name;
        std::string description;
        StorePolicy saved = NotStored;
    };

    //----------------------------------------------------------------------------
    /// Get instance (singleton pattern)
    ///
    /// @return returns instance of config
    //
    static Config &Inst();

    //----------------------------------------------------------------------------
    /// Parses command line options and config file if present.
    ///
    //
    bool parseOptions(int argc, char **argv);


    bool isOptionSet(const OptionType option);
    std::string getValue(const OptionType option);
    void setValue(const OptionType option, const std::string &value);

    void printUsage(const std::string &programName);

#if defined(__linux__)
    static std::string winePath();
#endif

private:
    Config(const std::string &applicationName);
    void setKnownOptions(const std::vector<OptionDefinition> &options);

    bool parseOption(const std::string &option);

    void parseConfigFile(const std::string &path);
    void writeConfigFile(const std::string &path);

    std::string m_dataPath;
    std::string m_gamePath;
    std::string m_scenarioFile;
    std::string m_filePath;
    std::unordered_map<OptionType, std::string> m_values;
    std::unordered_map<std::string, OptionDefinition> m_knownOptions;
};

