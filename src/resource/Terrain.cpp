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
#include <genie/resource/Color.h>

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

    if (!m_slp) {
        static sf::Texture nullTex;
        if (nullTex.getSize().x == 0) {
            sf::Image nullImg;
            nullImg.create(Map::TILE_SIZE_HORIZONTAL, Map::TILE_SIZE_VERTICAL, sf::Color::Red);
            nullTex.loadFromImage(nullImg);
        }

        return nullTex;
    }

    if (m_images.find(frameNum) != m_images.end()) {
        return m_images[frameNum];
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

const genie::Terrain &Terrain::data()
{
    return m_data;
}

uint8_t Terrain::blendMode(const uint8_t ownMode, const uint8_t neighborMode)
{
    const std::array<std::array<uint8_t, 8>, 8> blendmodeTable ({{
        {{ 2, 3, 2, 1, 1, 6, 5, 4 }},
        {{ 3, 3, 3, 1, 1, 6, 5, 4 }},
        {{ 2, 3, 2, 1, 1, 6, 1, 4 }},
        {{ 1, 1, 1, 0, 7, 6, 5, 4 }},
        {{ 1, 1, 1, 7, 7, 6, 5, 4 }},
        {{ 6, 6, 6, 6, 6, 6, 5, 4 }},
        {{ 5, 5, 1, 5, 5, 5, 5, 4 }},
        {{ 4, 3, 4, 4, 4, 4, 4, 4 }}
    }});

    if (IS_UNLIKELY(ownMode > blendmodeTable.size() || neighborMode > blendmodeTable[ownMode].size())) {
        log.error("invalid mode %d %d", ownMode, neighborMode);
        return 0;
    }

    return blendmodeTable[ownMode][neighborMode];
}

bool Terrain::blendImage(sf::Image *image, ResourcePtr<Terrain> other, uint8_t blendFrame)
{
    if (!image) {
        log.error("No image passed for blending");
        return false;
    }

    if (!other->m_slp) {
        log.error("other doesn't have slp loaded");
        return false;
    }

    genie::BlendModePtr blend = ResourceManager::Inst()->getBlendmode(blendMode(m_data.BlendType, other->m_data.BlendType));
    if (!blend) {
        log.error("Failed to get blend mode");
        return false;
    }

    genie::SlpFramePtr overlay = other->m_slp->getFrame();

    const int width = overlay->getWidth();
    const int height = overlay->getHeight();
    const genie::SlpFrameData &overlayData = overlay->img_data;

    if (width == 0 || height == 0) {
        log.warn("Invalid dimensions of overlay (%dx%d)", width, height);
        return false;
    }

    if (image->getSize().x == 0 || image->getSize().y == 0) {
        image->create(width, height, sf::Color::Transparent);
    }

    genie::PalFilePtr palette = ResourceManager::Inst()->getPalette(50500);

    int blendOffset = 0;
    for (int y = 0; y < height; y++) {
        int lineWidth = 0;
        if (y < height/2) {
            lineWidth = 1 + (4 * y);
        } else {
            lineWidth = (height * 2 - 1) - (4 * (y - height/2));
        }

        int offsetLeft = height - 1 - (lineWidth  / 2);

        if (blendOffset + lineWidth > blend->alphaValues[blendFrame].size()) {
            log.error("Trying to read out of bounds (blendoffset %d + linewidth %d = %d, > %d", blendOffset, lineWidth, blendOffset + lineWidth, blend->alphaValues.size());
            return false;
        }

        for (int x = 0; x < lineWidth; x++) {
            sf::Color sourceColor = image->getPixel(x + offsetLeft, y);

            float overlayAlpha = 1. - blend->alphaValues[blendFrame][blendOffset++] / 128.;
            const uint8_t overlayIndex = overlayData.pixel_indexes[y * width + x + offsetLeft];
            genie::Color overlayColor = (*palette)[overlayIndex];

            overlayColor.a = overlayData.alpha_channel[y * width + x + offsetLeft];
            if (!overlayColor.a) {
                continue;
            }

            overlayAlpha *= overlayColor.a / 255.;

            sourceColor.r = overlayAlpha * overlayColor.r + (1. - overlayAlpha) * sourceColor.r;
            sourceColor.g = overlayAlpha * overlayColor.g + (1. - overlayAlpha) * sourceColor.r;
            sourceColor.b = overlayAlpha * overlayColor.b + (1. - overlayAlpha) * sourceColor.b;
            sourceColor.a = overlayAlpha * overlayColor.a + (1. - overlayAlpha) * sourceColor.a;

            image->setPixel(x + offsetLeft, y, sourceColor);
        }
    }

    return true;
}

}
