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


#include "ColorPalette.h"

#include <iostream>

using std::string;

ColorPalette::ColorPalette()
{

}


ColorPalette::ColorPalette(std::string filename)
{
  file_.open(filename.c_str(), std::ios::in);
  
  if (!file_.is_open() || file_.bad())
  {
    std::cerr << "Could not open " << filename.c_str() << std::endl;
    return;
  }
  
  parsePalette(file_);
  
  file_.close();
}

void ColorPalette::parsePalette(std::istream &istr)
{
  string smth;
  
  istr >> smth;
  istr >> smth;
  
  u_int32_t num_colors;
  
  istr >> num_colors;
  
  for (u_int32_t i=0; i<num_colors; i++)
  {
    u_int32_t color_in;
    sf::Color color_out;
    
    istr >> color_in;
    color_out.r = color_in;
    
    istr >> color_in;
    color_out.g = color_in;
    
    istr >> color_in;
    color_out.b = color_in;
    
    color_out.a = 255;
    
    colors_.push_back(color_out);
  }
}


ColorPalette::~ColorPalette()
{

}

sf::Color ColorPalette::getColorAt(u_int16_t pos)
{
  return colors_[pos];
}


