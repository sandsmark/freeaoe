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


#include "Resource.h"

#include <global/Types.h>
#include <genie/resource/Color.h>

namespace res
{

//------------------------------------------------------------------------------
Resource::Resource(Uint32 id, Type type) : id_(id), type_(type), loaded_(false)
{

}

//------------------------------------------------------------------------------
Resource::~Resource()
{
  unload();
}

//------------------------------------------------------------------------------
Uint32 Resource::getId() const
{
  return id_;
}

//------------------------------------------------------------------------------
Resource::Type Resource::getType() const
{
  return type_;
}

//------------------------------------------------------------------------------
bool Resource::isLoaded() const
{
  return loaded_;
}

//------------------------------------------------------------------------------
void Resource::load()
{
  setLoaded(true);
}

//------------------------------------------------------------------------------
void Resource::unload()
{
  setLoaded(false);
}


//------------------------------------------------------------------------------
void Resource::setLoaded(bool loaded)
{
  loaded_ = loaded;
}

//------------------------------------------------------------------------------
sf::Image Resource::convertPixelsToImage(uint32_t width, uint32_t height,
                                               const uint8_t *pixels,
                                               uint8_t transparent_pixel,
                                               genie::PalFilePtr palette)
{
  sf::Image img;
  
  img.create(width, height, sf::Color::Transparent);

  for (uint32_t row=0; row < height; row++)
    for (uint32_t col=0; col < width; col++)
    {
      uint8_t c_index = pixels[row * width + col];
      
      if (c_index != transparent_pixel)
      {
        genie::Color g_color = (*palette)[c_index];
        img.setPixel(col, row, sf::Color(g_color.r, g_color.g, g_color.b));
      }           
    }
  
  return img;
}

}
