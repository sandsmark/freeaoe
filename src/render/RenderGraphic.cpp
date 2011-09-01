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

#include <file/SlpFile.h>
#include <file/SlpFrame.h>
#include <data/GenieGraphic.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <resource/ResourceManager.h>
#include <Engine.h>

#include <iostream>

//------------------------------------------------------------------------------
RenderGraphic::RenderGraphic(GenieGraphic *data) : data_(data),
                                                   current_frame_(0),
                                                   time_last_frame_(0)
{
  slp_file_ = ResourceManager::Inst()->getSlp(data->getSlpId());
}

//------------------------------------------------------------------------------
RenderGraphic::RenderGraphic(const RenderGraphic& other)
{

}

//------------------------------------------------------------------------------
RenderGraphic::~RenderGraphic()
{
  slp_file_ = 0;
}

//------------------------------------------------------------------------------
RenderGraphic& RenderGraphic::operator=(const RenderGraphic& other)
{
    return *this;
}

//------------------------------------------------------------------------------
void RenderGraphic::setX(float x)
{
  x_ = x;
}

//------------------------------------------------------------------------------
void RenderGraphic::setY(float y)
{
  y_ = y;
}

//------------------------------------------------------------------------------
void RenderGraphic::drawOn(sf::RenderTarget* target)
{
  if (time_last_frame_ == 0)
  {
    time_last_frame_ = Engine::GameClock.GetElapsedTime();
    current_frame_ = 0;
  }
  else
  {
    if ( (Engine::GameClock.GetElapsedTime() - time_last_frame_)
          > (data_->frame_rate_ * 1000) )
    {
      if (current_frame_ < data_->frame_count_ - 1)
        current_frame_ ++;
      else
        current_frame_ = 0;

      time_last_frame_ = Engine::GameClock.GetElapsedTime();
    }
  }

  sf::Texture textr_;

  SlpFrame *frame = slp_file_->getFrame(current_frame_);

  sprite_.SetX(x_ - frame->getHotspotX());
  sprite_.SetY(y_ - frame->getHotspotY());

  textr_.LoadFromImage(*frame->getImage());
  sprite_.SetTexture(textr_);
  target->Draw(sprite_);

  sf::Image *color_mask = frame->getPlayerColorMask(2);
  textr_.LoadFromImage(*color_mask);
  sprite_.SetTexture(textr_);
  target->Draw(sprite_);

  //delete textr_;
  delete color_mask;
}

