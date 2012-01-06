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


#ifndef FREEAOE_GRAPHIC_H
#define FREEAOE_GRAPHIC_H

#include "Resource.h"
#include <SFML/Graphics/Image.hpp>
#include <global/Types.h>
#include "ResourcePtr.h"
#include <global/Logger.h>
#include <geniedat/Graphic.h>

class SlpFile;

namespace res
{
  
//------------------------------------------------------------------------------
/// A graphic resource contains one or more frames and data stored to
/// the graphic.
// TODO: Player mask, outline
//
class Graphic : public Resource
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id Id of the graphic struct in .dat file.
  //
  Graphic(Uint32 id);
  virtual ~Graphic();
  
  //----------------------------------------------------------------------------
  /// Returns the image of the graphic. 
  ///
  /// @param frame_num Number of the frame
  /// @param mirrored If set, the image will be returned mirrored
  /// @return Image
  //
  const sf::Image& getImage(Uint32 frame_num=0, bool mirrored=false);
  
  //----------------------------------------------------------------------------
  /// Get the hotspot of a frame.
  // TODO: Maybe inherit from sf::Image and include this property
  //
  ScreenPos getHotspot(Uint32 frame_num=0, bool mirrored=false) const;
  
  //----------------------------------------------------------------------------
  /// Get the frame rate of the graphic
  ///
  /// @return frame rate
  //
  float getFrameRate(void) const;
  
  //----------------------------------------------------------------------------
  ///
  /// @return replay delay
  //
  float getReplayDelay(void) const;
  
  //----------------------------------------------------------------------------
  /// Get the graphics frame count.
  ///
  /// @return frame count
  //
  Uint32 getFrameCount(void) const;
    
  //----------------------------------------------------------------------------
  /// Get the graphics angle count
  ///
  /// @return angle count
  //
  Uint32 getAngleCount(void) const;
    
  virtual void load(void);
  virtual void unload(void);
private:
  static Logger &log;
  
  Uint32 id_;
  
  gdat::Graphic *data_;
  SlpFile *slp_;
  
  //TODO: collection with all frames, playercolors and outlines loaded
  //      And rewrite SlpFile/Frame so that it will not store any data.
};

typedef ResourcePtr<Graphic> GraphicPtr;

}

#endif // FREEAOE_GRAPHIC_H
