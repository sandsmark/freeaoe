#include "LanguageManager.h"

#include "global/Config.h"

#include <genie/lang/LangFile.h>

Logger &LanguageManager::log = Logger::getLogger("freeaoe.LanguageMAnager");

LanguageManager *LanguageManager::Inst()
{
    static LanguageManager instance;
    return &instance;
}

bool LanguageManager::initialize()
{
    std::string filename;
    try {
        loadLangFile("language.dll");
        loadLangFile("language_x1.dll");
        loadLangFile("language_x1_p1.dll");
    } catch (const std::exception &error) {
        std::cerr << "Failed to load language file " << filename << ": " << error.what() << std::endl;
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
    for (const std::shared_ptr<genie::LangFile> langfile : Inst()->m_langFiles) {
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

void LanguageManager::loadLangFile(std::string filename)
{
    log.info("Loading %s", filename.c_str());

    std::string filePath = Config::Inst()->getDataPath() + filename;

    std::shared_ptr<genie::LangFile> ret (new genie::LangFile);
    ret->load(filePath.c_str());

    m_langFiles.push_back(ret);
}
