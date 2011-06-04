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


#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::setUpSample()
{
  GenieTerrain ter1;
  GenieTerrain ter2;
  GenieTerrain ter3;
  
  ter1.name1 = "TER1";
  ter3.name1 = "TER3";
  ter2.name1 = "TER2";
  
  ter1.slp_id = 15000;
  ter2.slp_id = 15001;
  ter3.slp_id = 15002;
  
  for (int i=0; i < 4; i++)
  {
    terrain_[i][0] = ter1;
    terrain_[i][1] = ter2;
    terrain_[i][2] = ter3;
    //terrain_[i][3] = ter1;
  }
}
