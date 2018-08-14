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

#include "AssetManager.h"
#include "DataManager.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <global/Config.h>

#include <genie/resource/DrsFile.h>
#include <genie/resource/UIFile.h>
#include <core/Utility.h>

#include <filesystem>

#include <unordered_map>

//------------------------------------------------------------------------------
AssetManager *AssetManager::Inst()
{
    static AssetManager rm;
    return &rm;
}

genie::SlpFilePtr AssetManager::getSlp(const std::string &name, const ResourceType type)
{
    return getSlp(filenameID(name), type);
}

genie::SlpFilePtr AssetManager::getUiOverlay(const AssetManager::UiResolution res, const AssetManager::UiCiv civ)
{
    // wtf
    if (res == UiResolution::Ui1280x1024 && civ > UiCiv::Spanish) {
        return getSlp(51142 + uint32_t(civ), ResourceType::Interface);
    }

    return getSlp(uint32_t(res) + uint32_t(civ), ResourceType::Interface);
}

genie::ScnFilePtr AssetManager::getScn(unsigned int id)
{
    for (const std::shared_ptr<genie::DrsFile> &drsFile : m_gamedataFiles) {
        genie::ScnFilePtr scnfile = drsFile->getScnFile(id);

        if (scnfile) {
            DBG << "found scn file version" << scnfile->version;
            DBG << scnfile->scenarioInstructions;
            return scnfile;
        }
    }

    return genie::ScnFilePtr();
}

std::shared_ptr<genie::UIFile> AssetManager::getUIFile(const std::string &name)
{
    return m_interfaceFile->getUIFile(filenameID(name));
}

std::shared_ptr<uint8_t> AssetManager::getWavPtr(unsigned int id)
{
    std::weak_ptr<uint8_t> weakPtr = m_wavCache[id];
    std::shared_ptr<uint8_t> wavPtr = weakPtr.lock();
    if (wavPtr) {
        return wavPtr;
    }

    m_wavCache.erase(id);

    for (const std::shared_ptr<genie::DrsFile> &drsFile : m_soundFiles) {
        wavPtr = drsFile->getWavPtr(id);
        if (wavPtr) {
            m_wavCache[id] = wavPtr;
            return wavPtr;
        }
    }
    DBG << "failed to find wav file for" << id;
    return nullptr;
}

//------------------------------------------------------------------------------
genie::SlpFilePtr AssetManager::getSlp(sf::Uint32 id, const ResourceType type)
{
    genie::SlpFilePtr slp_ptr;
    if (m_nonExistentSlps.count(id)) {
        return slp_ptr;
    }

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
        DBG << "failed to find" << id << "in gamedata files, falling back to all files";
        break;
    case ResourceType::Undefined:
        [[fallthrough]];
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

    m_nonExistentSlps.insert(id);

    DBG << "No slp file with id" << id << "found!";
    return slp_ptr;
}

//------------------------------------------------------------------------------
GraphicPtr AssetManager::getGraphic(Uint32 id)
{
    GraphicPtr graph;

    if (graphics_.find(id) != graphics_.end()) {
        graph = graphics_[id];
    } else {
        graph = std::make_shared<Graphic>(DataManager::Inst().getGraphic(id));

        graphics_[id] = graph;
    }

    return graph;
}

//------------------------------------------------------------------------------
TerrainPtr AssetManager::getTerrain(unsigned int id)
{
    if (terrains_.find(id) != terrains_.end()) {
        return terrains_[id];
    }

    TerrainPtr terrain = std::make_shared<Terrain>(id);
    terrain->load();

    terrains_[id] = terrain;

    return terrain;
}

const genie::PalFile &AssetManager::getPalette(const std::string &name)
{
    return getPalette(filenameID(name));
}

const genie::BlendMode &AssetManager::getBlendmode(unsigned int id)
{
    if (!blendomatic_file_) {
        WARN << "No blendomatic file loaded";
        return genie::BlendMode::null;
    }

    return blendomatic_file_->getBlendMode(id);
}

//------------------------------------------------------------------------------
const genie::PalFile &AssetManager::getPalette(sf::Uint32 id)
{
    const genie::PalFile &palette = m_interfaceFile->getPalFile(id);
    if (palette.isValid()) {
        return palette;
    }

    for (const std::shared_ptr<genie::DrsFile> &drsFile : m_allFiles) {
        const genie::PalFile &palette = drsFile->getPalFile(id);

        if (palette.isValid()) {
            return palette;
        }
    }

    WARN << "No pal file with id" << id << "found!";

    return palette;
}

//------------------------------------------------------------------------------
AssetManager::AssetManager()
{
}

//------------------------------------------------------------------------------
AssetManager::~AssetManager()
{
}

std::string AssetManager::uiFilename(const AssetManager::UiResolution resolution, const AssetManager::UiCiv civ)
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
bool AssetManager::initialize(const std::string &dataPath, const genie::GameVersion gameVersion)
{
    DBG << "Initializing AssetManager";

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
            WARN << "Failed to find any gamedata files in" << dataPath;
            return false;
        }

        m_interfaceFile = loadDrs("interfac.drs");
        if (!m_interfaceFile) {
            WARN << "Failed to load interface file";
            return false;
        }

        m_graphicsFile = loadDrs("graphics.drs");
        if (!m_graphicsFile) {
            WARN << "Failed to load graphics file";
            return false;
        }

        m_terrainFile = loadDrs("terrain.drs");
        if (!m_terrainFile) {
            WARN << "Failed to load terrain file";
            return false;
        }

        const std::vector<std::string> soundFiles({
                { "sounds.drs" },
                { "sounds_x1.drs" },
        });

        m_soundFiles = loadDrs(soundFiles);

        if (m_soundFiles.empty()) {
            WARN << "Failed to find any sound files in" << dataPath;
            return false;
        }

        blendomatic_file_ = std::make_unique<genie::BlendomaticFile>();
        std::string blendomaticPath = dataPath + "blendomatic.dat";
        blendomatic_file_->load(blendomaticPath);


        m_stemplatesFile = std::make_unique<genie::SlpTemplateFile>();
        m_stemplatesFile->load(dataPath + "STemplet.dat");
        m_stemplatesFile->filtermapFile.load(dataPath + "FilterMaps.dat");
        m_stemplatesFile->filtermapFile.patternmasksFile.load(dataPath + "PatternMasks.dat");
        m_stemplatesFile->filtermapFile.patternmasksFile.icmFile.load(dataPath + "view_icm.dat");
        m_stemplatesFile->filtermapFile.patternmasksFile.lightmapFile.load(dataPath + "lightMaps.dat");
    } catch (const std::exception &error) {
        WARN << "Failed to load resource" << error.what();
        return false;
    }
    DBG << "Loaded" << m_allFiles.size() << "files";

    return true;
}

int AssetManager::filenameID(const std::string &filename)
{
    const std::unordered_map<std::string, int> idMap = {
        // Various button icons
        { "btncmd.shp", 50721     },
        { "btnunit.shp",  50730   },
        { "btntech.shp", 50729    },
        { "btngame2x.shp", 50754  },
        { "tradicon.shp", 50732   },

        { "btn_hist.slp", 50613   },
        { "btn_mute.slp", 50791   },

        // Various icons
        { "ico_unit.shp", 50730   }, // same as btnunit.shp
        { "ico_game.shp", 50752   },
        { "ico_misc.shp", 53011   },
        { "ico_bld1.shp", 50705   },
        { "ico_bld2.shp", 50706   },
        { "ico_bld3.shp", 50707   },
        { "ico_bld4.shp", 50708   },
        { "itemicon.shp", 50731   },

        // Minimap
        { "icomap_a.slp", 50787   },
        { "icomap_b.slp", 50788   },
        { "icomap_c.slp", 50789   },
        { "icomap_d.slp", 50790   },

        // Various graphics
        { "groupnum.shp", 50403   }, // just numbers for unit groups
        { "health.shp", 50745     }, // Different health bars
        { "mcursors.shp", 51000   },
        { "moveto.shp", 50405     },
        { "sundial.shp", 50764    }, // Age upgrade progress?
        { "unithalo.shp", 53003   }, // Box around unit icon
        { "waypoint.shp", 50404   },
        { "arrows.slp", 53004     },
        { "hourglas.slp", 53001   },
        { "dlg_plbn.shp", 50746   }, // Flag thing

        // Generic button background
        { "btnbrda2.shp", 50715   },
        { "btnbrdb2.shp", 50719   },
        { "btnbrdc2.shp", 50749   },
        { "sat_btn.slp", 50768    },

        // Tech tree
        { "techages.slp", 50342   },
        { "techback.slp", 50341   },
        { "technodex.slp", 53206  },
        { "tech_tile.slp", 50343  },
        { "ttx.slp", 53211        }, // unit not available

        // Various backgrounds
        { "xmain.slp", 50189      }, // Mainscreen
        { "objtabs.slp", 53005    },
        { "rollback.slp", 50150   }, // Checkered gray
        { "sat_tabs.slp", 50765   }, // Tab pane victory screen
        { "tml_bck.slp", 50763    }, // Texture victory screen
        { "viccheck.slp", 52001   },
        { "scr2.slp", 50100       }, // 800x600
        { "scr2b.slp", 50101      }, // 1024x768
        { "scr2c.slp", 50102      }, // 1280x1024
        { "scrstart.slp", 50163   },
        { "scrstart.pal", 50563   },


        // Logos
        { "c_logo.slp", 53207     },
        { "2logos.slp", 53012     },
        { "mslogo1.slp", 53200    },
        { "mslogo2.slp", 53201    },
        { "eslogo1.slp", 53202    },
        { "eslogo2.slp", 53203    },

        // Achievements
        { "AchDecal.slp", 50766   },
        { "AchTeam.slp", 50769    },

        // History view stuff
        { "hist_pic.sin", 50162   },
        { "hist_picx.sin", 53209  },

        // Old unused stuff
        { "colbar.slp", 50792     }, // Colored bars
        { "defcheck.slp", 52002   },
        { "g_wtr.slp", 15002      },
        { "btngame.shp", 50751    },
        { "btnmain.shp", 52064    },
        { "meet.shp", 53010       }, // Meat?
        { "PNBnr1.slp", 50762     }, // flags
        { "PNBnr2.slp", 50767     }, // flags2
        { "sshot_text.slp", 53204 },

        // Sounds
        { "archupg.wav", 50325    },
        { "artheld.wav", 50311    },
        { "artlost.wav", 50312    },
        { "atakwarn.wav", 50315   },
        { "athiesm.wav", 50368    },
        { "button1.wav", 50300    },
        { "button2.wav", 50301    },
        { "button3.wav", 50331    },
        { "button4.wav", 50332    },
        { "button5.wav", 50333    },
        { "button6.wav", 50334    },
        { "button7.wav", 50335    },
        { "button8.wav", 50336    },
        { "button9.wav", 50337    },
        { "buy.wav", 50360        },
        { "cantdo.wav", 50303     },
        { "capgaia.wav", 50356    },
        { "capsheep.wav", 50355   },
        { "chatrcvd.wav", 50302   },
        { "convdone.wav", 50314   },
        { "convwarn.wav", 50313   },
        { "enemwarn.wav", 50316   },
        { "farmdied.wav", 50328   },
        { "flare.wav", 50317      },
        { "flaresnd.wav", 50327   },
        { "fortupg.wav", 50326    },
        { "gatel.wav", 50362      },
        { "gateu.wav", 50363      },
        { "gather.wav", 50329     },
        { "housing.wav", 50322    },
        { "loosebld.wav", 50323   },
        { "lost.wav", 50321       },
        { "mdone.wav", 50309      },
        { "mkilled.wav", 50310    },
        { "mstart.wav", 50308     },
        { "needhous.wav", 50354   },
        { "needres.wav", 50318    },
        { "objctive.wav", 50364   },
        { "pdropped.wav", 50307   },
        { "pkilled.wav", 50306    },
        { "pscreen.wav", 50359    },
        { "puprelic.wav", 50365   },
        { "resdone.wav", 50305    },
        { "resdone2.wav", 50330   },
        { "rollover.wav", 50338   },
        { "sell.wav", 50361       },
        { "spies.wav", 50367      },
        { "takebld.wav", 50324    },
        { "townbell.wav", 50357   },
        { "townrcal.wav", 50358   },
        { "tribute.wav", 50304    },
        { "wolfwarn.wav", 50366   },
        { "won.wav", 50320        },


        /*
         * UI files
         */
        { "main.sin", 50081       },
        { "xmain.sin", 50089      },
        { "dlg_cha1.sin", 50017   },
        { "dlg_cha2.sin", 50019   },
        { "dlg_dip.sin", 50014    },
        { "dlg_gam.sin", 50018    },
        { "dlg_men.sin", 50015    },
        { "dlg_obj.sin", 50016    },
        { "dlg_objx.sin", 50021   },

        // Status screen/dialog
        { "scr1.sin", 50051       },

        // single player, select scenario, scenario editor,
        // save game, multiplayer save game, multiplayer wait, load multiplayer saved,
        // load saved, campaign select, aftermath, status screen
        { "scr2.sin", 50052       },

        // Options
        { "scr2p.sin", 50084      },

        // For multiplayer (create lobby, join, replay, scenario?)
        { "scr3.sin", 50053       },

        // campaign editor
        { "scr4.sin", 50054       },

        // scenario editor
        { "scr5.sin", 50055       },

        // game screen
        { "scr6.sin", 50056       },

        // one button tech tree, duplicate name for the main game screen
        // { "scr6.sin", 50007       },

        // Mission dialog
        { "scr9.sin", 50060       },

        // Achievements screen
        { "scr10.sin", 50061      },

        { "scr_cred.sin", 50059   },
        { "scr_hist.sin", 50062   },
        { "scrstart.sin", 50063   },
        { "scr_stms.sin", 50085   },
        { "xcredits.sin", 50088   },

        // BMP files
        { "map1280.bmp", 50409    },
        { "map1024.bmp", 50408    },
        { "map800.bmp", 50411     },
        { "map640.bmp", 50401     },

        // Scenarios
        { "real_world_spain.scx", 56001     },
        { "real_world_britain.scx", 56002   },
        { "real_world_mideast.scx", 56003   },
        { "real_world_texas.scx", 56004     },
        { "real_world_italy.scx", 56005     },
        { "real_world_caribbean.scx", 56006 },
        { "real_world_france.scx", 56007    },
        { "real_world_jutland.scx", 56008   },
        { "real_world_nippon.scx", 56009    },
        { "real_world_byzantium.scx", 56010 },
    };

    if (idMap.find(filename) == idMap.end()) {
        WARN << "Failed to find known id for filename" << filename;
        return -1;
    }

    return idMap.at(filename);
}

std::string AssetManager::findFile(const std::string &filename) const
{
    if (std::filesystem::exists(m_dataPath + filename)) {
        return m_dataPath + filename;
    }

    std::string compareFilename = util::toLowercase(filename);
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(m_dataPath)) {
        std::string candidate = util::toLowercase(entry.path().filename().string());
        if (candidate == compareFilename) {
            return entry.path().filename().string();
        }
    }

    DBG << "Can't find file" << filename;
    return std::string();
}

//------------------------------------------------------------------------------
AssetManager::DrsFileVector AssetManager::loadDrs(const std::vector<std::string> &filenames)
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

std::shared_ptr<genie::DrsFile> AssetManager::loadDrs(const std::string &filename)
{
    std::string filePath = findFile(filename);

    if (filePath.empty()) {
        return nullptr;
    }

    std::shared_ptr<genie::DrsFile> file = std::make_shared<genie::DrsFile>();
    file->setGameVersion(m_gameVersion);
    file->load(filePath);

    m_allFiles.push_back(file);

    return file;
}
