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


#ifndef GENIEUNIT_H
#define GENIEUNIT_H
#include <SFML/Config.hpp>

class GenieUnit
{
public:
  static const sf::Uint8 TYPE_DECO; //Decoration
  static const sf::Uint8 TYPE_FLAG;
  static const sf::Uint8 TYPE_FLAG2;
  static const sf::Uint8 TYPE_DEAD_FISH; // Dead unit or fihs unit
  static const sf::Uint8 TYPE_PROJECTILE;
  static const sf::Uint8 TYPE_LIVING;
  static const sf::Uint8 TYPE_BUILDING;
  
  
  sf::Uint32 id_;
  sf::Uint8 type_;
  sf::Uint32 display_name_id_;
  
  sf::Uint32 standing_graphic_;
  
  float Speed;
};

#endif // GENIEUNIT_H
