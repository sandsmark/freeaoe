#include "LanguageManager.h"

#include <genie/lang/LangFile.h>
#include <algorithm>
#include <filesystem>
#include <istream>

#include "core/Logger.h"
#include "core/Utility.h"
#include "global/Config.h"

LanguageManager *LanguageManager::Inst()
{
    static LanguageManager instance;
    return &instance;
}

bool LanguageManager::initialize()
{
    m_cache.clear();
    m_langFiles.clear();
    m_isHd = false;

    const std::string gamePath = Config::Inst().getValue(Config::GamePath) + "/";
    std::string hdFile = gamePath + "/resources/en/strings/key-value/key-value-strings-utf8.txt";
    if (std::filesystem::exists(hdFile)) {
        if (!loadTxtFile(hdFile)) {
            WARN << "Failed to load main strings";
            return false;
        }

        if (!loadTxtFile(gamePath + "/resources/en/strings/key-value/key-value-modded-strings-utf8.txt")) {
            WARN << "Failed to load modded strings";
        }

        m_isHd = true;

        return true;
    }

    std::string filename;
    try {
        filename = gamePath + "language.dll";
        loadLangFile(filename);
        filename = gamePath + "language_x1.dll";
        loadLangFile(filename);
        filename = gamePath + "language_x1_p1.dll";
        loadLangFile(filename);
    } catch (const std::exception &error) {
        WARN << "Failed to load language file" << filename << error.what();
        if (!m_langFiles.empty()) {
            WARN << "got at least one file, continoung";
            return true;
        }

        throw std::runtime_error("Failed to load language file " + filename);
    }

    return true;
}

std::string LanguageManager::getString(unsigned int id)
{
    std::unordered_map<unsigned int, std::string> &cache = Inst()->m_cache;
    // With HD we preload everything into the cache, so don't bother checking
    if (Inst()->m_isHd) {
        return cache[id];
    }

    if (cache.find(id) != cache.end()) {
        return cache[id];
    }

    std::string ret;

    for (const std::shared_ptr<genie::LangFile> &langfile : Inst()->m_langFiles) {
        ret = langfile->getString(id);
        if (!ret.empty()) {
            break;
        }
    }

    if (ret.empty()) {
        DBG << "Failed to find for" << id;
        ret = "";
    }

    cache[id] = ret;

    return cache[id];
}

std::string LanguageManager::cpnTitle(const uint8_t campaignNum)
{
    // IDK? It's in the DLL at this offset
    return getString(34928 + campaignNum * 30);
}

std::string LanguageManager::cpxTitle(const uint8_t campaignNum)
{
    return getString(34928 + campaignNum * 30 + 300); // cpx files are +300
}

std::string LanguageManager::cpnScenarioTitle(const uint8_t campaignNum, const uint8_t scenarioNum)
{
    return getString(34928 + campaignNum * 30 + 1 + scenarioNum);
}

std::string LanguageManager::cpxScenarioTitle(const uint8_t campaignNum, const uint8_t scenarioNum)
{
    return getString(34928 + campaignNum * 30 + 1 + scenarioNum + 300);
}

void LanguageManager::loadLangFile(const std::string &filename)
{
    DBG << "Loading" << filename;

    std::shared_ptr<genie::LangFile> ret = std::make_shared<genie::LangFile>();
    ret->load(filename);

    m_langFiles.push_back(ret);
}

bool LanguageManager::loadTxtFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)) {
        line = util::trimString(line);

        if (line.empty()) {
            continue;
        }

        if (!std::isdigit(line[0])) {
            continue;
        }
        std::string::size_type spacePos = line.find(' ');
        if (spacePos == std::string::npos) {
            continue;
        }

        int id = std::stoi(line.substr(0, spacePos));

        // For some reason it has dumb quotes around it, which is retareded when all of them are on a single line
        std::string text = line.substr(spacePos + 1);
        if (text.size() > 2 && text[0] == '"' && text[text.length() - 1] == '"') {
            text = text.substr(1, text.length() - 2);
        }

        if (text.empty()) {
            WARN << "empty string";
            continue;
        }

        m_cache[id] = text;
    }

    return true;
}
