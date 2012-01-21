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
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Utility.h"

#include "IComponent.h"
#include "IAction.h"

class EntityForm;

/// Entity is a generic class for game objects.
class Entity
{       //TODO: entity collections, actions

public:  
  Entity();
  virtual ~Entity();
  
  virtual void update(Time time);
  
  void addComponent(const std::string &name, ComponentPtr comp);
  
  template <class T>
  boost::shared_ptr< T > getComponent(const std::string &name)
  {
    ComponentPtr ptr = components_[name.c_str()];
    return boost::dynamic_pointer_cast<T>(ptr);
  }
  
  unsigned int getComponentSize() { return components_.size(); }
  
public:
  ActionPtr current_action_;
  
private:
  typedef std::map<const char *, ComponentPtr, util::cstr_comp > ComponentMap;
  ComponentMap components_;
  
};

typedef boost::shared_ptr< Entity > EntityPtr;


/// A generic class representing an entity on screen
class EntityForm : public Entity
{
public:
  EntityForm() {}
  EntityForm(EntityPtr root) : root_(root) {}
  virtual ~EntityForm() {}
  
  EntityPtr getRoot(void) { return root_; }
  
private:
  EntityPtr root_;
  
  //EntityForm(const EntityForm& other);
};

typedef boost::shared_ptr< EntityForm > EntityFormPtr;

#endif // ENTITY_H
