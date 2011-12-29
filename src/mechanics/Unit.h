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


#ifndef FREEAOE_UNIT_H
#define FREEAOE_UNIT_H
#include <SFML/Config.hpp>

#include <SFML/System/Vector2.hpp>
#include <global/Types.h>
#include <communication/UnitStatus.h>
#include <geniedat/Unit.h>

class IAction;
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
  
//  void setPos(float x, float y);
  void setPos(MapPos pos);
  
  MapPos getPos(void) const;
  
  void setData(gdat::Unit data);
  gdat::Unit getData(void) const;
  
  //UnitStatus getStatus(void);
  
  void setCurrentAction(IAction *action);
  IAction *getCurrentAction(void) const;
  
private:
  Unit(const Unit& other);
  
  sf::Uint32 id_; //Unique ingame unit id
  
  MapPos pos_;
  
  gdat::Unit data_;
  
  bool data_changed_;
  
  IAction *action_;
};

#endif // FREEAOE_UNIT_H
