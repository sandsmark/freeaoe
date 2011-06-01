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


#ifndef SLPFILE_H
#define SLPFILE_H

#include <istream>
#include <vector>

#include "FileIO.h"
#include "../resource/Resource.h"

#include <SFML/Graphics/Image.hpp>

class SlpFrame;

class SlpFile : public FileIO //TODO: Not a resource, but a resource loader!!
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  //
  SlpFile();
  
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id resources' id
  /// @param len 
  /// @param istr input stream
  /// @param pos start position of this file in stream
  //
  SlpFile(sf::Int32 id, sf::Int32 len, std::istream *istr, std::streampos pos);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SlpFile();
  
  void load();
  
  sf::Uint32 getFrameCount();
  
  sf::Image* getImageAt(sf::Uint32 frame);
  
  //sf::Image *image_; //DEBUG!!
  
private:
  sf::Int32 id_;
  sf::Int32 len_;
  
  sf::Uint32 num_frames_;
  
  std::vector<SlpFrame *> frames_;
  
  void readHeader();
};

#endif // SLPFILE_H
