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

#include "ActionMove.h"
#include <Engine.h>

#include <iostream>
#include "CompMapObject.h"

namespace act {

MoveOnMap::MoveOnMap(EntityPtr entity, MapPos destination) :
    entity_(entity)
{
    dest_ = destination;
    last_update_ = 0;
}

MoveOnMap::~MoveOnMap()
{
}

bool MoveOnMap::update(Time time)
{
    if (last_update_ == 0 || (time - last_update_) >= 1000) //test!
    {
        comp::MapObjectPtr ptr = entity_->getComponent<comp::MapObject>(comp::MAP_OBJECT);

        ptr->setPos(ptr->getPos() + MapPos(10, 10, 0));

        last_update_ = time;
    }

    return false;
}
}

/*
// TODO: UUUUGGGLYYY 
void ActionMove::update(void )
{
  /*
  float time_step = 30;
  
  sf::Uint32 time = Engine::GameClock.GetElapsedTime();
  
  if (last_update_ == 0) // || time - last_update_ > 100 )
  {
    sf::Vector2f u_pos = unit_->getPos();
    sf::Vector2f path = goal_pos_ - u_pos;
             
    float length = thor::Length<float>(path);
    
    // (Speed + 1) / 10
    path_part.x = (path.x * 0.09 * time_step) / length;
    path_part.y = (path.y * 0.09 * time_step) / length;
   
    unit_->setPos(unit_->getPos() + path_part);
    
    last_update_ = time;
  }
  else 
  {
    if (time - last_update_ > time_step )
    {
      unit_->setPos(unit_->getPos() + path_part);
      last_update_ = time;
    }
  }
  
  sf::Vector2f dist = unit_->getPos() - goal_pos_ ; 
  float ld = thor::Length<float>(dist);
  
  if ( abs(ld) < 3)
  {
    target_reached = true;
    IAction::setDone();
  }*
}*/
