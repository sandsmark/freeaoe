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


#include "Graphic.h"
#include <resource/DataManager.h>
#include "ResourceManager.h"

#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <genie/resource/Color.h>

namespace res
{
  
Logger& Graphic::log = Logger::getLogger("freeaoe.resource.Graphic");

//------------------------------------------------------------------------------
Graphic::Graphic(uint32_t id) : Resource(id, TYPE_GRAPHIC), data_(0)
{

}

//------------------------------------------------------------------------------
Graphic::~Graphic()
{

}

//------------------------------------------------------------------------------
sf::Image Graphic::getImage(uint32_t frame_num, bool mirrored)
{
  genie::SlpFramePtr frame = slp_->getFrame(frame_num);
  
  sf::Image img = convertPixelsToImage(frame->getWidth(), frame->getHeight(),
                                       frame->getPixelIndexes(), 
                                       frame->getTransparentPixelIndex(), 
                                       ResourceManager::Inst()->getPalette(50500) 
                                      );
  
  if (mirrored)
  {
    img.FlipHorizontally();
  }
  
  return img;
}

//------------------------------------------------------------------------------
ScreenPos Graphic::getHotspot(uint32_t frame_num, bool mirrored) const
{
  genie::SlpFramePtr frame = slp_->getFrame(frame_num);
  
  int32_t hot_spot_x = frame->getHotspotX();
  
  if (mirrored)
    hot_spot_x = frame->getWidth() - hot_spot_x;
  
  return ScreenPos(hot_spot_x, frame->getHotspotY());
}

//------------------------------------------------------------------------------
float Graphic::getFrameRate(void ) const
{
  return data_->FrameRate;
}

//------------------------------------------------------------------------------
float Graphic::getReplayDelay(void ) const
{
  return data_->ReplayDelay;
}

//------------------------------------------------------------------------------
uint32_t Graphic::getFrameCount(void ) const
{
  return data_->FrameCount;
}

//------------------------------------------------------------------------------
uint32_t Graphic::getAngleCount(void ) const
{
  return data_->AngleCount;
}

//------------------------------------------------------------------------------
void Graphic::load(void )
{
  if (!isLoaded())
  {
    data_ = new genie::Graphic(DataManager::Inst().getGraphic(getId()));
  
    slp_ = ResourceManager::Inst()->getSlp(data_->SLP);
  
    if (slp_->getFrameCount() != 
        data_->FrameCount * (data_->AngleCount / 2 + 1) )
      log.warn("Graphic [%d]: Framecount between data and slp differs.", 
               getId());
    
    Resource::load();
  }
}

//------------------------------------------------------------------------------
void Graphic::unload(void )
{
  if (isLoaded())
  {
    delete data_;
    data_ = 0;
    
    slp_->unload();
    Resource::unload();
  }
}

//------------------------------------------------------------------------------
sf::Image Graphic::convertPixelsToImage(uint32_t width, uint32_t height,
                                               const uint8_t *pixels,
                                               uint8_t transparent_pixel,
                                               genie::PalFilePtr palette)
{
  sf::Image img;
  
  img.Create(width, height, sf::Color::Transparent);

  for (uint32_t row=0; row < height; row++)
    for (uint32_t col=0; col < width; col++)
    {
      uint8_t c_index = pixels[row * width + col];
      
      if (c_index != transparent_pixel)
      {
        genie::Color g_color = (*palette)[c_index];
        img.SetPixel(col, row, sf::Color(g_color.r, g_color.g, g_color.b));
      }           
    }
  
  return img;
}

}