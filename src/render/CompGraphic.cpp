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
#include <mechanics/CompMapObject.h>

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
  current_frame_ = 0; 
  time_last_frame_ = 0;
  current_angle_ = 0; 
  angle_diff_ = 0;
  mirror_frame_ = false;
}

Graphic::~Graphic()
{

}

void Graphic::update(Time time)
{
  
  
  if (time_last_frame_ == 0)
  {
    time_last_frame_ = time;
    current_frame_ = 0;
  }
  else
  {
    if ( (time - time_last_frame_) > (graphic_->getFrameRate() * 1000) )
    {
      if (current_frame_ < graphic_->getFrameCount() - 1)
        current_frame_ ++;
      else
        current_frame_ = 0;

      time_last_frame_ = time;
    }
  }
}

void Graphic::drawOn(GameRenderer& renderer)
{
  
  screen_pos_ = mapToScreenPos(map_object_->getPos());
  
  renderer.draw(graphic_, screen_pos_, current_frame_);
}

void Graphic::setMapObject(MapObjectPtr map_object)
{
  map_object_ = map_object;
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

ScreenPos Graphic::mapToScreenPos(MapPos mpos)
{
  ScreenPos spos;
  
  spos.x = mpos.x - mpos.y;
  spos.y = mpos.z + (mpos.x + mpos.y)/2;
  
  return spos;
}



}
