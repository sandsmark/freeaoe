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


#ifndef COMPMAPOBJECT_H
#define COMPMAPOBJECT_H

#include "core/IComponent.h"

#include "global/Types.h"

#include "core/Entity.h"
#include "core/IAction.h"

namespace comp
{
  
const std::string MAP_OBJECT("map_object");

class MapObject : public IComponent
{
public:
  MapObject();
  virtual ~MapObject();
  
  virtual void update(Time time) {}
  
  void setPos(MapPos pos);
  
  MapPos getPos(void) const;
    
private:
  MapPos pos_;
  
  //FacingDirection

  //*map
  
};

typedef boost::shared_ptr< MapObject > MapObjectPtr;

namespace act
{
  
class PlaceMapObject : public IAction 
{
public:
  PlaceMapObject(EntityPtr entity, MapPos pos) : target_(entity), new_pos_(pos)
  {}
  
  virtual bool update(Time time)
  {
    target_->getComponent<comp::MapObject>(comp::MAP_OBJECT)->setPos(new_pos_);
    return true;
  }
  
private:
  EntityPtr target_;
  MapPos new_pos_;
};

}

}

#endif // COMPMAPOBJECT_H
