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


#ifndef COMPGRAPHIC_H
#define COMPGRAPHIC_H

#include <core/IComponent.h>
#include <resource/Graphic.h>
#include "GameRenderer.h"
#include <resource/ResourceManager.h>

namespace attr
{
  const std::string GRAPHIC_DESC("attr_graphic");
  
  class GraphicDesc;
  typedef boost::shared_ptr<GraphicDesc> GraphicDescPtr;
  
  class GraphicDesc : public IAttribute
  {
  public:
    res::GraphicPtr Resource;
    
    static GraphicDescPtr create(unsigned int graphic_id);
    
  };
  
}

namespace comp
{

const std::string GRAPHIC("comp_graphic");
  
class Graphic;

typedef boost::shared_ptr< Graphic > GraphicPtr;

class Graphic : public IComponent
{

public:
  Graphic();
  virtual ~Graphic();
  
  virtual void update(Time time);
  
  void drawOn(GameRenderer &renderer);
  
  static comp::GraphicPtr create(unsigned int graphic_id);
  
};

}

#endif // COMPGRAPHIC_H
