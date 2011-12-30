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


#ifndef BINAFILE_H
#define BINAFILE_H

#include "FileIO.h"

class ColorPalette;

//------------------------------------------------------------------------------
/// Class for reading binary files in drs. Like palettes ...
//
class BinaFile
{
public:
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id resources' id
  /// @param len 
  /// @param istr input/output stream
  /// @param pos start position of this file in stream
  //
  BinaFile(uint32_t id, uint32_t pos, uint32_t len, std::iostream *iostr);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~BinaFile();
  
  //----------------------------------------------------------------------------
  /// Tries to read a color palette from data.
  ///
  /// @return color palette if successfull
  //
  ColorPalette* readPalette();
  
  //----------------------------------------------------------------------------
  /// Get resource id
  ///
  /// @return resource id
  //
  uint32_t getId();
  
private:
  FileIO file_;
  
  uint32_t id_;
  uint32_t len_;
  
  ColorPalette *palette_;
};

#endif // BINAFILE_H
