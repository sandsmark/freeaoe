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

#include "TerrainSprite.h"

#include "Sprite.h"
#include "DataManager.h"
#include "AssetManager.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/Types.h"
#include "core/Utility.h"

#include <genie/resource/BlendomaticFile.h>
#include <genie/resource/Color.h>
#include <genie/resource/SlpFile.h>

#include <SFML/Config.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <assert.h>
#include <algorithm>
#include <array>
#include <utility>
#include <vector>

#include <cmath>
#include <cstdint>

#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#error "I don't think big endian will work with SFML images"
#endif
#endif


TerrainSprite::TerrainSprite(unsigned int id_) : id(id_)
{
    const genie::Terrain *data = &DataManager::Inst().getTerrain(id);
    if (data->TerrainToDraw != -1) {
        data = &DataManager::Inst().getTerrain(data->TerrainToDraw);
    }
    if (!data->Enabled) {
        DBG << "Terrain disabled!";
        return;
    }

    m_slp = AssetManager::Inst()->getSlp(data->SLP);

#if PNG_TERRAIN_TEXTURES
    if (!m_slp) {
        DBG << data->Name2;
        const std::string pngFolder = AssetManager::Inst()->assetsPath() + "/terrain/textures/";

        // Resolves case because windows is retard case insensitive
        m_pngPath = AssetManager::findFile(data->Name2 + "_00_color.png", pngFolder);
        if (m_pngPath.empty()) {
            DBG << "failed to find terrain SLP by ID and failed to find PNG texture" << data->Name << data->Name << data->Enabled;
            return;
        }
        DBG << "Found PNG file" << m_pngPath;
        m_isPng = true;
        DBG << data->TerrainDimensions.first << data->TerrainDimensions.second;
    }
#endif

    if (!m_slp) {
        WARN << "Failed to get slp for" << data->SLP;
        m_slp = AssetManager::Inst()->getSlp(15000); // TODO Loading grass if -1

        return;
    }
    m_tileSquareCount = sqrt(m_slp->getFrameCount());
}

TerrainSprite::~TerrainSprite() {  }

#if PNG_TERRAIN_TEXTURES
const Drawable::Image::Ptr &TerrainSprite::pngTexture(const MapTile &tile, const IRenderTargetPtr &renderer)
{
    if (!m_isPng) {
        WARN << "is not png?";
        return Drawable::Image::null;
    }

    const std::unordered_map<MapTile, Drawable::Image::Ptr>::iterator it = m_textures.find(tile);
    if (it != m_textures.end() && it->second) {
        return it->second;
    }

    sf::Image sourceImage;
    sourceImage.loadFromFile(m_pngPath);


    const int cols = sourceImage.getSize().x / 64;

    sf::IntRect subRect;
    subRect.width = Constants::TILE_SIZE_HORIZONTAL;
    subRect.height = Constants::TILE_SIZE_VERTICAL;
    subRect.left = (tile.frame % cols) * 64;
    subRect.top = (tile.frame / cols) * 64;

    const int area = subRect.width * subRect.height;

    // First generate an alpha mask that we use to blend the two frames below
    const int byteCount = area * 4;
    if (byteCount <= 0) {
        WARN << "invalid size" << subRect.width << subRect.height;
        return Drawable::Image::null;
    }
    std::vector<uint8_t> pixelsBuf(byteCount, 0);
    uint8_t *pixels = pixelsBuf.data();
    const sf::Uint8 *sourcePixels = sourceImage.getPixelsPtr();
    Vector2u sourceSize = sourceImage.getSize();

    uint8_t widths[49];
    uint8_t size = 1;
    uint8_t leftEdge[49];
    for(int i = 0; i < 25; i++){
        widths[i] = size;
        widths[48-i] = size;
        leftEdge[i] = Constants::TILE_SIZE_HORIZONTAL/2 - size/2;
        leftEdge[48 - i] = Constants::TILE_SIZE_HORIZONTAL/2 - size/2;
        size += 4;
    }

    for (int y = 0; y<Constants::TILE_SIZE_VERTICAL; y++) {
        for (int x = 0; x<widths[y]; x++) {
            const int index = (y * Constants::TILE_SIZE_HORIZONTAL + x + leftEdge[y]) * 4;
            ScreenPos sourcePos = MapPos(x, y).toScreen() ;
            sourcePos += ScreenPos(Constants::TILE_SIZE_HORIZONTAL, Constants::TILE_SIZE_VERTICAL);
            if (sourcePos.x < 0 || sourcePos.x >= sourceSize.x) {
                continue;
            }
            if (sourcePos.y < 0 || sourcePos.y >= sourceSize.y) {
                continue;
            }
            const int sourceIndex = (sourcePos.y * sourceSize.x + sourcePos.x) * 4;
            pixels[index + 0] = sourcePixels[sourceIndex + 0];
            pixels[index + 1] = sourcePixels[sourceIndex + 1];
            pixels[index + 2] = sourcePixels[sourceIndex + 2];
            pixels[index + 3] = 255;
        }
    }

    const std::string pngFolder = AssetManager::Inst()->assetsPath() + "/terrain/textures/";
#if DEBUG_TERRAIN_TEXTURES
    float maxAlpha = 0.f;
    float minAlpha = 1.f;
#endif
    for (const Blend &tileBlend : tile.blends) {
        const genie::BlendMode &blendMode = AssetManager::Inst()->getBlendmode(tileBlend.blendMode);
        std::vector<float> alphamask(area, 1.);
        if (blendMode.pixelCount >= alphamask.size()) {
            WARN << "Invalid alphamask";
            break;
        }

        for (unsigned i=0; i < Blend::BlendTileCount; i++) {
            if ((tileBlend.bits & (1u << i)) == 0) {
                continue;
            }

            for (unsigned j=0; j<blendMode.alphaValues[i].size(); j++) {
                alphamask[j] = std::min(alphamask[j], blendMode.alphaValues[i][j] / 128.f);
#if DEBUG_TERRAIN_TEXTURES
                maxAlpha = std::max(alphamask[j], maxAlpha);
                minAlpha = std::min(alphamask[j], minAlpha);
#endif
            }
        }

        const genie::Terrain *data = &DataManager::Inst().getTerrain(tileBlend.terrainId);
        const std::string blendPngPath = AssetManager::findFile(data->Name2 + "_00_color.png", pngFolder);
        sf::Image blendSourceImage;
        blendSourceImage.loadFromFile(blendPngPath);
        if (!blendSourceImage.getSize().x) {
            WARN << "Invalid blend" << blendPngPath << tileBlend.terrainId;
            continue;
        }
        Vector2u blendSourceSize = blendSourceImage.getSize();
        const sf::Uint8 *blendSourcePixels = blendSourceImage.getPixelsPtr();

        int alphaOffset = 0;
        for (int y = 0; y<Constants::TILE_SIZE_VERTICAL; y++) {
            for (int x = 0; x<widths[y]; x++) {
                const int index = (y * Constants::TILE_SIZE_HORIZONTAL + x + leftEdge[y]) * 4;
                ScreenPos sourcePos = MapPos(x, y).toScreen() ;
                sourcePos += ScreenPos(Constants::TILE_SIZE_HORIZONTAL, Constants::TILE_SIZE_VERTICAL);
                if (sourcePos.x < 0 || sourcePos.x >= blendSourceSize.x) {
                    continue;
                }
                if (sourcePos.y < 0 || sourcePos.y >= blendSourceSize.y) {
                    continue;
                }
                const int sourceIndex = (sourcePos.y * sourceSize.x + sourcePos.x) * 4;
                const float alpha = alphamask[alphaOffset];
                pixels[index + 0] = (blendSourcePixels[sourceIndex + 0] * (1.f - alpha)) + (pixels[index + 0] *( alpha));
                pixels[index + 1] = (blendSourcePixels[sourceIndex + 1] * (1.f - alpha)) + (pixels[index + 1] *( alpha));
                pixels[index + 2] = (blendSourcePixels[sourceIndex + 2] * (1.f - alpha)) + (pixels[index + 2] *( alpha));
                alphaOffset++;
            }
        }
    }

#if 0
    // This is used to alter the source SLP (for sloping), but we mostly ignore it,
    // we only need the modified offset to the left and then use the texture filtering for the rest
    const genie::SlpTemplateFile::SlpTemplate &slpTemplate = AssetManager::Inst()->getSlpTemplateFile()->templates[tile.slopes.self.toGenie()];

    // This defines the texture mapping for slopes (what pixels from the original SLP should go where)
    const genie::FiltermapFile::Filtermap &filter = AssetManager::Inst()->filtermapFile()->maps[tile.slopes.self.toGenie()];

    const std::vector<genie::Pattern> &slopePatterns = tile.slopePatterns();

    const int width = m_slp->frameWidth(tile.frame);
    const int area = width * filter.height;

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
            const genie::IcmFile::InverseColorMap &icm = patternmasksFile->getIcm(cmd.lightIndex, slopePatterns);
            const int pixelIndex = icm.paletteIndex(r >> 11, g >> 11, b >> 11);

            // And then finally we get the color for a single pixel
            pixels[y * width + xPos] = colors[pixelIndex].toUint32();
        }
    }
#endif
    m_textures[tile] = renderer->createImage(Size(subRect.width, subRect.height), pixelsBuf.data());
    return m_textures[tile];
}

#endif//PNG_TERRAIN_TEXTURES

const Drawable::Image::Ptr &TerrainSprite::texture(const MapTile &tile, const IRenderTargetPtr &renderer)
{
#if PNG_TERRAIN_TEXTURES
    if (m_isPng) {
        return pngTexture(tile, renderer);
    }
#endif
    // The original graphics code in aoe was apparently hand-written assembly according to people on the internet,
    // and since I'm too lazy and too dumb to optimize this properly we just cache heavily instead
    const std::unordered_map<MapTile, Drawable::Image::Ptr>::const_iterator it = m_textures.find(tile);
    if (it != m_textures.end()) {
        return it->second;
    }
    if (IS_UNLIKELY(!m_slp)) {
        return Drawable::Image::null;
    }

    // This defines lightning textures (e. g. to darken edges)
    std::shared_ptr<genie::PatternMasksFile> patternmasksFile = AssetManager::Inst()->patternmasksFile();

    // We need to keep operating on indexed colors with the right palette until we've done all
    // the transformations and mapping and lighting
    const genie::Color * const colors = AssetManager::Inst()->getPalette().getColors().data();

    // This maps from RGB to indices in the palette
    const genie::IcmFile::InverseColorMap &defaultIcm = patternmasksFile->icmFile.maps[genie::IcmFile::AokNeutral];

    // Precalculate the line widths
    // This could be static or a constexpr or something, but way out of a hot path so meh
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

        if (blendMode.pixelCount < Blend::BlendTileCount) {
            WARN << "Invalid blendmode" << tileBlend.blendMode << "pixel count:" << blendMode.pixelCount << "requires" << int(Blend::BlendTileCount);
            continue;
        }

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
                    const genie::Color col1 = colors[data[srcOffset]];
                    const genie::Color col2 = colors[blendData[blendOffset]];
                    const unsigned r = col1.r * alpha + col2.r * (128 - alpha);
                    const unsigned g = col1.g * alpha + col2.g * (128 - alpha);
                    const unsigned b = col1.b * alpha + col2.b * (128 - alpha);

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
    const genie::FiltermapFile::Filtermap &filter = AssetManager::Inst()->filtermapFile()->maps[tile.slopes.self.toGenie()];

    const std::vector<genie::Pattern> &slopePatterns = tile.slopePatterns();

    const int width = m_slp->frameWidth(tile.frame);
    const int area = width * filter.height;
    if (area <= 0) {
        WARN << "invalid size" << width << filter.height;
        return Drawable::Image::null;
    }

    std::vector<Uint8> pixelsBuf(area * 4, 0);
    uint32_t *pixels = reinterpret_cast<uint32_t*>(pixelsBuf.data());

    for (unsigned y=0; y<filter.height; y++) {
        int xPos = slpTemplate.left_edges_[y];
        const genie::FiltermapFile::FilterLine &line = filter.lines[y];

        for (unsigned x=0; x<line.width; x++, xPos++) {
            const genie::FiltermapFile::FilterCmd &cmd = line.commands[x];

            // Each target pixel can blend several source pixels
            int r = 0, g = 0, b = 0;

            // Don't use value based for loops or other dumb c++ iterator shit, it is slooow
            for (unsigned i = 0; i < cmd.sourcePixelCount; i++) {
                const genie::FiltermapFile::SourcePixel source = cmd.sourcePixels[i];

                // This is the hottest path of them all...
                const genie::Color sourceColor = colors[data[source.sourceIndex]];
                r += sourceColor.r * source.alpha;
                g += sourceColor.g * source.alpha;
                b += sourceColor.b * source.alpha;
            }

            // Get the appropriate lightning from the pattern masks file
            // There are several lightning textures used for each tile, so here we blend them
            // together to get the inverse color map with the appropriate darkness for this pixel
            const genie::IcmFile::InverseColorMap &icm = patternmasksFile->getIcm(cmd.lightIndex, slopePatterns);
            const int pixelIndex = icm.paletteIndex(r >> 11, g >> 11, b >> 11);

            // And then finally we get the color for a single pixel
            pixels[y * width + xPos] = colors[pixelIndex].toUint32();
        }
    }

#ifdef DEBUG
    addOutline(pixels, width, filter.height);
#endif

    if (renderer) {
        m_textures[tile] = renderer->createImage(Size(width, filter.height), reinterpret_cast<uint8_t*>(pixels));
    } else {
        DBG << "no renderer!";
    }

    return m_textures[tile];
}

bool TerrainSprite::isValid() const noexcept
{
#if PNG_TERRAIN_TEXTURES
    if (m_isPng) {
        return !m_pngPath.empty();
    }
#endif

    return m_slp != nullptr;
}


#define ALPHA_MASK 0xff000000

void TerrainSprite::addOutline(uint32_t *pixels, const int width, const int height) noexcept
{
    for (size_t x=2;x<width; x++) {
        for (size_t y=0;y<height; y++) {
            const uint8_t nonTransparentLeft = (pixels[y * width + x - 1] & ALPHA_MASK) != 0;
            const uint8_t transparentTwoLeft = (pixels[y * width + x - 2] & ALPHA_MASK) == 0;
            const unsigned index = y * width + x;
            const uint8_t isTop = (y == 0) & (x % 2);
            if ((nonTransparentLeft & (transparentTwoLeft | isTop))) {
                pixels[index] = 0xFFFFFFFF;
            }
        }
    }
}
