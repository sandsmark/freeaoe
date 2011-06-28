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


#ifndef PALFILE_H
#define PALFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <SFML/Graphics/Color.hpp>

//------------------------------------------------------------------------------
/// Class for opening aoe palletes from .pal files
//
class ColorPalette
{

public:
  ColorPalette();
  
  //----------------------------------------------------------------------------
  /// Constructor that loads the palette from given file.
  ///
  /// @param filename filename to load from
  //
  ColorPalette(std::string filename);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~ColorPalette();
   
  //----------------------------------------------------------------------------
  /// Returns a color at given index.
  ///
  /// @param index index of color in palette
  /// @return color object
  //
  sf::Color getColorAt(u_int16_t index);  
  
  void parsePalette(std::istream &istr);
private:
  std::fstream file_;
  
  std::vector<sf::Color> colors_;
};

#endif // PALFILE_H
