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


#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <vector>
#include <core/Entity.h>


// IDEA: Class containing all entities, (adds, removes, updates them).
// Base class (EntitySpace?)
class EntityManager
{

public:
  EntityManager();
  virtual ~EntityManager();
  
  void add(EntityPtr entity);
  
  void update(Time time);
  
private:
  
  typedef std::vector< EntityPtr > EntityVector;
  
  EntityVector entities_;
};

#endif // ENTITYMANAGER_H
