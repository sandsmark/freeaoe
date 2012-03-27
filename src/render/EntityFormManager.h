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


#ifndef ENTITYFORMMANAGER_H
#define ENTITYFORMMANAGER_H
#include <vector>
#include <core/Entity.h>
#include "SfmlRenderTarget.h"

class SfmlRenderTarget;
/// Handles entity forms and draws them properly to screen
class EntityFormManager
{

public:
  EntityFormManager();
  virtual ~EntityFormManager();
  
  void setGameRenderer(boost::shared_ptr<SfmlRenderTarget> renderer);
  
  void add(EntityForm &form);
  
  void createForms(EntityPtr entity);
  
  void update(Time time);
  void draw();
  
private:
  typedef std::vector<EntityForm> EFVector;
  EFVector forms_;
  
  boost::shared_ptr<SfmlRenderTarget> game_renderer_;
};

#endif // ENTITYFORMMANAGER_H
