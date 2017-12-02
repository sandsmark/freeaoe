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

#include <cmath>

namespace res {

Logger &Terrain::log = Logger::getLogger("freeaoe.resource.Terrain");

Terrain::Terrain(unsigned int Id) :
    Resource(Id, TYPE_TERRAIN)
{
}

Terrain::~Terrain()
{
}

const sf::Image &Terrain::image(int x, int y)
{
    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (x % tileSquareCount) + (y % tileSquareCount) * tileSquareCount;

    if (m_images.find(frameNum) != m_images.end()) {
        return m_images[frameNum];
    }

    if (!m_slp) {
        static sf::Image img;
        if (!img.getSize().x) {
            img.create(Map::TILE_SIZE_HORIZONTAL, Map::TILE_SIZE_VERTICAL, sf::Color::Red);
        }

        return img;
    }

    m_images[frameNum] = Resource::convertFrameToImage(m_slp->getFrame(frameNum),
                                                        ResourceManager::Inst()->getPalette(50500));

    return m_images[frameNum];
}

void Terrain::load()
{
    if (!isLoaded()) {
        m_data = DataManager::Inst().getTerrain(getId());

        if (!m_slp) {
            m_slp = ResourceManager::Inst()->getSlp(m_data.SLP);
        }

        if (!m_slp) {
            m_slp = ResourceManager::Inst()->getSlp(15000); // TODO Loading grass if -1
        }

        Resource::load();
    }
}
}
