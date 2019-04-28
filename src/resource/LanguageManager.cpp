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
        filename = dataPath + "language.dll";
        loadLangFile(filename);
        filename = dataPath + "language_x1.dll";
        loadLangFile(filename);
        filename = dataPath + "language_x1_p1.dll";
        loadLangFile(filename);
    } catch (const std::exception &error) {
        WARN << "Failed to load language file" << filename << error.what();
        if (!m_langFiles.empty()) {
            WARN << "got at least one file, continoung";
            return true;
        }
        return false;
    }

    return true;
}

const std::string &LanguageManager::getString(unsigned int id)
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

    return cache[id];
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
