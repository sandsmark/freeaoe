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


#ifndef SLPFRAME_H
#define SLPFRAME_H

#include <istream>
#include "FileIO.h"
#include <SFML/Graphics/Color.hpp>

namespace sf
{
  class Image;
}

class ColorPalette;

class SlpFrame : public FileIO
{
  
public:  
  SlpFrame(std::istream *istr, std::streampos pos, std::streampos file_pos, 
           ColorPalette *palette);
  virtual ~SlpFrame();
  
  void loadHeader();
  void load();
  
  sf::Image* getImage();
  
private:
  std::streampos file_pos_;
  
  sf::Uint32 cmd_table_offset_;
  sf::Uint32 outline_table_offset_;
  sf::Uint32 palette_offset_;
  sf::Uint32 properties_;
  
  sf::Int32 width_;
  sf::Int32 height_;
  sf::Int32 hotspot_x_;
  sf::Int32 hotspot_y_;
  
  sf::Uint16 *left_edges_;
  sf::Uint16 *right_edges_;
  
  sf::Image *image_;
  
  ColorPalette *palette_;
  
  //----------------------------------------------------------------------------
  /// Reads the edges of the frame. An edge int is the number of pixels in 
  /// a row which are transparent. There are two 16 bit unsigned integers for
  /// each side of a row. One starting from left and the other starting from the
  /// right side.
  /// Assuming stream pointer is at beginning of edges array.
  //
  void readEdges();
  
  //----------------------------------------------------------------------------
  /// Reads pixel indeces from file and sets the pixels according to the
  /// colors from the palette.
  /// It is assumed that the stream pointer is at the start of the pixe array.
  ///
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be read
  //
  void readPixelsToImage(sf::Uint32 row, sf::Uint32 &col, sf::Uint32 count);
  
  //----------------------------------------------------------------------------
  /// Sets the next count of pixels to given color without reading from stream.
  ///
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be set
  /// @param color color to set
  //
  void setPixelsToColor(sf::Uint32 row, sf::Uint32 &col, sf::Uint32 count,
                        sf::Color color);
};

#endif // SLPFRAME_H
