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


#ifndef UNIT_H
#define UNIT_H
#include <SFML/Config.hpp>

#include <data/GenieUnit.h>
#include <SFML/System/Vector2.hpp>
#include <global/Types.h>

//------------------------------------------------------------------------------
/// Units in aoe are all objects the player may interact with. E.g. Buildings,
/// Trees, Workers ...
//
class Unit
{

public:
  Unit(sf::Uint32 id);
  virtual ~Unit();
  
  sf::Uint32 getID(void) const;
  
  void setPos(float x, float y);
  void setPos(MapPos pos);
  
  MapPos getPos(void) const;
  
  float getX(void) const;
  float getY(void) const;
  
  void setData(GenieUnit data) {data_ = data;}
  GenieUnit getData(void) const;
  
private:
  Unit(const Unit& other);
  
  sf::Uint32 id_;
  
  // Position on the map
  MapPos pos_;
  
  GenieUnit data_;
  
  bool data_changed_;
};

#endif // UNIT_H
