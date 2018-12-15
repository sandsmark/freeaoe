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

#include "global/Config.h"
#include "genie/dat/Graphic.h"
#include "genie/dat/Civ.h"
#include "genie/dat/Terrain.h"

#include "LanguageManager.h"

#include <filesystem>

const genie::Unit DataManager::nullUnit;
const genie::Tech DataManager::nullTech;
const genie::Civ DataManager::nullCiv;

DataManager &DataManager::Inst()
{
    static DataManager inst;
    return inst;
}

const genie::Graphic &DataManager::getGraphic(unsigned int id)
{
    static const genie::Graphic nullGraphic;
    if (id >= dat_file_.Graphics.size()) {
        WARN << "graphic id" << id << "is out of range";
        return nullGraphic;
    }
    return dat_file_.Graphics[id];
}

const genie::Tech &DataManager::getTech(unsigned int id)
{
    if (id >= dat_file_.Techs.size()) {
        return nullTech;
    }

    return dat_file_.Techs.at(id);
}

const genie::Terrain &DataManager::getTerrain(unsigned int id)
{
    if (id >= dat_file_.TerrainBlock.Terrains.size()) {
        static genie::Terrain nullterrain;
        WARN << "terrain id" << id << "is out of range";
        return nullterrain;
    }

    return dat_file_.TerrainBlock.Terrains[id];
}

genie::TerrainRestriction DataManager::getTerrainRestriction(unsigned int id)
{
    return dat_file_.TerrainRestrictions[id];
}

const genie::PlayerColour &DataManager::getPlayerColor(unsigned int id)
{
    return dat_file_.PlayerColours[id];
}

const genie::TerrainBlock &DataManager::terrainBlock()
{
    return dat_file_.TerrainBlock;
}

std::string DataManager::gameName(const genie::GameVersion version)
{
    switch (version) {
    case genie::GV_AoE:
        return "Age of Empires";
    case genie::GV_RoR:
        return "Rise of Rome";
    case genie::GV_AoK:
        return "Age of Empires 2: Age of Kings";
    case genie::GV_TC:
        return "Age of Empires 2: The Conquerors";
    default:
        return "Unknown";
    }
}
genie::GameVersion DataManager::gameVersion() const
{
    return dat_file_.getGameVersion();
}

const std::vector<genie::Civ> &DataManager::civilizations()
{
    return dat_file_.Civs;
}

const genie::Civ &DataManager::civilization(unsigned int id)
{
    if (id >= dat_file_.Civs.size()) {
        WARN << "civ out of range";
        return nullCiv;
    }

    return dat_file_.Civs[id];
}

const genie::DatFile &DataManager::datFile()
{
    return Inst().dat_file_;
}

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

bool DataManager::initialize(const std::string &dataPath)
{

    std::vector<std::pair<std::string, genie::GameVersion>> datFilenames({
        {"empires2_x1_p1.dat", genie::GV_TC  }, // the conquerors, patch 1
        {"empires2_x1.dat",    genie::GV_TC  }, // the conquerors
        {"empires2.dat",       genie::GV_AoK }, // age of kings
        {"empires_x1.dat",     genie::GV_RoR },
        {"Empires.dat",        genie::GV_AoE },
    });

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

    try {
        dat_file_.load(filePath);
    } catch (const std::exception &error) {
        WARN << "Failed to load dat file" << filePath << error.what();
        return false;
    }

    return true;
}
