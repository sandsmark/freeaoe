/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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


#ifndef FREEAOE_TERRAIN_H
#define FREEAOE_TERRAIN_H

//#include "Resource.h"
#include "ResourcePtr.h"
#include <SFML/Graphics/Image.hpp>
#include <geniedat/Terrain.h>
#include <global/Logger.h>

class SlpFile;

namespace res
{

class Terrain : public Resource
{
public:
  //----------------------------------------------------------------------------
  /// @param Id resource id
  //
  Terrain(unsigned int Id);
  virtual ~Terrain();
  
  const sf::Image &getImage(void); 
  
  virtual void load(void);
  
private:
  static Logger &log;
  
  gdat::Terrain data_;
  SlpFile *slp_;
  
};

typedef ResourcePtr<Terrain> TerrainPtr;

}

#endif // FREEAOE_TERRAIN_H
