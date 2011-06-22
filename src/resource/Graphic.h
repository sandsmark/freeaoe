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

class SlpFile;

//------------------------------------------------------------------------------
/// A graphic resource contains one or more images. E.g. a unit animation
/// like walk. Wrapper class for a slp file.
///
/// TODO: remove and/or somehow combine with data/GenieGraphic
//
class Graphic : public Resource
{

public:
  Graphic(SlpFile *slp_file);
  virtual ~Graphic();
  
  sf::Image *getImage(unsigned int frame=0);
    
  virtual void load();
private:
  
  SlpFile *slp_file_;
};

#endif // GRAPHIC_H
