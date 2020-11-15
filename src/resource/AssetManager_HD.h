#pragma once

#include "AssetManager.h"
#include "core/Logger.h"
#include "global/Config.h"

#include <genie/resource/DrsFile.h>
#include <genie/util/Utility.h>
#include <genie/resource/WavFile.h>

#include <memory>
#include <filesystem>
#include <cstdint>

class AssetManager_HD : public AssetManager
{

    // AssetManager interface
public:
    SlpFilePtr getSlp(uint32_t id, const ResourceType type) override;
    SlpFilePtr getSlp(const std::string &name, const ResourceType type) override;
    SlpFilePtr getUiOverlay(const UiResolution res, const UiCiv civ) override;
    std::shared_ptr<genie::UIFile> getUIFile(const std::string &name) override;
    const genie::PalFile &getPalette(uint32_t id) override;
    bool initialize(const genie::GameVersion gameVersion) override;
    const std::string &assetsPath() const override;
    std::string locateStreamFile(const std::string &filename) override;
    std::shared_ptr<uint8_t[]> loadWav(uint32_t id) const override;
    bool missingData() const override;

    std::string campaignsPath() const override;

    std::string blendomaticFilename() const override { return "blendomatic_x1.dat"; }

private:
    std::string findHdFile(const std::string &filename) const;

    std::string m_hdAssetPath;
    std::unordered_map<std::string, std::string> m_hdFilePaths;

    std::unordered_set<uint32_t> m_nonExistentSlps;

    std::unordered_map<int, std::unique_ptr<genie::PalFile>> m_hdPalFiles;

};

SlpFilePtr AssetManager_HD::getSlp(uint32_t id, const ResourceType type)
{
    genie::SlpFilePtr slp_ptr;
    if (m_nonExistentSlps.count(id)) {
        return slp_ptr;
    }

    std::string filePath = findHdFile(std::to_string(id) + ".slp");
    if (filePath.empty()) {
        m_nonExistentSlps.insert(id);
        DBG << "No slp file with id" << id << "found!";
        return slp_ptr;
    }

    slp_ptr = std::make_shared<genie::SlpFile>(std::filesystem::file_size(filePath));
    slp_ptr->load(filePath);
    return slp_ptr;
}

SlpFilePtr AssetManager_HD::getSlp(const std::string &name, const ResourceType type)
{
    std::string filePath = findHdFile(name);
    if (!filePath.empty()) {
        genie::SlpFilePtr slp_ptr;
        slp_ptr = std::make_shared<genie::SlpFile>(std::filesystem::file_size(filePath));
        slp_ptr->load(filePath);
        return slp_ptr;
    }

    DBG << "No slp file with name" << name << "found, trying id";
    // Falling back to looking up ID
    return getSlp(filenameID(name), type);
}

SlpFilePtr AssetManager_HD::getUiOverlay(const UiResolution res, const UiCiv civ)
{
    int offset = 0;
    switch(res) {
    case UiResolution::Ui800x600:
        offset = 18;
        break;
    case UiResolution::Ui1024x768:
        offset = 10;
        break;
    case UiResolution::Ui1280x1024:
        offset = 20;
        break;
    default:
        WARN << "This probably isn't going to exist";
    }
    WARN << (uint32_t(res) + uint32_t(civ) + offset);
    return getSlp(uint32_t(res) + uint32_t(civ) + offset, ResourceType::Interface);
}

std::shared_ptr<genie::UIFile> AssetManager_HD::getUIFile(const std::string &name)
{
    std::string filePath = findHdFile(name);
    if (filePath.empty()) {
        WARN << "Failed to find UI file" << name;
        filePath = findHdFile(std::to_string(filenameID(name)) + ".bina");
        if (filePath.empty()) {
            WARN << "Not even with fallback";
            return {};
        }
        DBG << "Found with falling back to ID";
    }
    std::shared_ptr<genie::UIFile> file = std::make_shared<genie::UIFile>();
    file->load(filePath);
    return file;
}

const genie::PalFile &AssetManager_HD::getPalette(uint32_t id)
{
    if (m_hdPalFiles[id]) {
        return *m_hdPalFiles[id];
    }
    std::string filepath = findHdFile(std::to_string(id) + ".bina");
    if (!filepath.empty()) {
        m_hdPalFiles[id] = std::make_unique<genie::PalFile>();
        m_hdPalFiles[id]->load(filepath);
    } else {
        WARN << "Failed to find palette" << id;
    }
    return *m_hdPalFiles[id];
}

bool AssetManager_HD::initialize(const genie::GameVersion gameVersion)
{
    const std::string gamePath = Config::Inst().getValue(Config::GamePath);

    AssetManager::initializeInternal(gamePath + "/resources/_common/dat/", gameVersion);

    m_hdAssetPath = genie::util::resolvePathCaseInsensitive("/resources/_common/", gamePath);

    DBG << "Is HD, not loading DRS files";
    TIME_THIS;

    for (const std::string &subfolder : {"drs/graphics", "drs/gamedata_x2", "drs/terrain", "drs/terrain/textures", "drs/gamedata_x1", "drs/interface", "drs/sounds", "slp" }) {
        const std::string folder = m_hdAssetPath + subfolder + "/";
        if (!std::filesystem::exists(folder)) {
            WARN << "folder no exist" << folder;
            continue;
        }
        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(folder)) {
            if (!entry.is_regular_file()) {
                WARN << "not regular file!" << entry.path();
                continue;
            }
            const std::filesystem::path path = entry.path();
            m_hdFilePaths[path.filename().string()] = path.string();
        }
    }
    return true;
}

const std::string &AssetManager_HD::assetsPath() const
{
    return m_hdAssetPath;
}

std::string AssetManager_HD::locateStreamFile(const std::string &filename)
{
    static const std::vector<std::string> possibleFolders = {
        "resources/_common/sound/stream/",
        "resources-dlc2/_common/sound/stream/",
        "resources/_common/sound/civ/",
        "resources/_common/sound/music/",
        "resources-dlc2/_common/sound/civ/",
        "resources/en/campaign/sound/",
        "resources/en/sound/scenario/",
        "resources/en/sound/taunt/",
         // TODO: other languages?
    };

    const std::string gamePath = Config::Inst().getValue(Config::GamePath);
    for (const std::string &folder : possibleFolders) {
        std::string path = genie::util::resolvePathCaseInsensitive(folder + filename, gamePath);
        if (!path.empty()) {
            return path;
        }
    }
    return "";
}

std::shared_ptr<uint8_t[]> AssetManager_HD::loadWav(uint32_t id) const try
{
    // TODO: move to genieutils?
    static const std::vector<std::string> possibleFolders = {
        "resources/_common/drs/sounds/",
        "resources-dlc2/_common/drs/gamedata_x2/",
        "resources/_common/drs/gamedata_x2/",
        "resources/_common/drs/interface/",
        "resources/_common/sound/terrain/",
    };

    const std::string filename = std::to_string(id) + ".wav";
    const std::string gamePath = Config::Inst().getValue(Config::GamePath);
    std::string path;
    for (const std::string &folder : possibleFolders) {
        path = genie::util::resolvePathCaseInsensitive(folder + filename, gamePath);
        if (!path.empty()) {
            break;
        }
    }
    if (path.empty()) {
        WARN << "Failed to locate" << filename << "in" << gamePath;
        return nullptr;
    }
    DBG << "Loading" << path;

    std::ifstream file(path, std::ios::binary|std::ios::in);
    if (!file.good()) {
        WARN << "FAiled to open" << path;
        return nullptr;
    }

    file.seekg(0, std::ios_base::end);
    ssize_t size = ssize_t(file.tellg());
    file.seekg(0);

    std::shared_ptr<uint8_t[]> ptr(new uint8_t[size]);
    file.read(reinterpret_cast<char*>(ptr.get()), size);

    genie::WavFile::WavHeader *header = reinterpret_cast<genie::WavFile::WavHeader*>(ptr.get());
    if (size < header->Subchunk2Size) {
        WARN << "Invalid filesize" << size << "expected more than" << header->Subchunk2Size;
        return nullptr;
    }

    return ptr;
} catch (const std::exception &e) {
    WARN << "Failed to load wav" << e.what();
    return nullptr;
}

bool AssetManager_HD::missingData() const
{
    return !std::filesystem::exists(m_hdAssetPath + "/drs/terrain/");
}

std::string AssetManager_HD::campaignsPath() const
{
    return genie::util::resolvePathCaseInsensitive("/campaign/", m_hdAssetPath);
}

std::string AssetManager_HD::findHdFile(const std::string &filename) const
{
    std::unordered_map<std::string, std::string>::const_iterator it = m_hdFilePaths.find(filename);
    if (it != m_hdFilePaths.end()) {
        return it->second;
    }

    return "";
}
