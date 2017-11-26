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
#include <mechanics/Map.h>

namespace res {

Logger &Terrain::log = Logger::getLogger("freeaoe.resource.Terrain");

Terrain::Terrain(unsigned int Id) :
    Resource(Id, TYPE_TERRAIN)
{

    image_ = 0;
}

Terrain::~Terrain()
{
    delete image_;
}

sf::Image Terrain::getImage(void)
{
    if (image_ == 0) {
        if (slp_.get() == 0) {
            image_ = new sf::Image();
            image_->create(Map::TILE_SIZE_HORIZONTAL, Map::TILE_SIZE_VERTICAL,
                           sf::Color::Transparent);
        } else {

            genie::SlpFramePtr frame = slp_->getFrame(0);

            sf::Image img = Resource::convertPixelsToImage(frame->getWidth(), frame->getHeight(),
                                                           frame->img_data.pixel_indexes,
                                                           //frame->getTransparentPixelIndex(),
                                                           ResourceManager::Inst()->getPalette(50500));
            image_ = new sf::Image(img);
        }
    }
    return *image_;
}

void Terrain::load(void)
{
    if (!isLoaded()) {
        data_ = DataManager::Inst().getTerrain(getId());

        if (slp_.get() == 0)
            slp_ = ResourceManager::Inst()->getSlp(data_.SLP);

        //     if (slp_.get() == 0)
        //       slp_ = ResourceManager::Inst()->getSlp(15000); // TODO Loading grass if -1

        Resource::load();
    }
}
}
