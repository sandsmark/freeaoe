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
#include <SFML/Graphics/Image.hpp>
#include <vector>

class ColorPalette;

//------------------------------------------------------------------------------
/// Class for reading a frame in a slp file.
/// TODO: Check file corruption
/// TODO: One (or more??) mask for player color and outline (and shadow?)
//
class SlpFrame
{
  
public:  
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param istr stream to read from
  /// @param pos position to start reading from
  /// @param file_pos position pointing at the beginning of the slp file.
  /// @param palette color palette to choose colors from
  //
  SlpFrame(std::iostream *iostr, std::streampos pos, std::streampos file_pos, 
           ColorPalette *palette);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SlpFrame();
  
  //----------------------------------------------------------------------------
  /// Loads header data. The headers of frames are stored after the header of 
  /// the slp file.
  //
  void loadHeader();
  
  //----------------------------------------------------------------------------
  /// Loads frame data and creates an image. Frame data is located after all
  /// frame headers of the slp file.
  //
  void load();
  
  //----------------------------------------------------------------------------
  /// Returns the image created by loading the frame.
  ///
  /// @return loaded image
  //
  sf::Image* getImage() const;
  
  //----------------------------------------------------------------------------
  /// Returns the outline created by loading the frame.
  /// Outline is the border of the sprite shown if a object is behind another
  /// one.
  ///
  /// @return loaded outline
  //
  sf::Image* getOutline() const;
  
  //----------------------------------------------------------------------------
  /// Returns the mask colored with color of given players index.
  ///
  /// @param player index
  /// @return player color mask
  //
  sf::Image* getPlayerColorMask(sf::Uint8 player) const; //TODO auto_ptr
  
  //----------------------------------------------------------------------------
  /// Get the hotspot of the frame. The Hotspot is the center of the image.
  ///
  /// @return x coordinate of the hotspot
  // TODO: Hotspot as vector
  sf::Int32 getHotspotX() const;
  
  //----------------------------------------------------------------------------
  /// Get the hotspot of the frame. The Hotspot is the center of the image.
  ///
  /// @return y coordinate of the hotspot
  //
  sf::Int32 getHotspotY() const;
  
private:
  FileIO file_;
  std::streampos file_pos_;
  
  sf::Uint32 cmd_table_offset_;
  sf::Uint32 outline_table_offset_;
  sf::Uint32 palette_offset_;
  sf::Uint32 properties_;
  
  sf::Int32 width_;
  sf::Int32 height_;
  sf::Int32 hotspot_x_;
  sf::Int32 hotspot_y_;
  
  sf::Int16 *left_edges_;
  sf::Int16 *right_edges_;
  
  sf::Image *image_;
  sf::Image *outline_;
  //sf::Image *player_color_mask_;
  
  sf::Int32 player_color_index_;
  
  ColorPalette *palette_;
  
  // Element for player_color vector, the vector stores position (x, y) of
  // a player color pixel and the palette index for the color
  struct PlayerColorElement
  {
    sf::Uint32 x;
    sf::Uint32 y;
    sf::Uint8 index;
  };
  
  std::vector<PlayerColorElement> player_color_mask_;
  
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
  /// It is assumed that the stream pointer is at the start of the pixel array.
  ///
  /// @param image target to set pixel
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be read
  /// @param player_col if true, pixel will be written to player color image
  //
  void readPixelsToImage(sf::Image *image, sf::Uint32 row, sf::Uint32 &col, 
                         sf::Uint32 count, bool player_col = false);
  
  //----------------------------------------------------------------------------
  /// Sets the next count of pixels to given color without reading from stream.
  ///
  /// @param image target to set pixel
  /// @param row row to set pixels at
  /// @param col column to set pixels from
  /// @param count how many pixels should be set
  /// @param color color to set
  /// @param player_col if true, pixel will be written to player color image
  //
  void setPixelsToColor(sf::Image *image, sf::Uint32 row, sf::Uint32 &col, 
                        sf::Uint32 count, sf::Uint8 color_index, 
                        bool player_col = false);
  
  //----------------------------------------------------------------------------
  /// This method returns either the count stored in command byte or (if not 
  /// stored in command) the value of the next byte.
  ///
  /// @param data command byte
  //
  sf::Uint8 getPixelCountFromData(sf::Uint8 data);
};

#endif // SLPFRAME_H
