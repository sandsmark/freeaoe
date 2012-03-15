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


#include "Terrain.h"

#include "DataManager.h"
#include "ResourceManager.h"

#include <genie/resource/SlpFrame.h>

namespace res
{
  
Logger& Terrain::log = Logger::getLogger("freeaoe.resource.Terrain");

Terrain::Terrain(unsigned int Id): Resource(Id, TYPE_TERRAIN)
{

}

Terrain::~Terrain()
{

}

sf::Image Terrain::getImage(void )
{
  if (slp_.get())
  {
    // TODO: maybe move to resourcemanager because res::Graphic is using the same
    genie::SlpFramePtr frame = slp_->getFrame(0);
    
    sf::Image img = Graphic::convertPixelsToImage(frame->getWidth(), frame->getHeight(),
                                        frame->getPixelIndexes(), 
                                        frame->getTransparentPixelIndex(), 
                                        ResourceManager::Inst()->getPalette(50500) 
                                        );
    
    return img;
  }
  return sf::Image();
}

void Terrain::load(void )
{
  if (!isLoaded())
  {
    data_ = DataManager::Inst().getTerrain(getId());
  
    if (slp_.get() == 0)
      slp_ = ResourceManager::Inst()->getSlp(data_.SLP);
    
    if (slp_.get() == 0)
      slp_ = ResourceManager::Inst()->getSlp(15000); // TODO Loading grass if -1
    
    Resource::load();
  }
}


  
}