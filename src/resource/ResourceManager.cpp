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

#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <global/Config.h>

#include <genie/resource/DrsFile.h>
#include <genie/resource/UIFile.h>

#include <experimental/filesystem>

using namespace std::experimental;


Logger &ResourceManager::log = Logger::getLogger("freeaoe.ResourceManager");

//------------------------------------------------------------------------------
ResourceManager *ResourceManager::Inst()
{
    static ResourceManager rm;
    return &rm;
}

genie::SlpFilePtr ResourceManager::getUiOverlay(const ResourceManager::UiResolution res, const ResourceManager::UiCiv civ)
{
    return getSlp(uint32_t(res) + uint32_t(civ), Interface);
}

genie::ScnFilePtr ResourceManager::getScn(unsigned int id)
{
    for (std::shared_ptr<genie::DrsFile> drsFile : m_gamedataFiles) {
        genie::ScnFilePtr scnfile = drsFile->getScnFile(id);

        if (scnfile) {
            log.info("found scn file v %s", scnfile->version.c_str());
            std::cout << scnfile->scenarioInstructions << std::endl;
            return scnfile;
        }
    }

    return genie::ScnFilePtr();
}

//------------------------------------------------------------------------------
genie::SlpFilePtr ResourceManager::getSlp(sf::Uint32 id, const ResourceType type)
{
    genie::SlpFilePtr slp_ptr;

    switch (type) {
    case Interface:
        return m_interfaceFile->getSlpFile(id);
        break;
    case Graphics:
        return m_graphicsFile->getSlpFile(id);
        break;
    case Terrain:
        return m_terrainFile->getSlpFile(id);
        break;
    case GameData:
    case Undefined:
    default:
        break;
    }

    if (slp_ptr) {
        return slp_ptr;
    }

    for (const std::shared_ptr<genie::DrsFile> &drsFile : type == GameData ? m_gamedataFiles : m_allFiles) {
        slp_ptr = drsFile->getSlpFile(id);
        if (slp_ptr) {
            return slp_ptr;
        }
    }

    log.debug("No slp file with id [%d] found!", id);
    return slp_ptr;
}

//------------------------------------------------------------------------------
res::GraphicPtr ResourceManager::getGraphic(Uint32 id)
{
    res::GraphicPtr graph;

    if (graphics_.find(id) != graphics_.end()) {
        graph = graphics_[id];
    } else {
        graph = std::make_shared<res::Graphic>(id);

        if (!graph->load()) {
            return nullptr;
        }

        graphics_[id] = graph;
    }

    return graph;
}

//------------------------------------------------------------------------------
res::TerrainPtr ResourceManager::getTerrain(unsigned int type)
{
    if (terrains_.find(type) != terrains_.end()) {
        return terrains_[type];
    }

    res::TerrainPtr terrain = res::TerrainPtr(new res::Terrain(type));
    terrain->load();

    terrains_[type] = terrain;

    return terrain;
}

genie::BlendModePtr ResourceManager::getBlendmode(unsigned int id)
{
    if (!blendomatic_file_) {
        log.warn("No blendomatic file loaded");
        return nullptr;
    }

    return blendomatic_file_->getBlendMode(id);
}

//------------------------------------------------------------------------------
genie::PalFilePtr ResourceManager::getPalette(sf::Uint32 id)
{
    static genie::PalFilePtr defaultPalette;
    if (id == 50500 && defaultPalette) {
        return defaultPalette;
    }

    genie::PalFilePtr pal_ptr = m_interfaceFile->getPalFile(id);
    if (pal_ptr) {
        if (id == 50500) {
            defaultPalette = pal_ptr;
        }
        return pal_ptr;
    }

    for (std::shared_ptr<genie::DrsFile> drsFile : m_allFiles) {
        pal_ptr = drsFile->getPalFile(id);

        if (pal_ptr) {
            if (id == 50500) {
                defaultPalette = pal_ptr;
            }

            return pal_ptr;
        }
    }

    log.warn("No pal file with id [%u] found!", id);
    return pal_ptr;
}

//------------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
}

//------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
}

//------------------------------------------------------------------------------
bool ResourceManager::initialize(const std::string &dataPath, const genie::GameVersion gameVersion)
{
    log.debug("Initializing ResourceManager");

    m_dataPath = dataPath;
    m_gameVersion = gameVersion;

    try {
        const std::vector<std::string> gamedataFiles({
                { "gamedata.drs" },
                { "gamedata_x1.drs" },
                { "gamedata_x1_p1.drs" },
        });

        m_gamedataFiles = loadDrs(gamedataFiles);
        if (m_gamedataFiles.empty()) {
            std::cerr << "Failed to find any gamedata files in " << dataPath << std::endl;
            return false;
        }

        m_interfaceFile = loadDrs(m_dataPath + "interfac.drs");
        if (!m_interfaceFile) {
            log.error("Failed to load interface file");
            return false;
        }

        m_graphicsFile = loadDrs(m_dataPath + "graphics.drs");
        if (!m_graphicsFile) {
            log.error("Failed to load graphics file");
            return false;
        }

        m_terrainFile = loadDrs(m_dataPath + "terrain.drs");
        if (!m_terrainFile) {
            log.error("Failed to load terrain file");
            return false;
        }

        const std::vector<std::string> soundFiles({
                { "sounds.drs" },
                { "sounds_x1.drs" },
        });

        m_soundFiles = loadDrs(soundFiles);

        if (m_soundFiles.empty()) {
            std::cerr << "Failed to find any sound files in " << dataPath << std::endl;
            return false;
        }

        blendomatic_file_ = std::make_unique<genie::BlendomaticFile>();
        std::string blendomaticPath = dataPath + "blendomatic.dat";
        blendomatic_file_->load(blendomaticPath.c_str());
    } catch (const std::exception &error) {
        log.error("Failed to load resource: %", error.what());
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
ResourceManager::DrsFileVector ResourceManager::loadDrs(const std::vector<std::string> &filenames)
{
    DrsFileVector files;

    for (const std::string &filename : filenames) {
        const std::string filePath = m_dataPath + filename;
        if (!filesystem::exists(filePath)) {
            log.debug("Skipping non-existing file %", filePath);
            continue;
        }

        std::shared_ptr<genie::DrsFile> file = loadDrs(filePath);
        if (!file) {
            continue;
        }
        files.push_back(file);
    }

    return files;
}

std::shared_ptr<genie::DrsFile> ResourceManager::loadDrs(const std::string filePath)
{
    if (!filesystem::exists(filePath)) {
        log.debug("Can't find file %", filePath);
        return nullptr;
    }

    std::shared_ptr<genie::DrsFile> file = std::make_shared<genie::DrsFile>();
    file->setGameVersion(m_gameVersion);
    file->load(filePath.c_str());
    m_allFiles.push_back(file);
    return file;
}
