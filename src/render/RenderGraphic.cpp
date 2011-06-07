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


#include "RenderGraphic.h"

#include <data/GenieGraphic.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <resource/ResourceManager.h>
#include <Engine.h>

RenderGraphic::RenderGraphic(GenieGraphic *data) : data_(data), 
                                                   current_frame_(0),
                                                   time_last_frame_(0)
{

}

RenderGraphic::RenderGraphic(const RenderGraphic& other)
{

}

RenderGraphic::~RenderGraphic()
{

}

RenderGraphic& RenderGraphic::operator=(const RenderGraphic& other)
{
    return *this;
}

void RenderGraphic::setX(int x)
{
  x_ = x;
}

void RenderGraphic::setY(int y)
{
  y_ = y;
}


void RenderGraphic::drawOn(sf::RenderTarget* target)
{
  ResourceManager *rm = ResourceManager::Inst();
  sf::Image *img;
  
  sprite_.SetX(x_);     //TODO: Center of slp file
  sprite_.SetY(y_);
  
  if (time_last_frame_ == 0)
  {
    time_last_frame_ = Engine::GameClock.GetElapsedTime();
    current_frame_ = 0;
  }
  else
  {
    if ( (Engine::GameClock.GetElapsedTime() - time_last_frame_) > data_->frame_rate_ )
    {
      if (current_frame_ < data_->frame_count_ - 1)
        current_frame_ ++;
      else
        current_frame_ = 0;
      
      time_last_frame_ = Engine::GameClock.GetElapsedTime();
    }
  }
  
  img = rm->getGraphic(data_->slp_id_)->getImage(current_frame_);
  
  
  sprite_.SetImage(*img);
  target->Draw(sprite_);
}

