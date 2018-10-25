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

    sf::Image sourceImage = image(tileX, tileY);
    const Size size = sourceImage.getSize();

    const size_t byteCount = size.width * size.height * 4;

    // fuck msvc
    std::vector<Uint8> pixelsBuf(byteCount);
    Uint8 *pixels = pixelsBuf.data();
    memcpy(pixels, sourceImage.getPixelsPtr(), byteCount);

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

const sf::Texture &Terrain::texture(const MapTile &tile)
{
    if (m_textures.find(tile) != m_textures.end()) {
        return m_textures[tile];
    }

    genie::SlpFramePtr srcFrame = m_slp->getUnloadedFrame(tile.frame);
    assert(srcFrame->getHeight() == 49);

    std::vector<uint8_t> srcData;
    std::string stringdata = m_slp->fileData();
    srcData.reserve(stringdata.size());
    for (size_t i=0; i<stringdata.size(); i++) {
        srcData.push_back(stringdata[i]);
    }
    const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette().getColors();
    const genie::IcmFile::InverseColorMap &icm = AssetManager::Inst()->getSlpTemplateFile()->filtermapFile.patternmasksFile.icmFile.maps[9]; // fixme this shit

    std::vector<uint8_t> data;

    uint8_t width[48];
    uint8_t size = 1;
    for(int i = 0; i < 25; i++){
        width[i] = size;
        width[48-i] = size;
        size += 4;
    }

    data = srcData;
//    for (const Blend &tileBlend : tile.blends) {
    for (size_t blendIdx = 0; blendIdx < tile.blends.size(); blendIdx++) {
//        data = srcData;
        const Blend &tileBlend = tile.blends[blendIdx];
        const genie::BlendMode &blendMode = AssetManager::Inst()->getBlendmode(tileBlend.blendMode);
        std::vector<uint8_t> alphamask;
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


        TerrainPtr blendTerrain = AssetManager::Inst()->getTerrain(tileBlend.terrainId);
        genie::SlpFramePtr blendFrame = blendTerrain->m_slp->getFrame(blendTerrain->coordinatesToFrame(tileBlend.x, tileBlend.y));
//        const std::vector<uint8_t> &blendSrcData = blendTerrain->m_slp->fileData();
        std::vector<uint8_t> blendSrcData;
        std::string stringdata = blendTerrain->m_slp->fileData();
        blendSrcData.reserve(stringdata.size());
        for (size_t i=0; i<stringdata.size(); i++) {
            blendSrcData.push_back(stringdata[i]);
        }

        int alphaOffset = 0;
        for (int y=0; y<srcFrame->getHeight(); y++) {
            int srcOffset = srcFrame->cmd_offsets_[y];
            int blendSrcOffset = blendFrame->cmd_offsets_[y];

            if (width[y] <= 0x3f) {
                data[srcOffset++] = width[y] << 2;
//                data.push_back(width[y] << 2);
//                srcOffset++;
                blendSrcOffset++;
            } else {
                data[srcOffset++] = 0x2;
                data[srcOffset++] = width[y];
//                data.push_back(0x2);
//                data.push_back(width[y]);
//                srcOffset += 2;
                blendSrcOffset += 2;
            }

            for (int x=0; x<width[y]; x++) {
                uint8_t alpha = alphamask[alphaOffset++];
                if (alpha == 0x80) {
                    data.push_back(srcData[srcOffset]);
                } else if (alpha == 0) {
                    data[srcOffset] = blendSrcData[srcOffset];
//                    data.push_back(blendSrcData[srcOffset]);
                } else {
                    genie::Color col1 = colors[srcData[srcOffset]];
                    genie::Color col2 = colors[blendSrcData[blendSrcOffset]];
                    int r = col1.r * alpha + col2.r * (0x80 - alpha);
                    int g = col1.g * alpha + col2.g * (0x80 - alpha);
                    int b = col1.b * alpha + col2.b * (0x80 - alpha);
                    data[srcOffset] = icm.paletteIndex(r >> 10, g >> 10, b >> 10);
//                    data.push_back(icm.paletteIndex(r >> 10, g >> 10, b >> 10));
                }
                srcOffset++;
                blendSrcOffset++;
            }

            data[srcOffset++] = 0x0f;
//            data.push_back(0x0f);
        }

        srcData = data;
    }
//    data = srcData;
//    srcData = data;
//    data.clear();
//    WARN << data.size() << srcData.size();

    if (0){
        sf::Image image;
        image.create(srcFrame->getWidth(), srcFrame->getHeight(), sf::Color::Transparent);

        int srcOffset = 0;
//        int srcOffset = srcFrame->outline_table_offset_;
        for (uint32_t y=0; y<srcFrame->getHeight(); y++) {

//            if (tile.blends.empty()) {
                srcOffset = srcFrame->cmd_offsets_[y];
//            }

            int xPos = srcFrame->left_edges_[y];

            for (int x=0; x<width[y]; x++) {
                assert(srcOffset < srcData.size());
                uint8_t cmd = srcData[srcOffset];
//                DBG << srcOffset << int(srcData[srcOffset]);
                if ((cmd & 0x3) == 0) {
//                    DBG << "writing small";
                    int npx = uint8_t(srcData[srcOffset++]) >> 2;
//                    DBG << "writing small" << npx;
                    assert(npx >= 0);
                    assert(npx < image.getSize().x);
                    while(npx--) {
                        assert(xPos < image.getSize().x);

                        int idx = srcData[srcOffset++];
                        const genie::Color color = colors[idx];
                        image.setPixel(xPos++, y, sf::Color(color.r, color.g, color.b));
                        x++;
                    }
                    continue;
                }
                if ((cmd & 0x3) == 1) {
                    srcOffset++;
                    xPos++;
                    x++;
//                    DBG << "skipping small";
                    continue;
                }
                if ((cmd & 0xf) == 0x2) {
                    int npx = (srcData[srcOffset++] & 0xF0) << 4;
                    npx |= srcData[srcOffset++];
                    while(npx--) {
                        const genie::Color color = colors[srcData[srcOffset++]];
                        image.setPixel(xPos++, y, sf::Color(color.r, color.g, color.b));
                        x++;
                    }
                    continue;
                }
                if ((cmd & 0xf) == 0x3) {
                    int npx = int(srcData[srcOffset++] & 0xF0) << 4;
                    npx |= srcData[srcOffset++];
                    xPos += npx;
                    x += npx;
                    continue;
                }
                if ((cmd & 0xf) == 0xf) {
                    break;
                }
                WARN << int(srcData[srcOffset]);
            }
        }

//        m_textures[tile].loadFromImage(image);
//        return m_textures[tile];
    }


    const genie::SlpTemplateFile::SlpTemplate &slpTemplate = AssetManager::Inst()->getSlpTemplateFile()->templates[tile.slopes.self.toGenie()];
    genie::FiltermapFile &filterFile = AssetManager::Inst()->getSlpTemplateFile()->filtermapFile;
    const genie::FiltermapFile::Filtermap filter = filterFile.maps[tile.slopes.self.toGenie()];
//    assert(filter.height == 49);
    const genie::PatternMasksFile &patternmasksFile = filterFile.patternmasksFile;

    sf::Image image;
    image.create(srcFrame->getWidth(), filter.height, sf::Color::Transparent);
    for (uint32_t y=0; y<filter.height; y++) {
        int xPos = slpTemplate.left_edges_[y];

        assert(y < filter.lines.size());

        const genie::FiltermapFile::FilterLine &line = filter.lines[y];

        for (uint32_t x=0; x<line.width; x++, xPos++) {
            if (x >= line.commands.size()) {
                WARN << "out of bounds: "  << x << " " << line.commands.size();
            }
            assert(x < line.commands.size());

            const genie::FiltermapFile::FilterCmd &cmd = line.commands[x];

            int r = 0, g = 0, b = 0;
            for (const genie::FiltermapFile::SourcePixel source : cmd.sourcePixels) {
                const uint8_t sourcePaletteIndex = data[source.sourceIndex + srcFrame->cmd_offsets_[0]];
                const genie::Color sourceColor = colors[sourcePaletteIndex];
                r += int(sourceColor.r) * source.alpha;
                g += int(sourceColor.g) * source.alpha;
                b += int(sourceColor.b) * source.alpha;
            }

            const genie::IcmFile::InverseColorMap &icm = patternmasksFile.getIcm(cmd.lightIndex, tile.slopePatterns());
            const uint8_t pixelIndex = icm.paletteIndex(r >> 11, g >> 11, b >> 11);
            const genie::Color newColor = colors[pixelIndex];

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
