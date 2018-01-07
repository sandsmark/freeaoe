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

const sf::Texture &Terrain::image(int x, int y)
{
    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (x % tileSquareCount) + (y % tileSquareCount) * tileSquareCount;

    if (m_images.find(frameNum) != m_images.end()) {
        return m_images[frameNum];
    }

    if (!m_slp) {
        static sf::Texture nullTex;
        if (nullTex.getSize().x == 0) {
            sf::Image nullImg;
            nullImg.create(Map::TILE_SIZE_HORIZONTAL, Map::TILE_SIZE_VERTICAL, sf::Color::Red);
            nullTex.loadFromImage(nullImg);
        }

        return nullTex;
    }

    std::vector<uint8_t> alphamask;
    if (m_blendIndex >= 0) {
         alphamask = ResourceManager::Inst()->getBlendmode(m_data.BlendType)->bytemasks[m_blendIndex];
    }

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    const genie::SlpFrameData &frameData = frame->img_data;

    sf::Image img;
    img.create(width, height, sf::Color::Red);

    if (alphamask.size() != height * width) {
        if (!alphamask.empty()) {
//            std::cerr << "wrong alphamask size: " << alphamask.size() << ", expected " << (height * width) << std::endl;
        }

        alphamask.resize(height * width, 128);
    }

//    for (uint32_t row = 0; row < height; row++) {
//        for (uint32_t col = 0; col < width; col++) {
//            const int index = row * width + col;
//            if (alphamask[index] <= 0) {
//                continue;
//            }
//            alphamask[index] = 255 * ((alphamask[index]/255.) * (frameData.alpha_channel[index] / 255.));
//        }
//    }

    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];
            genie::Color g_color = (*palette)[paletteIndex];
//            g_color.g = 0;
//            g_color.b = 0;
//            g_color.a = 255;
//            g_color.r = alphamask[row * width + col];
            g_color.a = alphamask[row * width + col];
            img.setPixel(col, row, sf::Color(g_color.r, g_color.g, g_color.b, g_color.a));
        }
    }

    sf::Image img = Resource::convertFrameToImage(m_slp->getFrame(frameNum),
                                                  ResourceManager::Inst()->getPalette(50500)
                                                  );

    m_images[frameNum].loadFromImage(img);

    return m_images[frameNum];
}

bool Terrain::load()
{
    if (!isLoaded()) {
        m_data = DataManager::Inst().getTerrain(getId());

        if (!m_slp) {
            m_slp = ResourceManager::Inst()->getSlp(m_data.SLP);
        }

        if (!m_slp) {
            log.error("Failed to get slp for %d", m_data.SLP);
            m_slp = ResourceManager::Inst()->getSlp(15000); // TODO Loading grass if -1

            return false;
        }

        return Resource::load();
    }

    return true;
}
}
