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

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <resource/ResourceManager.h>
#include <Engine.h>

#include <iostream>

Logger& RenderGraphic::log = Logger::getLogger("freeaoe.Render.RenderGraphic");

//------------------------------------------------------------------------------
RenderGraphic::RenderGraphic(Uint32 graph_id, sf::RenderTarget *render_target) 
                : render_target_(render_target),  current_frame_(0), 
                  time_last_frame_(0), current_angle_(0), 
                  angle_diff_(0), mirror_frame_(false)
{
  //graph_ = ResourceManager::Inst()->getGraphic(15001);//graph_id);
  graph_ = ResourceManager::Inst()->getGraphic(graph_id);
  
  setAngle(7);
}

//------------------------------------------------------------------------------
RenderGraphic::~RenderGraphic()
{
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
void RenderGraphic::setAngle(Uint32 angle)
{
  if (angle >= graph_->getAngleCount())
  {
    log.warn("Graphic with id [%d] has no frames for given angle.", 
             graph_->getId());
  }
  else
  {
    current_angle_ = angle;
    
    if (angle <= graph_->getAngleCount() / 2)
    {
      angle_diff_ = graph_->getFrameCount() * angle;
      mirror_frame_ = false;
    }
    else
    {
      angle_diff_ = graph_->getFrameCount() * (graph_->getAngleCount() - angle);
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
          > (graph_->getFrameRate() * 1000) )
    {
      if (current_frame_ < graph_->getFrameCount() - 1)
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

  textr_.LoadFromImage(graph_->getImage(getCurrentFrame(), mirror_frame_));
  
  sprite_.SetPosition(pos_ - graph_->getHotspot(getCurrentFrame(), mirror_frame_));
  sprite_.SetTexture(textr_);
  
  render_target_->Draw(sprite_);

  /*
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
  */
}

//------------------------------------------------------------------------------
bool RenderGraphic::coversPos(sf::Uint32 x, sf::Uint32 y)
{
  //TODO: Better locating. Outline?
  
  float x_img = pos_.x - graph_->getHotspot(getCurrentFrame()).x;
  float y_img = pos_.y - graph_->getHotspot(getCurrentFrame()).y;
  
  sf::Image img = graph_->getImage(getCurrentFrame());
  
  if (x >= x_img && x <= x_img + img.GetWidth() &&
      y >= y_img && y <= y_img + img.GetHeight())
    return true;
  
  return false;
}

//------------------------------------------------------------------------------
Uint32 RenderGraphic::getCurrentFrame(void )
{
  return current_frame_ + angle_diff_;
}

