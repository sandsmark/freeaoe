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

uint32_t Terrain::coordinatesToFrame(int x, int y)
{
    const int tileSquareCount = sqrt(m_slp->getFrameCount());
    return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
}

const sf::Texture &Terrain::texture(const MapTile &tile)
{
    if (m_textures.find(tile) != m_textures.end()) {
        return m_textures[tile];
    }

    std::vector<uint8_t> data = m_slp->fileData();

    const std::vector<genie::Color> colors = AssetManager::Inst()->getPalette().getColors();
    const genie::IcmFile::InverseColorMap &icm = AssetManager::Inst()->patternmasksFile().icmFile.maps[9]; // fixme this shit

    uint8_t width[48];
    uint8_t size = 1;
    for(int i = 0; i < 25; i++){
        width[i] = size;
        width[48-i] = size;
        size += 4;
    }

    for (size_t blendIdx = 0; blendIdx < tile.blends.size(); blendIdx++) {
        const Blend &tileBlend = tile.blends[blendIdx];
        const genie::BlendMode &blendMode = AssetManager::Inst()->getBlendmode(tileBlend.blendMode);
        std::vector<uint8_t> alphamask(blendMode.pixelCount, 0x80);
        for (unsigned i=0; i < Blend::BlendTileCount; i++) {
            if ((tileBlend.bits & (1u << i)) == 0) {
                continue;
            }

            if (alphamask.size() < blendMode.alphaValues[i].size()) {
                alphamask.resize(blendMode.alphaValues[i].size(), 0x80);
            }

            for (size_t j=0; j<blendMode.alphaValues[i].size(); j++) {
                alphamask[j] = std::min(alphamask[j], blendMode.alphaValues[i][j]);
            }
        }


        const TerrainPtr blendTerrain = AssetManager::Inst()->getTerrain(tileBlend.terrainId);
        const int blendFrame = blendTerrain->coordinatesToFrame(tileBlend.x, tileBlend.y);
        const std::vector<uint8_t> &blendData = blendTerrain->m_slp->fileData();

        int alphaOffset = 0;
        for (int y=0; y<m_slp->frameHeight(tile.frame); y++) {
            int srcOffset = m_slp->frameCommandsOffset(tile.frame, y);
            int blendOffset = blendTerrain->m_slp->frameCommandsOffset(blendFrame, y);

            if (width[y] <= 0x3f) {
                data[srcOffset++] = width[y] << 2;
                blendOffset++;
            } else {
                data[srcOffset++] = 0x2;
                data[srcOffset++] = width[y];
                blendOffset += 2;
            }

            for (int x=0; x<width[y]; x++) {
                uint8_t alpha = alphamask[alphaOffset++];
                if (alpha == 0x80) {
                } else if (alpha == 0) {
                    data[srcOffset] = blendData[srcOffset];
                } else {
                    genie::Color col1 = colors[data[srcOffset]];
                    genie::Color col2 = colors[blendData[blendOffset]];
                    int r = col1.r * alpha + col2.r * (0x80 - alpha);
                    int g = col1.g * alpha + col2.g * (0x80 - alpha);
                    int b = col1.b * alpha + col2.b * (0x80 - alpha);
                    data[srcOffset] = icm.paletteIndex(r >> 10, g >> 10, b >> 10);
                }
                srcOffset++;
                blendOffset++;
            }

            data[srcOffset++] = 0x0f;
        }
    }

    const genie::SlpTemplateFile::SlpTemplate &slpTemplate = AssetManager::Inst()->getSlpTemplateFile()->templates[tile.slopes.self.toGenie()];
    const genie::FiltermapFile &filterFile = AssetManager::Inst()->filtermapFile();
    const genie::FiltermapFile::Filtermap &filter = filterFile.maps[tile.slopes.self.toGenie()];
    const genie::PatternMasksFile &patternmasksFile = AssetManager::Inst()->patternmasksFile();

    sf::Image image;
    image.create(m_slp->frameWidth(tile.frame), filter.height, sf::Color::Transparent);

    const uint32_t baseOffset = m_slp->frameCommandsOffset(tile.frame, 0);
    const uint8_t *rawData = data.data() + baseOffset;
    const std::vector<genie::Pattern> slopePatterns = tile.slopePatterns();
    const genie::IcmFile::InverseColorMap &defaultIcm = patternmasksFile.icmFile.maps[4];
    for (uint32_t y=0; y<filter.height; y++) {
        int xPos = slpTemplate.left_edges_[y];
        const genie::FiltermapFile::FilterLine &line = filter.lines[y];

        for (uint32_t x=0; x<line.width; x++, xPos++) {
            if (x >= line.commands.size()) {
                WARN << "out of bounds: "  << x << " " << line.commands.size();
            }

            const genie::FiltermapFile::FilterCmd &cmd = line.commands[x];

            int r = 0, g = 0, b = 0;
            for (const genie::FiltermapFile::SourcePixel &source : cmd.sourcePixels) {
                const uint8_t sourcePaletteIndex = rawData[source.sourceIndex];
                const genie::Color sourceColor = colors[sourcePaletteIndex];
                r += sourceColor.r * source.alpha;
                g += sourceColor.g * source.alpha;
                b += sourceColor.b * source.alpha;
            }

            uint8_t pixelIndex;
            if (slopePatterns.empty()) {
                pixelIndex = defaultIcm.paletteIndex(r >> 11, g >> 11, b >> 11);
            } else {
                const genie::IcmFile::InverseColorMap &icm = patternmasksFile.getIcm(cmd.lightIndex, slopePatterns);
                pixelIndex = icm.paletteIndex(r >> 11, g >> 11, b >> 11);
            }

            const genie::Color &newColor = colors[pixelIndex];

            image.setPixel(xPos, y, sf::Color(newColor.r, newColor.g, newColor.b));
        }
    }

    m_textures[tile].loadFromImage(image);

    return m_textures[tile];
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
