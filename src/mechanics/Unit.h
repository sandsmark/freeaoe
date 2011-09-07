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
  
  void setPos(sf::Uint32 x, sf::Uint32 y);
  
  sf::Uint32 getX(void) const;
  sf::Uint32 getY(void) const;
  
  void setData(GenieUnit data) {data_ = data;}
  GenieUnit getData(void) const;
  
private:
  Unit(const Unit& other);
  
  sf::Uint32 id_;
  
  // Position on the map
  sf::Uint32 x_, y_;
  
  GenieUnit data_;
};

#endif // UNIT_H
