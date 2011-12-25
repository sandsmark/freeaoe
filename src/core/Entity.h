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


#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include "Attributes.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include "IComponent.h"

/// Entity is a generic class for game objects.
class Entity
{

public:
  Entity();
  virtual ~Entity();
  
  void update(Time time);
  
private:
  typedef std::map<const char *, boost::shared_ptr< IComponent > > ComponentMap;
  ComponentMap components_;
};

#endif // ENTITY_H
