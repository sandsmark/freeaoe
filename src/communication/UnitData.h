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


#ifndef UNITDATA_H
#define UNITDATA_H
#include <SFML/Config.hpp>

class UnitData
{

public:
  UnitData();
  
  UnitData(sf::Uint32 id, sf::Uint32 data_id, sf::Uint32 x_pos, 
           sf::Uint32 y_pos);
  
  UnitData(const UnitData& other);
  virtual ~UnitData();
  
  //TODO: getter + setter
  void *player;
  sf::Uint32 id_;
  sf::Uint32 data_id_;
  sf::Uint32 x_pos_;    // Map pos
  sf::Uint32 y_pos_;
};

#endif // UNITDATA_H
