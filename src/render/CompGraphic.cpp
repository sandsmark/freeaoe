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


#include "CompGraphic.h"

#include "core/IAttribute.h"
#include <resource/ResourceManager.h>
#include <resource/DataManager.h>

namespace attr
{

GraphicDescPtr GraphicDesc::create(unsigned int graphic_id)
{
  GraphicDescPtr attr_graph(new GraphicDesc());
  attr_graph->Resource = ResourceManager::Inst()->getGraphic(graphic_id);
  
  return attr_graph;
}

}


namespace comp
{

Graphic::Graphic() : screen_pos_(0,0)
{
  
}

Graphic::~Graphic()
{

}

void Graphic::update(Time time)
{

}

void Graphic::drawOn(GameRenderer& renderer)
{
  //renderer.draw(getAttribute<attr::GraphicDesc>(attr::GRAPHIC_DESC)->Resource, ScreenPos(100,100));
  renderer.draw(graphic_, screen_pos_);
}

GraphicPtr Graphic::create(unsigned int graphic_id)
{
  comp::GraphicPtr ptr (new comp::Graphic());
  
  attr::GraphicDescPtr gdesc = attr::GraphicDesc::create(graphic_id);
 // ptr->addAttribute(attr::GRAPHIC_DESC, gdesc);
  
  ptr->graphic_ = gdesc->Resource;
  ptr->screen_pos_ = ScreenPos(100, 100);
  
  return ptr;
}


}
