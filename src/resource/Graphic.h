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


#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Resource.h"
#include <SFML/Graphics/Image.hpp>
#include <data/GenieGraphic.h>

class SlpFile;

namespace res
{

//------------------------------------------------------------------------------
/// A graphic resource contains one or more images. E.g. a unit animation
/// like walk. Wrapper class for a slp file.
///
/// TODO: remove and/or somehow combine with data/GenieGraphic
//
class Graphic : public Resource
{

public:
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id Id of the graphic struct in .dat file.
  //
  Graphic(sf::Uint32 id);
  virtual ~Graphic();
  
  sf::Image *getImage(unsigned int frame=0);
    
  virtual void load();
private:
  
  sf::Uint32 id_;
  
  GenieGraphic *data_;
  SlpFile *slp_;
  
  //TODO: collection with all frames, playercolors and outlines loaded
  //      And rewrite SlpFile/Frame so that it will not store any data.
};

}

#endif // GRAPHIC_H
