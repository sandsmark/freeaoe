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

#pragma once

#include <genie/Types.h>
#include <genie/dat/DatFile.h>
#include <string>
#include <vector>

#include "core/Logger.h"

namespace genie {
class Civ;
class Effect;
class Graphic;
class PlayerColour;
class Sound;
class Task;
class Tech;
class Terrain;
class TerrainBlock;
class TerrainRestriction;
}  // namespace genie

//------------------------------------------------------------------------------
/// Class for receiving and managing data files (.dat)
//
class DataManager
{
public:
    bool initialize();

    DataManager(const DataManager &) = delete;
    DataManager &operator=(const DataManager &) = delete;

    static DataManager &Inst();

    const genie::Graphic &getGraphic(unsigned int id) const;
    const genie::Tech &getTech(unsigned int id) const;
    const genie::Terrain &getTerrain(unsigned int id) const;
    const genie::Effect &getEffect(unsigned int id) const;
    const genie::TerrainRestriction &getTerrainRestriction(unsigned int id) const;
    const genie::PlayerColour &getPlayerColor(unsigned int id) const;
    const genie::Sound &getSound(unsigned int id) const;
    const std::vector<genie::Task> &getTasks(unsigned int id) const;

    const std::vector<genie::Tech> &allTechs() const { return dat_file_->Techs; }
    const genie::TerrainBlock &terrainBlock() const { return dat_file_->TerrainBlock; }

    bool isHd() const { return m_isHd; }
    genie::GameVersion gameVersion() const;
    static std::string gameName(const genie::GameVersion version);
    static std::string genieVersionString(const genie::GameVersion version);

    const std::vector<genie::Civ> &civilizations() const;

    const genie::Civ &civilization(unsigned int id) const;

private:
    DataManager() = default;
    virtual ~DataManager() = default;

    std::unique_ptr<genie::DatFile> dat_file_;
    bool m_isHd = false;
};

inline LogPrinter operator <<(LogPrinter os, const genie::GameVersion version) {
    const char *separator = os.separator;
    os.separator = "";
    os << "Game("
       << DataManager::gameName(version)
       << ", Genie " << DataManager::genieVersionString(version)
       << ")" << separator;
    os.separator = separator;
    return os;
}


