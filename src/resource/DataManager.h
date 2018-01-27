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

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <global/Logger.h>
#include <genie/dat/DatFile.h>
#include <genie/dat/Unit.h>
#include <genie/dat/Graphic.h>
#include <genie/dat/Terrain.h>
#include <genie/dat/Civ.h>

#include <map>
#include <unordered_map>
#include <SFML/Config.hpp>

//------------------------------------------------------------------------------
/// Class for receiving and managing data files (.dat)
//
class DataManager
{
public:
    bool initialize(const std::string dataPath);

    DataManager(const DataManager &) = delete;
    DataManager &operator=(const DataManager &) = delete;

    static DataManager &Inst();

    genie::Graphic getGraphic(unsigned int id);
    genie::Unit getUnit(unsigned int id);
    const genie::Terrain &getTerrain(unsigned int id);
    genie::TerrainRestriction getTerrainRestriction(unsigned int id);

    const genie::TerrainBlock &terrainBlock();

    static std::string gameName(const genie::GameVersion version);

private:
    DataManager();
    virtual ~DataManager();

    static Logger &log;

    genie::DatFile dat_file_;
    const std::unordered_map<genie::GameVersion, std::string> m_dataFileNames;
};

#endif // DATAMANAGER_H
