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

Logger& RenderGraphic::log = Logger::getLogger("freeaoe.Render.RenderGraphic");

//------------------------------------------------------------------------------
RenderGraphic::RenderGraphic(GenieGraphic data, sf::RenderTarget *render_target) 
                : data_(data), current_frame_(0), time_last_frame_(0),
                  render_target_(render_target), current_angle_(0), 
                  angle_diff_(0), mirror_frame_(false)
{
  slp_file_ = ResourceManager::Inst()->getSlp(data.getSlpId());
  setAngle(7);
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
  pos_.x = x;
}

//------------------------------------------------------------------------------
void RenderGraphic::setY(float y)
{
  pos_.y = y;
}

//------------------------------------------------------------------------------
void RenderGraphic::setPos (sf::Vector2f pos)
{
  pos_ = pos;
}

//------------------------------------------------------------------------------
void RenderGraphic::setAngle(sf::Uint8 angle)
{
  if (angle >= data_.angle_count_)
  {
    log.warn("Graphic with id [%d] has no frames for given angle.", data_.id_);
  }
  else
  {
    current_angle_ = angle;
    
    if (angle <= data_.angle_count_/2)
    {
      angle_diff_ = data_.frame_count_ * angle;
      mirror_frame_ = false;
    }
    else
    {
      angle_diff_ = data_.frame_count_ * (data_.angle_count_ - angle);
      mirror_frame_ = true;
    }
  }
}


//------------------------------------------------------------------------------
void RenderGraphic::update()
{
  if (time_last_frame_ == 0)
  {
    time_last_frame_ = Engine::GameClock.GetElapsedTime();
    current_frame_ = 0;
  }
  else
  {
    if ( (Engine::GameClock.GetElapsedTime() - time_last_frame_)
          > (data_.frame_rate_ * 1000) )
    {
      if (current_frame_ < data_.frame_count_ - 1)
        current_frame_ ++;
      else
        current_frame_ = 0;

      time_last_frame_ = Engine::GameClock.GetElapsedTime();
    }
  }
}

//------------------------------------------------------------------------------
void RenderGraphic::draw()
{  
  sf::Texture textr_;

  SlpFrame *frame = slp_file_->getFrame(current_frame_ + angle_diff_);

  sprite_.SetX(pos_.x - frame->getHotspotX()); //TODO: Hotspot as vector
  sprite_.SetY(pos_.y - frame->getHotspotY());
  
  sf::Image img = sf::Image(*frame->getImage());
  
  if (mirror_frame_)    //TODO: hotspot also differs
    img.FlipHorizontally();
  
  textr_.LoadFromImage(img);
  
  sprite_.SetTexture(textr_);
  render_target_->Draw(sprite_);

  sf::Image *cmask = frame->getPlayerColorMask(2);
  sf::Image color_mask = sf::Image(*cmask);
  
  if (mirror_frame_)
    color_mask.FlipHorizontally();
  
  textr_.LoadFromImage(color_mask);
  sprite_.SetTexture(textr_);
  render_target_->Draw(sprite_);

  //delete textr_;
  //delete color_mask;
  delete cmask;
}

//------------------------------------------------------------------------------
bool RenderGraphic::coversPos(sf::Uint32 x, sf::Uint32 y)
{
  SlpFrame *frame = slp_file_->getFrame(current_frame_);
  
  //TODO: Better locating. Outline?
  
  sf::Uint32 x_img = pos_.x - frame->getHotspotX();
  sf::Uint32 y_img = pos_.y - frame->getHotspotY();
  
  if (x >= x_img && x <= x_img + frame->getImage()->GetWidth() &&
      y >= y_img && y <= y_img + frame->getImage()->GetHeight())
    return true;
  
  return false;
}

