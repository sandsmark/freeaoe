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

Logger &DataManager::log = Logger::getLogger("freeaoe.DataManager");

DataManager &DataManager::Inst()
{
    static DataManager inst;
    return inst;
}

genie::Graphic DataManager::getGraphic(unsigned int id)
{
    if (id >= dat_file_.Graphics.size()) {
        log.warn("graphic id %d is out of range", id);
        return genie::Graphic();
    }
    return dat_file_.Graphics[id];
}

genie::Unit DataManager::getUnit(unsigned int id)
{
    return dat_file_.Civs[0].Units[id];
}

const genie::Terrain &DataManager::getTerrain(unsigned int id)
{
    if (id >= dat_file_.TerrainBlock.Terrains.size()) {
        static genie::Terrain nullterrain;
        log.warn("terrain id %d is out of range", id);
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

DataManager::DataManager() :
    m_dataFileNames({
        { genie::GV_AoE, "Empires.dat" },
        { genie::GV_RoR, "empires_x1.dat" },
        { genie::GV_AoK, "empires2.dat" },
        { genie::GV_TC, "empires2_x1_p1.dat" },
    })
{
}

DataManager::~DataManager()
{
}

bool DataManager::initialize(const std::string dataPath)
{
    dat_file_.setGameVersion(genie::GV_TC);

    std::string filePath = dataPath + "empires2_x1_p1.dat";

    try {
        dat_file_.load(filePath.c_str());
    } catch (const std::exception &error) {
        std::cerr << "Failed to load " << filePath << ": " << error.what() << std::endl;
        return false;
    }

    return true;
}
