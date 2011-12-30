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


#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::addComponent(const std::string& name, ComponentPtr comp)
{
  components_[name.c_str()] = comp;
}

void Entity::update(Time time)
{
  for (ComponentMap::iterator it = components_.begin(); it != components_.end();
       it ++)
    (*it).second->update(time);
  
  if (current_action_.get() != 0)
    current_action_->update(time);
}



