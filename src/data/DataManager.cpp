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

#include "GenieGraphic.h"
#include "GenieTerrain.h"
#include "GenieUnit.h"

Logger& DataManager::log = Logger::getLogger("freeaoe.DataManager");

DataManager* DataManager::Inst()
{
  static DataManager inst;
  return &inst;
}

GenieGraphic DataManager::getGraphic(Uint32 id)
{
  return *graphics_[id];
}

GenieUnit DataManager::getUnit(Uint32 id)
{
  return *units_[id];
}



DataManager::DataManager()
{
  initialize();
}

DataManager::DataManager(const DataManager& other)
{

}

DataManager::~DataManager()
{

}

DataManager& DataManager::operator=(const DataManager& other)
{
    return *this;
}

void DataManager::initialize()
{
  log.debug("Initializing DataManager (sample data)");
  // Setup sample data:
  
  GenieUnit *gu = new GenieUnit();
  gu->id_ = 281;
  gu->display_name_id_ = 5111;
  gu->standing_graphic_ = 1128;
  //type = 70, living unit
  
  units_[gu->id_] = gu;
  
  gu = new GenieUnit();
  gu->id_ = 234;
  gu->display_name_id_ = 5154;
  gu->standing_graphic_ = 2532;
  // type = 80 building
  
  units_[gu->id_] = gu;
  
  GenieGraphic *gg = new GenieGraphic();
  
  gg->id_ = 1128;
  gg->slp_id_ = 1057;
  gg->name1_ = "TAXEM_FN";
  gg->frame_count_ = 10;
  gg->angle_count_ = 8;
  gg->frame_rate_ = 0.25;
  
  graphics_[gg->id_] = gg;
  
  gg = new GenieGraphic();
  
  gg->id_ = 2532;
  gg->slp_id_ = 2667;
  gg->name1_ = "WCTW2NNGW";
  gg->angle_count_ = 1;
  gg->frame_count_ = 1;
  gg->frame_rate_ = 0;
  
  graphics_[gg->id_] = gg;
  
  gg = new GenieGraphic();
  
  gg->id_ = 1972;
  gg->slp_id_ = 2085;
  gg->name1_ = "SCOUT_FN";
  gg->angle_count_ = 8;
  gg->frame_count_ = 10;
  gg->frame_rate_ = 0.2;
  
  graphics_[gg->id_] = gg;
}


