#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace genie {
class LangFile;
}

class LanguageManager
{
public:
    static LanguageManager *Inst();
    bool initialize();

    static const std::string &getString(unsigned int id);

    static const std::string &cpnTitle(const uint8_t campaignNum);
    static const std::string &cpxTitle(const uint8_t campaignNum);
    static const std::string &cpnScenarioTitle(const uint8_t campaignNum, const uint8_t scenarioNum);
    static const std::string &cpxScenarioTitle(const uint8_t campaignNum, const uint8_t scenarioNum);

private:
    LanguageManager() = default;
    void loadLangFile(const std::string &filename);
    bool loadTxtFile(const std::string &filename);

    std::vector<std::shared_ptr<genie::LangFile>> m_langFiles;
    std::unordered_map<unsigned int, std::string> m_cache;
    bool m_isHd = false;
};

