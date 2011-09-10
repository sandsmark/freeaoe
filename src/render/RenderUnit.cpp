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


#include "RenderUnit.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <render/RenderGraphic.h>

#include <mechanics/Unit.h>

#include <data/GenieUnit.h>
#include <data/DataManager.h>

RenderUnit::RenderUnit(Unit *unit, sf::RenderTarget *render_target) : 
            unit_(unit), render_target_(render_target), current_graph_(0)
{

}

RenderUnit::RenderUnit(const RenderUnit& other)
{

}

RenderUnit::~RenderUnit()
{

}

Unit* RenderUnit::getUnit()
{
  return unit_;
}


void RenderUnit::update()
{
  if (current_graph_ == 0)
  {
    GenieGraphic graph =
      DataManager::Inst()->getGraphic(unit_->getData().standing_graphic_);
      
    current_graph_ = new RenderGraphic(graph, render_target_);
  }
 
  current_graph_->setPos(unit_->getPos());
  
  current_graph_->update();
}


void RenderUnit::draw()
{
  current_graph_->draw();
}

bool RenderUnit::coversPos(Uint32 x, Uint32 y)
{
  return current_graph_->coversPos(x, y);
}
