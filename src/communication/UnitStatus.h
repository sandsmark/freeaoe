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


#ifndef UNITSTATUS_H
#define UNITSTATUS_H
#include <SFML/Config.hpp>
#include <global/Types.h>

//------------------------------------------------------------------------------
/// This data package contains information about a units status.
//
class UnitStatus
{

public:
  UnitStatus();
  
  UnitStatus(sf::Uint32 id, sf::Uint32 data_id, MapPos pos);
  
  virtual ~UnitStatus();
  
  sf::Uint32 getID();
  
  sf::Uint32 getDataID();
  
  MapPos getPos();
  
private:
  void *player;
  sf::Uint32 id_;
  sf::Uint32 data_id_;
  
  MapPos pos_;
};

#endif // UNITSTATUS_H
