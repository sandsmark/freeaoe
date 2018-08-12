#include "LanguageManager.h"

#include "global/Config.h"

#include <genie/lang/LangFile.h>

LanguageManager *LanguageManager::Inst()
{
    static LanguageManager instance;
    return &instance;
}

bool LanguageManager::initialize(const std::string &dataPath)
{
    std::string filename;
    try {
        loadLangFile(dataPath + "language.dll");
        loadLangFile(dataPath + "language_x1.dll");
        loadLangFile(dataPath + "language_x1_p1.dll");
    } catch (const std::exception &error) {
        WARN << "Failed to load language file" << filename << error.what();
        return false;
    }

    return true;
}

std::string LanguageManager::getString(unsigned int id)
{
    std::unordered_map<unsigned int, std::string> &cache = Inst()->m_cache;

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
        ret = "";
    }

    cache[id] = ret;

    return ret;
}

LanguageManager::LanguageManager()
{
}

void LanguageManager::loadLangFile(const std::string &filename)
{
    DBG << "Loading" << filename;

    std::shared_ptr<genie::LangFile> ret = std::make_shared<genie::LangFile>();
    ret->load(filename);

    m_langFiles.push_back(ret);
}
