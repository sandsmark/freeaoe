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

class SlpFile : public FileIO 
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  //
  //SlpFile();
  
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id resources' id
  /// @param len 
  /// @param istr input/output stream
  /// @param pos start position of this file in stream
  //
  SlpFile(sf::Uint32 id, sf::Uint32 pos, sf::Uint32 len, std::iostream *iostr 
          );
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~SlpFile();
  
  //----------------------------------------------------------------------------
  /// Loads the file and its frames. If already loaded this method does nothing.
  //
  void load();
  
  //----------------------------------------------------------------------------
  /// Return number of frames stored in the file. Available after load.
  ///
  /// @return number of frames
  //
  sf::Uint32 getFrameCount();
  
  //----------------------------------------------------------------------------
  sf::Int32 getId();
  
  //----------------------------------------------------------------------------
  /// Returns pointer to the image at given frame or 0 if no image is at frame.
  /// The image has not to be deleted!
  ///
  /// @param frame frame number, default = 0
  /// @return image object or 0
  //
  sf::Image* getImage(sf::Uint32 frame=0);
  
private:
  sf::Uint32 id_;
  sf::Uint32 len_;
  
  sf::Uint32 num_frames_;
  
  std::vector<SlpFrame *> frames_;
  
  void readHeader();
};

#endif // SLPFILE_H
