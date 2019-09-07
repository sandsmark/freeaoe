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

#include "core/Constants.h"
#include "core/Utility.h"

#include <cmath>

#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#error "I don't think big endian will work with SFML images"
#endif
#endif


Terrain::~Terrain() { }

bool Terrain::load() noexcept
{
    if (m_isLoaded) {
        return true;
    }

    m_isLoaded = true;

    m_data = DataManager::Inst().getTerrain(id).TerrainToDraw != -1 ?
                DataManager::Inst().getTerrain(m_data.TerrainToDraw) :
                DataManager::Inst().getTerrain(id);


    m_slp = AssetManager::Inst()->getSlp(m_data.SLP);
    if (!m_slp) {
        DBG << m_data.Name2;
        const std::string pngFolder = AssetManager::Inst()->assetsPath() + "/terrain/textures/";

        // Resolves case because windows is retard case insensitive
        m_pngPath = AssetManager::findFile(m_data.Name2 + "_00_color.png", pngFolder);
        if (m_pngPath.empty()) {
            DBG << "failed to find terrain SLP by ID and failed to find PNG texture" << m_data.Name << m_data.Name << m_data.Enabled;
            return false;
        }
        DBG << "Found PNG file" << m_pngPath;
        m_isPng = true;
        DBG << m_data.TerrainDimensions.first << m_data.TerrainDimensions.second;
    }
//    if (m_data.TerrainToDraw != -1) {
//        const int replacementSlp = DataManager::Inst().getTerrain(m_data.TerrainToDraw).SLP;
//        m_slp = AssetManager::Inst()->getSlp(replacementSlp);
//    } else {
//        m_slp = AssetManager::Inst()->getSlp(m_data.SLP);
//    }

    if (!m_slp) {
        WARN << "Failed to get slp for" << m_data.SLP;
        m_slp = AssetManager::Inst()->getSlp(15000); // TODO Loading grass if -1

        return false;
    }

    return true;
}

const genie::Terrain &Terrain::data() noexcept
{
    return m_data;
}

uint8_t Terrain::blendMode(const uint8_t ownMode, const uint8_t neighborMode) noexcept
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



const sf::Texture &Terrain::texture(const MapTile &tile) noexcept
{
    // The original graphics code in aoe was apparently hand-written assembly according to people on the internet,
    // and since I'm too lazy and too dumb to optimize this properly we just cache heavily instead
    const std::unordered_map<MapTile, sf::Texture>::const_iterator it = m_textures.find(tile);
    if (it != m_textures.end()) {
        return it->second;
    }
    if (IS_UNLIKELY(!m_slp)) {
        return Graphic::nullImage;
    }

    // This defines lightning textures (e. g. to darken edges)
    const genie::PatternMasksFile &patternmasksFile = AssetManager::Inst()->patternmasksFile();

    // We need to keep operating on indexed colors with the right palette until we've done all
    // the transformations and mapping and lighting
    const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette().getColors();

    // This maps from RGB to indices in the palette
    const genie::IcmFile::InverseColorMap &defaultIcm = patternmasksFile.icmFile.maps[genie::IcmFile::AokNeutral];

    // Precalculate the line widths
    uint8_t widths[49];
    uint8_t size = 1;
    for(int i = 0; i < 25; i++){
        widths[i] = size;
        widths[48-i] = size;
        size += 4;
    }

    // Copy out the relevant frame data so that we can work on it
    const int32_t baseOffset = m_slp->frameCommandsOffset(tile.frame, 0);
    std::vector<uint8_t> sourceData(m_slp->fileData().begin() + baseOffset, m_slp->fileData().end());
    uint8_t *data = sourceData.data();

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
            int srcOffset = m_slp->frameCommandsOffset(tile.frame, y) - baseOffset;
            assert(srcOffset >= 0);
            if (srcOffset < 0) {
                WARN << "invalid source offset" << srcOffset;
                break;
            }

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
                const uint8_t alpha = alphamask[alphaOffset];

                // Alpha goes from 0-128
                if (alpha == 0) {
                    data[srcOffset] = blendData[blendOffset];
                } else if (alpha != 128) {
                    const genie::Color &col1 = colors[data[srcOffset]];
                    const genie::Color &col2 = colors[blendData[blendOffset]];
                    const int r = col1.r * alpha + col2.r * (128 - alpha);
                    const int g = col1.g * alpha + col2.g * (128 - alpha);
                    const int b = col1.b * alpha + col2.b * (128 - alpha);

                    // The top five bits are used to look up the palette index
                    // E. g. we have max 255 * 128 = 32640, if we shift that 10
                    // we get 31 (there are 32 values for r, g and b in the ICMs)
                    data[srcOffset] = defaultIcm.paletteIndex(r >> 10, g >> 10, b >> 10);
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


    const std::vector<genie::Pattern> &slopePatterns = tile.slopePatterns();

    const int width = m_slp->frameWidth(tile.frame);
    const int area = width * filter.height;
    std::vector<Uint8> pixelsBuf(area * 4, 0);
    uint32_t *pixels = reinterpret_cast<uint32_t*>(pixelsBuf.data());

    for (uint32_t y=0; y<filter.height; y++) {
        int xPos = slpTemplate.left_edges_[y];
        const genie::FiltermapFile::FilterLine &line = filter.lines[y];

        for (uint32_t x=0; x<line.width; x++, xPos++) {
            const genie::FiltermapFile::FilterCmd &cmd = line.commands[x];

            // Each target pixel can blend several source pixels
            int r = 0, g = 0, b = 0;
            for (const genie::FiltermapFile::SourcePixel &source : cmd.sourcePixels) {
                const uint8_t sourcePaletteIndex = data[source.sourceIndex];
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
            pixels[y * width + xPos] = colors[pixelIndex].toUint32();
        }
    }

#ifdef DEBUG
    addOutline(pixels, width, filter.height);
#endif

    sf::Image image;
    image.create(width, filter.height, pixelsBuf.data());

    m_textures[tile].loadFromImage(image);

    return m_textures[tile];
}

sf::Sprite Terrain::sprite(const MapTile &tile) noexcept
{
    if (!m_isPng) {
        return sf::Sprite(texture(tile));
    }

    const std::unordered_map<MapTile, sf::Texture>::const_iterator it = m_textures.find(tile);
    if (it == m_textures.end()) {
        m_textures[tile].loadFromFile(m_pngPath);
    }

     sf::Texture &texture = m_textures[tile];
     const int cols = texture.getSize().x / 64;
     const int rows = texture.getSize().y / 64;

    sf::IntRect subRect;
    subRect.width = 68;
    subRect.height = 68;
    subRect.left = (tile.frame % cols) * 64;
    subRect.top = (tile.frame / cols) * 64;
    DBG << subRect.left << subRect.top << cols << rows << texture.getSize();

    sf::Sprite sprite(texture, subRect);
//    sprite.setOrigin(subRect.left + subRect.width/2, subRect.top + subRect.height/2);
    sprite.rotate(45);
    sprite.scale(1, 0.5);
    sprite.move(48.5, 0);
    return sprite;
}

bool Terrain::isValid() const noexcept
{
    if (!m_data.Enabled) {
        return false;
    }

    if (m_isPng) {
        return !m_pngPath.empty();
    }

    return m_slp != nullptr && m_data.Enabled;
}

#define ALPHA_MASK 0xff000000

void Terrain::addOutline(uint32_t *pixels, const int width, const int height) noexcept
{
    for (size_t x=2;x<width; x++) {
        for (size_t y=0;y<height; y++) {
            const bool nonTransparentLeft = (pixels[y * width + x - 1] & ALPHA_MASK) != 0;
            const bool transparentTwoLeft = (pixels[y * width + x - 2] & ALPHA_MASK) == 0;
            if (nonTransparentLeft && (transparentTwoLeft || (y == 0 && x%2))) {
                pixels[y * width + x] = 0xFFFFFFFF;

            }
        }
    }
}
