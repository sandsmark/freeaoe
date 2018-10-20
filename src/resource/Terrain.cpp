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
#include "AssetManager.h"

#include <genie/resource/SlpFrame.h>
#include <genie/resource/Color.h>

#include "global/Constants.h"
#include "core/Utility.h"

#include <cmath>

Terrain::Terrain(unsigned int id_) : id(id_)
{
}

Terrain::~Terrain()
{
}

const sf::Texture &Terrain::texture(int x, int y)
{
    if (!m_slp) {
        static sf::Texture nullTex;
        if (nullTex.getSize().x == 0) {
            sf::Image nullImg;
            nullImg.create(Constants::TILE_SIZE_HORIZONTAL, Constants::TILE_SIZE_VERTICAL, sf::Color::Red);
            nullTex.loadFromImage(nullImg);
        }

        return nullTex;
    }

    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;

    if (m_images.find(frameNum) != m_images.end()) {
        return m_images[frameNum];
    }

    sf::Image img = Resource::convertFrameToImage(m_slp->getFrame(frameNum));

#ifdef DEBUG
    addOutline(img);
#endif

    m_images[frameNum].loadFromImage(img);

    return m_images[frameNum];
}

const sf::Image Terrain::image(int x, int y)
{
    if (!m_slp) {
        return sf::Image();
    }

    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;


#ifdef DEBUG
    sf::Image img = Resource::convertFrameToImage(m_slp->getFrame(frameNum));
    addOutline(img);
    return img;
#else
    return Resource::convertFrameToImage(m_slp->getFrame(frameNum));
#endif
}

bool Terrain::load()
{
    if (!m_isLoaded) {
        m_isLoaded = true;

        m_data = DataManager::Inst().getTerrain(id);

        if (!m_slp) {
            if (m_data.TerrainToDraw != -1) {
                const int replacementSlp = DataManager::Inst().getTerrain(m_data.TerrainToDraw).SLP;
                m_slp = AssetManager::Inst()->getSlp(replacementSlp);
            } else {
                m_slp = AssetManager::Inst()->getSlp(m_data.SLP);
            }
        }

        if (!m_slp) {
            WARN << "Failed to get slp for" << m_data.SLP;
            m_slp = AssetManager::Inst()->getSlp(15000); // TODO Loading grass if -1

            return false;
        }
    }

    return true;
}

const genie::Terrain &Terrain::data()
{
    return m_data;
}

uint8_t Terrain::blendMode(const uint8_t ownMode, const uint8_t neighborMode)
{
    const std::array<std::array<uint8_t, 8>, 8> blendmodeTable = {{
        {{ 2, 3, 2, 1, 1, 6, 5, 4 }},
        {{ 3, 3, 3, 1, 1, 6, 5, 4 }},
        {{ 2, 3, 2, 1, 1, 6, 1, 4 }},
        {{ 1, 1, 1, 0, 7, 6, 5, 4 }},
        {{ 1, 1, 1, 7, 7, 6, 5, 4 }},
        {{ 6, 6, 6, 6, 6, 6, 5, 4 }},
        {{ 5, 5, 1, 5, 5, 5, 5, 4 }},
        {{ 4, 3, 4, 4, 4, 4, 4, 4 }}
    }};

    if (IS_UNLIKELY(ownMode > blendmodeTable.size() || neighborMode > blendmodeTable[ownMode].size())) {
        WARN << "invalid mode" <<  ownMode << neighborMode;
        return 0;
    }

    return blendmodeTable[ownMode][neighborMode];
}

const sf::Texture &Terrain::blendImage(const Blend blends, int tileX, int tileY)
{
    if (m_blendImages.find(blends) != m_blendImages.end()) {
        return m_blendImages[blends];
    }

    sf::Image sourceImage = image(tileX, tileY);
    const Size size = sourceImage.getSize();

    const size_t byteCount = size.width * size.height * 4;

    // fuck msvc
    std::vector<Uint8> pixelsBuf(byteCount);
    Uint8 *pixels = pixelsBuf.data();
    memcpy(pixels, sourceImage.getPixelsPtr(), byteCount);

    const genie::BlendMode &blend = AssetManager::Inst()->getBlendmode(blends.blendMode);
    std::vector<uint8_t> alphamask;
    for (unsigned i=0; i < Blend::BlendTileCount; i++) {
        if ((blends.bits & (1u << i)) == 0) {
            continue;
        }

        if (alphamask.size() < blend.alphaValues[i].size()) {
            alphamask.resize(blend.alphaValues[i].size(), 0x7f);
        }

        for (size_t j=0; j<blend.alphaValues[i].size(); j++) {
            alphamask[j] = std::min(alphamask[j], blend.alphaValues[i][j]);
        }
    }

    int blendOffset = 0;
    const int height = size.height;
    const int width = size.width;
    for (int y = 0; y < height; y++) {
        uint32_t lineWidth = 0;
        if (y < height/2) {
            lineWidth = 1 + (4 * y);
        } else {
            lineWidth = (height * 2 - 1) - (4 * (y - height/2));
        }

        int offsetLeft = height - 1 - (lineWidth  / 2);

        if (IS_UNLIKELY(blendOffset + lineWidth > alphamask.size())) {
            WARN << "Trying to read out of bounds (blendoffset" << blendOffset << "linewidth" << lineWidth << "=" << (blendOffset + lineWidth) << ">" << alphamask.size();
            break;
        }

        for (uint32_t x = 0; x < lineWidth; x++) {
            const int paletteIndex = y * width + x + offsetLeft;

            pixels[paletteIndex * 4 + 3] = 255 - std::min((2 * alphamask[blendOffset]), 255);
            blendOffset++;
        }
    }

    sf::Image blendImage;
    blendImage.create(size.width, size.height, pixels);

    m_blendImages[blends].loadFromImage(blendImage);

    return m_blendImages[blends];
}

const sf::Texture &Terrain::slopedImage(const TileSlopes &slopes, const std::vector<genie::Pattern> &patterns, int tileX, int tileY)
{
    if (m_slopeImages.find(slopes) != m_slopeImages.end()) {
        return m_slopeImages[slopes];
    }

    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (tileY % tileSquareCount) + (tileX % tileSquareCount) * tileSquareCount;

    genie::SlpFramePtr frame = AssetManager::Inst()->getSlpTemplateFile()->getFrame(m_slp->getFrame(frameNum), slopes.self.toGenie(), patterns, AssetManager::Inst()->getPalette().getColors(), m_slp);
    sf::Image img = Resource::convertFrameToImage(frame);
    if (!img.getSize().x) {
        static sf::Texture nullTex;
        if (nullTex.getSize().x == 0) {
            sf::Image nullImg;
            nullImg.create(Constants::TILE_SIZE_HORIZONTAL, Constants::TILE_SIZE_VERTICAL, sf::Color::Red);
            nullTex.loadFromImage(nullImg);
        }

        return nullTex;
    }

#ifdef DEBUG
    addOutline(img);
#endif

    m_slopeImages[slopes].loadFromImage(img);
    return m_slopeImages[slopes];
}

uint32_t Terrain::coordinatesToFrame(int x, int y)
{
    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
}

//const sf::Texture &Terrain::texture(const MapTile &tile)
//{

////    const int tileSquareCount = sqrt(m_slp->getFrameCount());
////    const int frameNum = (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;

//}

void Terrain::addOutline(sf::Image &img)
{
    for (size_t x=2;x<img.getSize().x; x++) {
        for (size_t y=0;y<img.getSize().y; y++) {
            if (img.getPixel(x-1, y).a == 255 && (img.getPixel(x-2, y).a == 0 || (y == 0 && x%2))) {
                img.setPixel(x, y, sf::Color::White);
                continue;
            }
        }
    }
}
