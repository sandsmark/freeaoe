#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <global/Logger.h>

#include <memory>
#include <unordered_map>
#include <vector>

namespace genie {
class LangFile;
}

class LanguageManager
{
public:
    static LanguageManager *Inst();
    bool initialize(const std::string dataPath);

    static std::string getString(unsigned int id);

private:
    LanguageManager();
    void loadLangFile(std::string filename);

    std::vector<std::shared_ptr<genie::LangFile>> m_langFiles;
    std::unordered_map<unsigned int, std::string> m_cache;

    static Logger &log;
};

#endif // LANGUAGEMANAGER_H
