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


Logger& DataManager::log = Logger::getLogger("freeaoe.DataManager");

DataManager& DataManager::Inst()
{
  static DataManager inst;
  return inst;
}

genie::Graphic DataManager::getGraphic(unsigned int id)
{
  return dat_file_.Graphics[id];
}

genie::Unit DataManager::getUnit(unsigned int id)
{
  return dat_file_.Civs[0].Units[id];
}

genie::Terrain DataManager::getTerrain(unsigned int id)
{
  return dat_file_.Terrains[id];
}



DataManager::DataManager()
{
  initialize();
}

DataManager::~DataManager()
{

}

void DataManager::initialize()
{
  dat_file_.setGameVersion(genie::GV_TC);
  
  std::string filePath = Config::Inst()->getDataPath() + "empires2_x1_p1.dat";
  
  dat_file_.load(filePath.c_str());
}