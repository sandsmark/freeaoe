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


#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H
#include "IAction.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>

class Unit;
class ActionMove : public IAction
{

public:
  ActionMove(Unit *unit, sf::Vector2f goal_pos);
  virtual ~ActionMove();
  
  virtual void update(void);
  
  virtual Unit *getUnit(void);
  
private:
  Unit *unit_;
  sf::Vector2f goal_pos_;
  
  sf::Uint32 last_update_;
  
  sf::Vector2f path_part;
  bool target_reached;
};

#endif // ACTIONMOVE_H
