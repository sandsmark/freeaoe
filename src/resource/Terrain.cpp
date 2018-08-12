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
            m_slp = ResourceManager::Inst()->getSlp(m_data.SLP);
        }

        if (!m_slp) {
            WARN << "Failed to get slp for" << m_data.SLP;
            m_slp = ResourceManager::Inst()->getSlp(15000); // TODO Loading grass if -1

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

    const genie::BlendMode &blend = ResourceManager::Inst()->getBlendmode(blends.blendMode);
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

const sf::Texture &Terrain::slopedImage(const TileSlopes &slopes, int tileX, int tileY)
{
    if (m_slopeImages.find(slopes) != m_slopeImages.end()) {
        return m_slopeImages[slopes];
    }

    // The correct patterns for the different slopes is from aoetwols by aap
    // (I just chose a much more horrible way of looking up and storing them, FIXME I guess)
    std::vector<genie::Pattern> patterns;
    switch (slopes.self) {
    case Slope::SouthUp: {
        patterns.push_back(genie::DiagDownPattern);

        if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern18);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.north == Slope::Flat) + (slopes.northEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern19);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::NorthUp || slopes.northWest == Slope::WestUp || slopes.northWest == Slope::NorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.northEast != Slope::Flat && slopes.northEast != Slope::NorthUp && slopes.northEast != Slope::EastUp && slopes.northEast != Slope::NorthEastUp) {
            if (slopes.east != Slope::Flat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfRightPattern);
        }

        if (slopes.northEast == Slope::SouthWestEastUp || slopes.southEast == Slope::SouthWestEastUp || slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern22);
        }
        if (slopes.northWest == Slope::SouthWestEastUp || slopes.southWest == Slope::SouthWestEastUp || slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern21);
        }

        break;
    }
    case Slope::NorthUp: {
        patterns.push_back(genie::DiagDownPattern);
        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern16);
        }
        if ((slopes.southWest == Slope::Flat) + (slopes.south == Slope::Flat) + (slopes.southEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern17);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthUp || slopes.northWest == Slope::WestUp || slopes.southWest == Slope::SouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.southEast != Slope::Flat && slopes.southEast != Slope::SouthUp && slopes.southEast != Slope::EastUp && slopes.southEast != Slope::SouthEastUp) {
            if (slopes.east != Slope::Flat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }
        if (slopes.northWest == Slope::NorthWestEastUp || slopes.southWest == Slope::NorthWestEastUp || slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopes.northEast == Slope::NorthWestEastUp || slopes.southEast == Slope::NorthWestEastUp || slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern22);
        }

        break;
    }
    case Slope::WestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern12);
        }

        if ((slopes.northEast == Slope::Flat) + (slopes.east == Slope::Flat) + (slopes.southEast == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern13);
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::NorthUp || slopes.northEast == Slope::EastUp || slopes.southWest == Slope::NorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern34);
        }

        if (!(slopes.southEast == Slope::Flat || slopes.southEast == Slope::SouthUp || slopes.northEast == Slope::EastUp || slopes.northEast == Slope::SouthEastUp)) {
            if (slopes.south != Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }

        break;
    }
    case Slope::EastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern14);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.west == Slope::Flat) + (slopes.southWest == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern15);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthUp || slopes.southWest == Slope::WestUp || slopes.southWest == Slope::SouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopes.northWest != Slope::Flat && slopes.northWest != Slope::NorthUp && slopes.northWest != Slope::WestUp && slopes.northWest != Slope::NorthWestUp) {
            if (slopes.north != Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
        } else {
            patterns.push_back(genie::DownPattern);
        }

        break;
    }
    case Slope::SouthWestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthSouthEastUp || slopes.southWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        } else {
            if (slopes.west == Slope::Flat) {
                patterns.push_back(genie::Pattern12);
            }

            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::NorthUp || slopes.northEast == Slope::EastUp || slopes.northEast == Slope::NorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else {
            if (slopes.north == Slope::Flat || slopes.north == Slope::SouthUp) {
                patterns.push_back(genie::Pattern34);
            }
            if (slopes.east == Slope::Flat || slopes.east == Slope::EastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopes.south == Slope::SouthUp && slopes.southWest == Slope::WestUp) {
            patterns.push_back(genie::Pattern35);
        }

        if (slopes.southWest == Slope::SouthUp && slopes.west == Slope::WestUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northEast == Slope::SouthWestEastUp || slopes.southEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.northWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        break;
    }
    case Slope::NorthWestUp: {
        patterns.push_back(genie::FlatPattern);
        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::NorthSouthEastUp || slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        } else {
            if (slopes.west == Slope::Flat) {
                patterns.push_back(genie::Pattern12);
            }
            if (slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern34);
            }
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::SouthUp || slopes.southEast == Slope::EastUp || slopes.southEast == Slope::SouthEastUp) {
            patterns.push_back(genie::HalfUpPattern);
        } else {
            if (slopes.south == Slope::Flat || slopes.south == Slope::SouthUp) {
                patterns.push_back(genie::Pattern35);
            }

            if (slopes.east == Slope::Flat || slopes.east == Slope::EastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopes.southWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern34);
        }

        if (slopes.west == Slope::WestUp && slopes.northWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopes.northWest == Slope::WestUp && slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern34);
        }

        break;
    }
    case Slope::SouthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::NorthUp || slopes.northWest == Slope::WestUp || slopes.northWest == Slope::NorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopes.west == Slope::Flat || slopes.west == Slope::WestUp) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.north == Slope::Flat || slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthSouthWestUp || slopes.southEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::UpPattern);
        } else {
            if (slopes.east == Slope::Flat){
                patterns.push_back(genie::Pattern14);
            }
            if (slopes.south == Slope::Flat){
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopes.south == Slope::SouthUp && slopes.southEast == Slope::EastUp) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopes.southEast == Slope::SouthUp && slopes.east == Slope::EastUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopes.northEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.west == Slope::SouthUp) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }

        break;
    }
    case Slope::NorthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::SouthWestUp || slopes.southWest == Slope::WestUp || slopes.southWest == Slope::SouthUp) {
            patterns.push_back(genie::LeftPattern);
        } else {
            if (slopes.west == Slope::Flat || slopes.west == Slope::WestUp) {
                patterns.push_back(genie::Pattern26);
            }
            if (slopes.south == Slope::Flat || slopes.south == Slope::SouthUp) {
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::SouthWestEastUp || slopes.northEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::RightPattern);
        } else {
            if(slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
            if (slopes.east == Slope::Flat) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.east == Slope::EastUp || slopes.northEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopes.northEast == Slope::EastUp || slopes.north == Slope::NorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopes.southEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.northWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }
        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        break;
    }
    case Slope::SouthWestEastUp: {
        patterns.push_back(genie::DiagUpPattern);

        if (slopes.north == Slope::Flat) {
            patterns.push_back(genie::Pattern30);
        }

        if ((slopes.southEast == Slope::Flat) + (slopes.southWest == Slope::Flat) + (slopes.south == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern31);
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthSouthWestUp || slopes.southEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::UpPattern);
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthSouthEastUp || slopes.southWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        }

        if (slopes.south == Slope::SouthUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.southWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.northWest == Slope::SouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.northEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.southEast == Slope::SouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        break;
    }
    case Slope::NorthSouthWestUp: {
        patterns.push_back(genie::FlatPattern);

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern28);
        }

        if ((slopes.northWest == Slope::Flat) + (slopes.southWest == Slope::Flat) + (slopes.west == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern29);
        }

        if (slopes.east == Slope::EastUp || slopes.east == Slope::NorthEastUp || slopes.east == Slope::NorthEastUp) {
            patterns.push_back(genie::Pattern28);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::SouthWestEastUp || slopes.northWest == Slope::NorthSouthEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        } else {
            if (slopes.north == Slope::Flat || slopes.north == Slope::NorthUp) {
                patterns.push_back(genie::Pattern34);
            }

            if (slopes.northWest == Slope::NorthUp) {
                patterns.push_back(genie::Pattern12);
            }
        }

        if (slopes.southWest == Slope::Flat || slopes.southWest == Slope::NorthEastUp || slopes.southWest == Slope::NorthWestEastUp || slopes.southWest == Slope::NorthSouthEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        } else {
            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern35);
            }

            if (slopes.southWest == Slope::SouthUp) {
                patterns.push_back(genie::Pattern12);
            }
        }

        if (slopes.northEast == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopes.southEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern28);
        }

        break;
    }
    case Slope::NorthSouthEastUp: {
        patterns.push_back(genie::BlackPattern);

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern26);
        }

        if ((slopes.northEast == Slope::Flat) + (slopes.southEast == Slope::Flat) + (slopes.east == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern27);
        }

        if (slopes.west == Slope::WestUp || slopes.west == Slope::NorthWestUp || slopes.west == Slope::SouthWestUp) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::SouthWestEastUp || slopes.northEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::RightPattern);
        } else {
            if (slopes.north == Slope::Flat) {
                patterns.push_back(genie::Pattern36);
            }
            if (slopes.northEast == Slope::NorthUp) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.southEast == Slope::Flat || slopes.southEast == Slope::NorthWestUp || slopes.southEast == Slope::NorthWestEastUp || slopes.southEast == Slope::NorthSouthWestUp) {
            patterns.push_back(genie::UpPattern);
        } else {
            if (slopes.south == Slope::Flat) {
                patterns.push_back(genie::Pattern37);
            }
            if (slopes.southEast == Slope::SouthUp) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopes.northWest == Slope::NorthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }
        if (slopes.southWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::Pattern26);
        }

        break;
    }
    case Slope::NorthWestEastUp: {
        patterns.push_back(genie::DiagUpPattern);

        if ((slopes.northEast == Slope::Flat) + (slopes.northWest == Slope::Flat) + (slopes.north == Slope::Flat) > 1) {
            patterns.push_back(genie::Pattern33);
        }

        if (slopes.south == Slope::Flat) {
            patterns.push_back(genie::Pattern32);
        }

        if (slopes.northWest == Slope::Flat || slopes.northWest == Slope::SouthEastUp || slopes.northWest == Slope::NorthSouthEastUp || slopes.northWest == Slope::SouthWestEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        }
        if (slopes.northEast == Slope::Flat || slopes.northEast == Slope::SouthWestUp || slopes.northEast == Slope::NorthSouthWestUp || slopes.northEast == Slope::SouthWestEastUp) {
            patterns.push_back(genie::RightPattern);
        }

        if (slopes.east == Slope::Flat) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopes.west == Slope::Flat) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopes.southWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }
        if (slopes.northWest == Slope::NorthUp) {
            patterns.push_back(genie::Pattern23);
        }
        if (slopes.southEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }
        if (slopes.northEast == Slope::NorthUp) {
            patterns.push_back(genie::Pattern20);
        }

        break;
    }

    default:
        patterns.push_back(genie::BlackPattern);
        WARN << "unhandled slope" << slopes.self.direction;
        break;
    }

    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    const int frameNum = (tileY % tileSquareCount) + (tileX % tileSquareCount) * tileSquareCount;

    genie::SlpFramePtr frame = ResourceManager::Inst()->getSlpTemplateFile()->getFrame(m_slp->getFrame(frameNum), slopes.self.toGenie(), patterns, ResourceManager::Inst()->getPalette().getColors(), m_slp);
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
