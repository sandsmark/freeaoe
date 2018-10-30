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
    // The original graphics code in aoe was apparently hand-written assembly according to people on the internet,
    // and since I'm too lazy and too dumb to optimize this properly we just cache heavily instead
    std::unordered_map<MapTile, sf::Texture>::const_iterator it = m_textures.find(tile);
    if (it != m_textures.end()) {
        return it->second;
    }

    std::vector<uint8_t> data = m_slp->fileData();

    // This defines lightning textures (e. g. to darken edges)
    const genie::PatternMasksFile &patternmasksFile = AssetManager::Inst()->patternmasksFile();

    // We need to keep operating on indexed colors with the right palette until we've done all
    // the transformations and mapping and lighting
    const std::vector<genie::Color> colors = AssetManager::Inst()->getPalette().getColors();

    // This maps from RGB to indices in the palette
    const genie::IcmFile::InverseColorMap &icm = patternmasksFile.icmFile.maps[genie::IcmFile::AokNeutral];

    uint8_t widths[49];
    uint8_t size = 1;
    for(int i = 0; i < 25; i++){
        widths[i] = size;
        widths[48-i] = size;
        size += 4;
    }

    // We first need to blend it and "rewrite" the image data/commands, because the texture filtering works
    // by addressing the original commands in the image
    for (const Blend &tileBlend : tile.blends) {
        const genie::BlendMode &blendMode = AssetManager::Inst()->getBlendmode(tileBlend.blendMode);

        // First generate an alpha mask that we use to blend the two frames below
        std::vector<uint8_t> alphamask(blendMode.pixelCount, 128);
        for (unsigned i=0; i < Blend::BlendTileCount; i++) {
            if ((tileBlend.bits & (1u << i)) == 0) {
                continue;
            }

            for (size_t j=0; j<blendMode.alphaValues[i].size(); j++) {
                alphamask[j] = std::min(alphamask[j], blendMode.alphaValues[i][j]);
            }
        }


        const TerrainPtr blendTerrain = AssetManager::Inst()->getTerrain(tileBlend.terrainId);
        const std::vector<uint8_t> &blendData = blendTerrain->m_slp->fileData();

        int alphaOffset = 0;
        for (int y=0; y<m_slp->frameHeight(tile.frame); y++) {
            int srcOffset = m_slp->frameCommandsOffset(tile.frame, y);
            int blendOffset = blendTerrain->m_slp->frameCommandsOffset(tileBlend.frame, y);

            // We can assume that there aren't any fancy commands here (no player colors or shadows),
            // so we only check the width to see if it is a lesser or greater block copy
            if (widths[y] <= 63) {
                data[srcOffset++] = widths[y] << 2;
                blendOffset++;
            } else {
                data[srcOffset++] = genie::SlpFrame::GreaterBlockCopy;
                data[srcOffset++] = widths[y];
                blendOffset += 2;
            }

            for (int x=0; x<widths[y]; x++) {
                uint8_t alpha = alphamask[alphaOffset];

                // Alpha goes from 0-128
                if (alpha == 0) {
                    data[srcOffset] = blendData[blendOffset];
                } else if (alpha != 128) {
                    const genie::Color &col1 = colors[data[srcOffset]];
                    const genie::Color &col2 = colors[blendData[blendOffset]];
                    int r = col1.r * alpha + col2.r * (128 - alpha);
                    int g = col1.g * alpha + col2.g * (128 - alpha);
                    int b = col1.b * alpha + col2.b * (128 - alpha);

                    // The top five bits are used to look up the palette index
                    // E. g. we have max 255 * 128 = 32640, if we shift that 10
                    // we get 31 (there are 32 values for r, g and b in the ICMs)
                    data[srcOffset] = icm.paletteIndex(r >> 10, g >> 10, b >> 10);
                }

                srcOffset++;
                blendOffset++;
                alphaOffset++;
            }

            data[srcOffset++] = genie::SlpFrame::EndOfRow;
        }
    }

    // This is used to alter the source SLP (for sloping), but we mostly ignore it,
    // we only need the modified offset to the left and then use the texture filtering for the rest
    const genie::SlpTemplateFile::SlpTemplate &slpTemplate = AssetManager::Inst()->getSlpTemplateFile()->templates[tile.slopes.self.toGenie()];

    // This defines the texture mapping for slopes (what pixels from the original SLP should go where)
    const genie::FiltermapFile &filterFile = AssetManager::Inst()->filtermapFile();
    const genie::FiltermapFile::Filtermap &filter = filterFile.maps[tile.slopes.self.toGenie()];

    sf::Image image;
    image.create(m_slp->frameWidth(tile.frame), filter.height, sf::Color::Transparent);

    const uint32_t baseOffset = m_slp->frameCommandsOffset(tile.frame, 0);
    const uint8_t *rawData = data.data() + baseOffset;
    const std::vector<genie::Pattern> slopePatterns = tile.slopePatterns();
    for (uint32_t y=0; y<filter.height; y++) {
        int xPos = slpTemplate.left_edges_[y];
        const genie::FiltermapFile::FilterLine &line = filter.lines[y];

        for (uint32_t x=0; x<line.width; x++, xPos++) {
            const genie::FiltermapFile::FilterCmd &cmd = line.commands[x];

            // Each target pixel can blend several source pixels
            int r = 0, g = 0, b = 0;
            for (const genie::FiltermapFile::SourcePixel &source : cmd.sourcePixels) {
                const uint8_t sourcePaletteIndex = rawData[source.sourceIndex];
                const genie::Color &sourceColor = colors[sourcePaletteIndex];
                r += sourceColor.r * source.alpha;
                g += sourceColor.g * source.alpha;
                b += sourceColor.b * source.alpha;
            }

            // Get the appropriate lightning from the pattern masks file
            // There are several lightning textures used for each tile, so here we blend them
            // together to get the inverse color map with the appropriate darkness for this pixel
            const genie::IcmFile::InverseColorMap &icm = patternmasksFile.getIcm(cmd.lightIndex, slopePatterns);
            const int pixelIndex = icm.paletteIndex(r >> 11, g >> 11, b >> 11);

            // And then finally we get the color for a single pixel
            const genie::Color &newColor = colors[pixelIndex];
            image.setPixel(xPos, y, sf::Color(newColor.r, newColor.g, newColor.b));
        }
    }

#ifdef DEBUG
    addOutline(image);
#endif

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
