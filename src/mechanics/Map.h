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


#ifndef MAP_H
#define MAP_H
#include <data/GenieTerrain.h>

class Map
{

public:
  Map();
  virtual ~Map();
  
  void setUpSample();
  
  unsigned int getRows() { return 3; }
  unsigned int getCols() { return 3; }
  
  GenieTerrain getTerrain(unsigned int col, unsigned int row) { return terrain_[col][row]; }
  
private:
  GenieTerrain terrain_[4][4];
};

#endif // MAP_H
