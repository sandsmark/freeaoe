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


#ifndef UNIT_RENDERER_H
#define UNIT_RENDERER_H

#include <vector>

#include "IRenderer.h"
#include "core/Entity.h"

/// Handles entity forms and draws them properly to screen
class UnitRenderer : public IRenderer
{

public:
  UnitRenderer();
  virtual ~UnitRenderer();
  
  void add(EntityForm &form);
  
  void createForms(EntityPtr entity);
  
  virtual void update(Time time);
  virtual void display();
  
private:
  typedef std::vector<EntityForm> EFVector;
  EFVector forms_;
  
};

#endif // UNIT_RENDERER_H
