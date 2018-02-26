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
#include "DataManager.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <global/Config.h>

#include <genie/resource/DrsFile.h>
#include <genie/resource/UIFile.h>

#include <experimental/filesystem>
#include <unordered_map>

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
    // wtf
    if (res == UiResolution::Ui1280x1024 && civ > UiCiv::Spanish) {
        return getSlp(51142 + uint32_t(civ), ResourceType::Interface);
    }

    return getSlp(uint32_t(res) + uint32_t(civ), ResourceType::Interface);
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

genie::SlpFramePtr ResourceManager::getTemplatedSlp(unsigned int slp, const genie::SlpTemplateFile::Slope slope)
{
    return m_stemplatesFile->getFrame(getSlp(slp, ResourceType::Terrain), slope);
}

//------------------------------------------------------------------------------
genie::SlpFilePtr ResourceManager::getSlp(sf::Uint32 id, const ResourceType type)
{
    genie::SlpFilePtr slp_ptr;

    switch (type) {
    case ResourceType::Interface:
        return m_interfaceFile->getSlpFile(id);
    case ResourceType::Graphics:
        return m_graphicsFile->getSlpFile(id);
    case ResourceType::Terrain:
        return m_terrainFile->getSlpFile(id);
    case ResourceType::GameData:
        for (const std::shared_ptr<genie::DrsFile> &drsFile : m_gamedataFiles) {
            slp_ptr = drsFile->getSlpFile(id);
            if (slp_ptr) {
                return slp_ptr;
            }
        }
        log.debug("failed to find % in gamedata files, falling back to all files", id);
        break;
    case ResourceType::Undefined:
    default:
        break;
    }

    if (slp_ptr) {
        return slp_ptr;
    }

    for (const std::shared_ptr<genie::DrsFile> &drsFile : m_allFiles) {
        slp_ptr = drsFile->getSlpFile(id);
        if (slp_ptr) {
            return slp_ptr;
        }
    }

    log.debug("No slp file with id [%] found!", id);
    return slp_ptr;
}

//------------------------------------------------------------------------------
res::GraphicPtr ResourceManager::getGraphic(Uint32 id)
{
    res::GraphicPtr graph;

    if (graphics_.find(id) != graphics_.end()) {
        graph = graphics_[id];
    } else {
        graph = std::make_shared<res::Graphic>(DataManager::Inst().getGraphic(id));

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

std::string ResourceManager::uiFilename(const ResourceManager::UiResolution resolution, const ResourceManager::UiCiv civ)
{
    std::string ret = "game_";
    switch (resolution) {
    case (UiResolution::Ui800x600):
      ret += "a";
        break;
    case (UiResolution::Ui1024x768):
      ret += "b";
        break;
    case (UiResolution::Ui1280x1024):
      ret += "c";
        break;
    case (UiResolution::Ui1600x1200):
      ret += "d";
        break;
    }
    ret += std::to_string(int(civ));
    ret += ".slp";

    return ret;
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

        m_interfaceFile = loadDrs("interfac.drs");
        if (!m_interfaceFile) {
            log.error("Failed to load interface file");
            return false;
        }

        m_graphicsFile = loadDrs("graphics.drs");
        if (!m_graphicsFile) {
            log.error("Failed to load graphics file");
            return false;
        }

        m_terrainFile = loadDrs("terrain.drs");
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
    std::cerr << "Loaded " << m_allFiles.size() << " files" << std::endl;

    return true;
}

int ResourceManager::filenameID(const std::string &filename)
{
    const std::unordered_map<std::string, int> idMap = {
        { "btncmd.shp", 50721    },
        { "btngame2x.shp", 50754 },
        { "btngame.shp", 50751   },
        { "btnmain.shp", 52064   },
        { "btntech.shp", 50729   },
        { "btnunit.shp", 50730   },
        { "dlg_plbn.shp", 50746  },
        { "groupnum.shp", 50403  },
        { "health.shp", 50745    },
        { "ico_game.shp", 50752  },
        { "ico_misc.shp", 53011  },
        { "ico_unit.shp", 50730  },
        { "itemicon.shp", 50731  },
        { "mcursors.shp", 51000  },
        { "meet.shp", 53010      },
        { "moveto.shp", 50405    },
        { "sundial.shp", 50764   },
        { "tradicon.shp", 50732  },
        { "unithalo.shp", 53003  },
        { "waypoint.shp", 50404  },

        { "ico_bld1.shp", 50705  },
        { "ico_bld2.shp", 50706  },
        { "ico_bld3.shp", 50707  },
        { "ico_bld4.shp", 50708  },

        { "btnbrda2.shp", 50715   },
        { "btnbrdb2.shp", 50719   },
        { "btnbrdc2.shp", 50749   },

        { "2logos.slp", 53012     },
        { "AchDecal.slp", 50766   },
        { "AchTeam.slp", 50769    },
        { "arrows.slp", 53004     },
        { "btn_hist.slp", 50613   },
        { "btn_mute.slp", 50791   },
        { "c_logo.slp", 53207     },
        { "colbar.slp", 50792     },
        { "defcheck.slp", 52002   },
        { "eslogo1.slp", 53202    },
        { "eslogo2.slp", 53203    },
        { "g_wtr.slp", 15002      },
        { "hourglas.slp", 53001   },
        { "icomap_b.slp", 50788   },
        { "icomap_c.slp", 50789   },
        { "icomap_d.slp", 50790   },
        { "mslogo1.slp", 53200    },
        { "mslogo2.slp", 53201    },
        { "objtabs.slp", 53005    },
        { "PNBnr1.slp", 50762     },
        { "PNBnr2.slp", 50767     },
        { "rollback.slp", 50150   },
        { "sat_btn.slp", 50768    },
        { "sat_tabs.slp", 50765   },
        { "sshot_text.slp", 53204 },
        { "techages.slp", 50342   },
        { "techback.slp", 50341   },
        { "technodex.slp", 53206  },
        { "tech_tile.slp", 50343  },
        { "tml_bck.slp", 50763    },
        { "ttx.slp", 53211        },
        { "viccheck.slp", 52001   },
        { "xmain.slp", 50189      },
    };

    if (idMap.find(filename) != idMap.end()) {
        return idMap.at(filename);
    } else {
        log.error("Failed to find known id for filename %", filename);
        return -1;
    }
}

//------------------------------------------------------------------------------
ResourceManager::DrsFileVector ResourceManager::loadDrs(const std::vector<std::string> &filenames)
{
    DrsFileVector files;

    for (const std::string &filename : filenames) {
        std::shared_ptr<genie::DrsFile> file = loadDrs(filename);
        if (!file) {
            continue;
        }
        files.push_back(file);
    }

    return files;
}

inline std::string toLowercase(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

std::shared_ptr<genie::DrsFile> ResourceManager::loadDrs(std::string filename)
{
    if (!filesystem::exists(m_dataPath + filename)) {
        std::string compareFilename = toLowercase(filename);
        filename = "";
        for (const filesystem::directory_entry &entry : filesystem::directory_iterator(m_dataPath)) {
            std::string candidate = toLowercase(entry.path().filename());
            if (candidate == compareFilename) {
                filename = entry.path().filename();
                break;
            }
        }
        if (filename.empty()) {
            //log.debug("Can't find file %", filename);
            return nullptr;
        }
    }

    std::shared_ptr<genie::DrsFile> file = std::make_shared<genie::DrsFile>();
    file->setGameVersion(m_gameVersion);
    file->load((m_dataPath + filename).c_str());
    m_allFiles.push_back(file);
    return file;
}
