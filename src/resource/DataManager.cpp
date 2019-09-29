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

#include "DataManager.h"

#include <genie/dat/PlayerColour.h>
#include <genie/dat/Research.h>
#include <genie/dat/Sound.h>
#include <genie/dat/Techage.h>
#include <genie/dat/TerrainBlock.h>
#include <genie/dat/TerrainRestriction.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/../UnitCommand.h>
#include <filesystem>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>

#include "genie/dat/Civ.h"
#include "genie/dat/Graphic.h"
#include "genie/dat/Terrain.h"

#include "LanguageManager.h"

#include <filesystem>


namespace {
    // Because I like to return const refs, and also do error checking
    static const genie::Unit nullUnit;
    static const genie::Tech nullTech;
    static const genie::Civ nullCiv;
    static const genie::Effect nullEffect;
    static const genie::TerrainRestriction nullTerrainRestriction;
    static const genie::PlayerColour nullPlayerColor;
    static const genie::Terrain nullTerrain;
    static const genie::Sound nullSound;
    static const std::vector<genie::Task> nullTaskList;
}

DataManager &DataManager::Inst()
{
    static DataManager inst;
    return inst;
}

const genie::Graphic &DataManager::getGraphic(unsigned int id) const
{
    static const genie::Graphic nullGraphic;
    if (id >= dat_file_.Graphics.size()) {
        WARN << "graphic id" << id << "is out of range";
        return nullGraphic;
    }
    return dat_file_.Graphics[id];
}

const genie::Tech &DataManager::getTech(unsigned int id) const
{
    if (id >= dat_file_.Techs.size()) {
        return nullTech;
    }

    return dat_file_.Techs.at(id);
}

const genie::Terrain &DataManager::getTerrain(unsigned int id) const
{
    if (id >= dat_file_.TerrainBlock.Terrains.size()) {
        WARN << "terrain id" << id << "is out of range";
        return nullTerrain;
    }

    return dat_file_.TerrainBlock.Terrains[id];
}

const genie::Effect &DataManager::getEffect(unsigned int id) const
{
    if (id >= dat_file_.Effects.size()) {
        WARN << "terrain id" << id << "is out of range";
        return nullEffect;
    }

    return dat_file_.Effects[id];

}

const genie::TerrainRestriction &DataManager::getTerrainRestriction(unsigned int id) const
{
    if (id >= dat_file_.TerrainRestrictions.size()) {
        WARN << "terrain restriction" << id << "out of range";
        return nullTerrainRestriction;
    }

    return dat_file_.TerrainRestrictions[id];
}

const genie::PlayerColour &DataManager::getPlayerColor(unsigned int id) const
{
    if (id >= dat_file_.PlayerColours.size()) {
        WARN << "invalid player color id" << id;
        return nullPlayerColor;
    }

    return dat_file_.PlayerColours[id];
}

const genie::Sound &DataManager::getSound(unsigned int id) const
{
    if (id >= dat_file_.Sounds.size()) {
        WARN << "Invalid sound ID" << id;
        return nullSound;
    }

    return dat_file_.Sounds[id];
}

const std::vector<genie::Task> &DataManager::getTasks(unsigned int id) const
{
    if (id >= dat_file_.UnitHeaders.size()) {
//        WARN << "Invalid unit id, can't give tasks" << id;
        return nullTaskList;
    }

    return dat_file_.UnitHeaders[id].TaskList;
}

std::string DataManager::gameName(const genie::GameVersion version)
{
    static const std::unordered_map<genie::GameVersion, std::string> versionNames({
        { genie::GV_TEST, "Test" },
        { genie::GV_MIK, "Mike" },
        { genie::GV_DAVE, "Dave" },
        { genie::GV_MATT, "Matt" },
        { genie::GV_AoEB, "Age of Empires Beta" },
        { genie::GV_AoE, "Age of Empires" },
        { genie::GV_RoR, "Age of Empires: Rise of Rome" },
        { genie::GV_Tapsa, "Tapsa" },
        { genie::GV_T2, "Tapsa Test 2" },
        { genie::GV_T3, "Tapsa Test 3" },
        { genie::GV_T4, "Tapsa Test 4" },
        { genie::GV_T5, "Tapsa Test 5" },
        { genie::GV_T6, "Tapsa Test 6" },
        { genie::GV_T7, "Tapsa Test 7" },
        { genie::GV_T8, "Tapsa Test 8" },
        { genie::GV_AoKE3, "Age of Empires 2: Age of Kings E3 Preview" },
        { genie::GV_AoKA, "Age of Empires 2: Age of Kings Alpha" },
        { genie::GV_AoKB, "Age of Empires 2: Age of Kings Beta" },
        { genie::GV_AoK, "Age of Empires 2: Age of Kings" },
        { genie::GV_TC, "Age of Empires 2: The Conquerors" },
        { genie::GV_Cysion, "Age of Empires 2: Cysion" },
        { genie::GV_SWGB, "Star Wars: Galactic Battlegrounds" },
        { genie::GV_CC, "Star Wars: Galactic Battlegrounds: Clone Campaigns" }
    });
    if (versionNames.find(version) == versionNames.end()) {
        static const std::string unknownString("Unknown game");
        return unknownString;
    }

    return versionNames.at(version);



}

std::string DataManager::genieVersionString(const genie::GameVersion version)
{

    static const std::unordered_map<genie::GameVersion, std::string> engineVersions ({
        { genie::GV_MATT, "<6.92" },
        { genie::GV_AoEB, "7.04 - 7.11" },
        { genie::GV_AoE, "7.2" },
        { genie::GV_RoR, "7.24" },
        { genie::GV_AoKE3, "9.36" },
        { genie::GV_AoKA, "10.19" },
        { genie::GV_AoKB, "11.05" },
        { genie::GV_AoK, "11.5" },
        { genie::GV_TC, "11.76 - 12.0" },
        { genie::GV_Cysion, "12.0" },
        { genie::GV_SWGB, "1.0" },
        { genie::GV_CC, "1.1" }
    });
    if (engineVersions.find(version) == engineVersions.end()) {
        static const std::string unknownString("Unknown version");
        return unknownString;
    }

    return engineVersions.at(version);
}

genie::GameVersion DataManager::gameVersion() const
{
    return dat_file_.getGameVersion();
}

const std::vector<genie::Civ> &DataManager::civilizations() const
{
    return dat_file_.Civs;
}

const genie::Civ &DataManager::civilization(unsigned int id) const
{
    if (id >= dat_file_.Civs.size()) {
        WARN << "civ out of range";
        return nullCiv;
    }

    return dat_file_.Civs[id];
}

bool DataManager::initialize(const std::string &gamePath)
{
    std::vector<std::pair<std::string, genie::GameVersion>> datFilenames({
//        {"empires2_x2_p1.dat", genie::GV_TC  }, // forgotten kingdoms, TODO
        {"empires2_x1_p1.dat", genie::GV_TC  }, // the conquerors, patch 1
        {"empires2_x1.dat",    genie::GV_TC  }, // the conquerors
        {"empires2.dat",       genie::GV_AoK }, // age of kings
        {"empires_x1.dat",     genie::GV_RoR },
        {"Empires.dat",        genie::GV_AoE },
    });

    std::string dataPath = gamePath + "/Data/";
    if (!std::filesystem::exists(dataPath)) {
        DBG << dataPath << "doesn't exist, trying HD";
        dataPath = gamePath + "/resources/_common/dat/";
        m_isHd = true;
    }

    if (!std::filesystem::exists(dataPath)) {
        WARN << "Failed to find neither normal or HD data folder";
        return false;
    }
    DBG << "Loading from" << dataPath;

    std::string filePath;
    for (const std::pair<std::string, genie::GameVersion> &datfile : datFilenames) {
        std::string potential = dataPath + datfile.first;
        if (std::filesystem::exists(potential)) {
            filePath = potential;
            dat_file_.setGameVersion(datfile.second);
            break;
        }
    }

    if (filePath.empty()) {
        WARN << "Failed to find any dat files in" << dataPath;
        return false;
    }

    dat_file_.load(filePath);

    return true;
}
