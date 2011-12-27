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

namespace comp
{
  
GraphicPtr GraphicTemplate::create(unsigned int graphic_id)
{
  GraphicPtr graph(new Graphic());
  
  attr::GraphicPtr attr_graph(new attr::Graphic());
  
  attr_graph->Resource = ResourceManager::Inst()->getGraphic(graphic_id);
  
  graph->addAttribute(attr::GRAPHIC, attr_graph);
  
  std::cout << graph->getAttribute<attr::Graphic>(attr::GRAPHIC)->Resource->getId() << std::endl;
  
  GraphicPtr x = graph;
  
  std::cout << x->getAttribute<attr::Graphic>(attr::GRAPHIC)->Resource->getId() << std::endl;
  
  
  std::cout << "attr: " << attr_graph.get() << std::endl;
  std::cout << "attr: " << x->getAttribute<attr::Graphic>(attr::GRAPHIC).get() << std::endl;
  
  std::cout << "comp: " << graph.get() << std::endl;
  return graph;
}


Graphic::Graphic()
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
  renderer.draw(getAttribute<attr::Graphic>(attr::GRAPHIC)->Resource, ScreenPos(100,100));
}


}
