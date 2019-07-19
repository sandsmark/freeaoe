/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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

#include "Graphic.h"
#include <resource/DataManager.h>
#include "AssetManager.h"
#include <core/Utility.h>

#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <genie/resource/Color.h>

const sf::Texture Graphic::nullImage;

//------------------------------------------------------------------------------
Graphic::Graphic(const genie::Graphic &data, const int id) :
    graphicId(id),
    m_data(data),
    m_runOnce(data.SequenceType & genie::Graphic::SequenceOnce)
{

    if (data.SLP < 0) {
        WARN << data.Name << "doesn't have a SLP id" << data.ID << data.Deltas.size();
        return;
    }

    slp_ = AssetManager::Inst()->getSlp(data.SLP, AssetManager::ResourceType::Graphics);

    if (!slp_) {
//        log.debug("Failed to get slp % for ", data_.SLP, data_.Name);
        return;
    }
}

sf::Image Graphic::slpFrameToImage(const genie::SlpFramePtr &frame, int8_t playerColor, const ImageType imageType) noexcept
{
    const genie::PalFile &palette = AssetManager::Inst()->getPalette(50500);
    const genie::SlpFrameData &frameData = frame->img_data;
    const int width = frame->getWidth();
    const int height = frame->getHeight();

    sf::Image img;
    if (width < 1 || height < 1) {
        img.create(1, 1, sf::Color::Transparent);
        return img;
    }

    switch(imageType) {
    case ImageType::Base:
        img = Resource::convertFrameToImage(frame, palette, playerColor);
        break;
    case ImageType::Shadow: {
        img.create(width, height, sf::Color::Transparent);

        const sf::Color shadow(0, 0, 0, 128);
        for (const genie::XY pos : frameData.shadow_mask) {
            img.setPixel(pos.x, pos.y, shadow);
        }

        break;
    }
    case ImageType::Outline: {
        if (playerColor < 0) {
            img.create(1, 1, sf::Color::Transparent);
            return img;
        }
        img.create(width, height, sf::Color::Transparent);

        const genie::PlayerColour pc = DataManager::Inst().getPlayerColor(playerColor);
        const genie::PalFile &palette = AssetManager::Inst()->getPalette(50500);
        genie::Color outlineColor = palette[pc.UnitOutlineColor];
        const sf::Color outline(outlineColor.r, outlineColor.g, outlineColor.b);

        for (const genie::XY pos : frameData.outline_pc_mask) {
            img.setPixel(pos.x, pos.y, outline);
        }

        break;
    }
    case ImageType::ConstructionUnavailable: {
        // fuck msvc
        std::vector<Uint8> pixelsBuf(width * height * 4);
        Uint8 *pixels = pixelsBuf.data();

        for (uint32_t row = 0; row < height; row++) {
            for (uint32_t col = 0; col < width; col++) {
                const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];
                assert(paletteIndex < palette.colors_.size());

                const genie::Color &g_color = palette.colors_[paletteIndex];
                const size_t pixelPos = (row * width + col) * 4;

                if ((row + col) % 2 == 1) {
                    pixels[pixelPos    ] = g_color.r;
                    pixels[pixelPos + 1] = g_color.g;
                    pixels[pixelPos + 2] = g_color.b;
                    pixels[pixelPos + 3] = frameData.alpha_channel[row * width + col];
                } else {
                    pixels[pixelPos    ] = 255;
                    pixels[pixelPos + 1] = 0;
                    pixels[pixelPos + 2] = 0;
                    pixels[pixelPos + 3] = frameData.alpha_channel[row * width + col]/2;
                }
            }
        }

        img.create(width, height, pixels);
        break;
    }
    case ImageType::Construction: {
        // fuck msvc
        std::vector<Uint8> pixelsBuf(width * height * 4);
        Uint8 *pixels = pixelsBuf.data();

        for (uint32_t row = 0; row < height; row++) {
            for (uint32_t col = 0; col < width; col++) {
                const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];
                assert(paletteIndex < palette.colors_.size());

                const genie::Color &g_color = palette.colors_[paletteIndex];
                const size_t pixelPos = (row * width + col) * 4;

                if ((row + col) % 2 == 1) {
                    pixels[pixelPos    ] = g_color.r;
                    pixels[pixelPos + 1] = g_color.g;
                    pixels[pixelPos + 2] = g_color.b;
                    pixels[pixelPos + 3] = frameData.alpha_channel[row * width + col];
                } else {
                    pixels[pixelPos    ] = g_color.r/2;
                    pixels[pixelPos + 1] = g_color.g/2;
                    pixels[pixelPos + 2] = g_color.b/2;
                    pixels[pixelPos + 3] = frameData.alpha_channel[row * width + col]/2;
                }
            }
        }

        img.create(width, height, pixels);
        break;
    }
    case ImageType::InTheShadows: {
        // fuck msvc
        std::vector<Uint8> pixelsBuf(width * height * 4);
        Uint8 *pixels = pixelsBuf.data();

        for (uint32_t row = 0; row < height; row++) {
            for (uint32_t col = 0; col < width; col++) {
                const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];
                assert(paletteIndex < palette.colors_.size());

                const genie::Color &g_color = palette.colors_[paletteIndex];
                const size_t pixelPos = (row * width + col) * 4;

                pixels[pixelPos    ] = g_color.r / 2;
                pixels[pixelPos + 1] = g_color.g / 2;
                pixels[pixelPos + 2] = g_color.b / 2;
                pixels[pixelPos + 3] = frameData.alpha_channel[row * width + col];
            }
        }

        img.create(width, height, pixels);
        break;
    }
    default:
        WARN << "Trying to get invalid image type" << imageType;
        break;
    }

    return img;
}

const sf::Texture &Graphic::texture(uint32_t frameNum, float angleRadians, int8_t playerColor, const ImageType imageType) noexcept
{
    if (!slp_) {
        return nullImage;
    }

    GraphicState state;
    state.frame = frameNum;
    state.playerColor = playerColor;
    state.type = imageType;

    const FrameInfo frameInfo = calcFrameInfo(frameNum, angleRadians);
    state.frame = frameInfo.frameNum;
    state.flipped = frameInfo.mirrored;

    if (m_cache.count(state)) {
        return m_cache[state];
    }

    if (state.frame >= slp_->getFrameCount()) {
        WARN << "trying to look up" << state.frame << "but we only have" << slp_->getFrameCount();
        state.frame = 0;
    }

    sf::Image img = slpFrameToImage(slp_->getFrame(state.frame), playerColor, imageType);

    if (state.flipped) {
        img.flipHorizontally();
    }

    m_cache[state].loadFromImage(img);

    return m_cache[state];

}

Size Graphic::size(uint32_t frame_num, float angle) const noexcept
{
    if (!slp_) {
        return Size(0, 0);
    }

    genie::SlpFramePtr frame = getFrame(frame_num, angle);

    return Size(frame->getWidth(), frame->getHeight());
}

ScreenRect Graphic::rect(uint32_t frame_num, float angle) const noexcept
{
    ScreenRect ret;
    const ScreenPos hotspot = getHotspot(frame_num, angle);
    ret.x = -hotspot.x;
    ret.y = -hotspot.y;
    const sf::Vector2u frameSize = size(frame_num, angle);
    ret.width = frameSize.x;
    ret.height = frameSize.y;

    return ret;
}

//------------------------------------------------------------------------------
ScreenPos Graphic::getHotspot(uint32_t frame_num, float angle) const noexcept
{
    if (!slp_) {
        return ScreenPos();
    }

    if (slp_->getFrameCount() == 0) {
        return ScreenPos();
    }

    FrameInfo frameInfo = calcFrameInfo(frame_num, angle);
    genie::SlpFramePtr frame = slp_->getFrame(frameInfo.frameNum);

    int32_t hot_spot_x = frame->hotspot_x;
    if (frameInfo.mirrored) {
        hot_spot_x = frame->getWidth() - hot_spot_x;
    }

    return ScreenPos(hot_spot_x, frame->hotspot_y);
}

bool Graphic::checkClick(const ScreenPos &pos, uint32_t frame_num, float angle) const noexcept
{
    if (!slp_) {
        return false;
    }

    FrameInfo frameInfo = calcFrameInfo(frame_num, angle);
    genie::SlpFramePtr frame = slp_->getFrame(frameInfo.frameNum);
    if (!frame || pos.x < 0 || pos.y < 0 || pos.x > frame->getWidth() || pos.y > frame->getHeight()) {
        return false;
    }


    switch (m_data.TransparentSelection) {
    case genie::Graphic::SelectOnPixels: {

        const std::vector<uint8_t> &alphachannel = frame->img_data.alpha_channel;

        const size_t pixelPos = (std::round(pos.y) * frame->getWidth() + std::round(pos.x));
        if (pixelPos > alphachannel.size()) {
            return false;
        }

        if (alphachannel[pixelPos] > 0) {
            return true;
        }

        const genie::GameVersion gameVersion = DataManager::Inst().gameVersion();
        if (gameVersion >= genie::GV_AoKE3 && gameVersion <= genie::GV_TC) {
            return false;
        }
        DBG << "Assuming" << gameVersion << "needs to check pixels with mask";
        // I assume this is needed for another version of Genie
        genie::XY spot;
        spot.x = std::round(pos.x);
        spot.y = std::round(pos.y);

        const std::vector<genie::XY> &mask = frame->img_data.transparency_mask;
        return std::find(mask.begin(), mask.end(), spot) != mask.end();
    }
    case genie::Graphic::SelectInBox: {
        return (pos.x > 0 && pos.y > 0 &&
                pos.x < frame->getWidth() && pos.y < frame->getHeight());
    }
    case genie::Graphic::NotSelectable:
    default:
        return false;
    }
}



const genie::GraphicAngleSound &Graphic::soundForAngle(float angle) const noexcept
{
    const int orientation = angleToOrientation(angle);
    return m_data.AngleSounds[orientation % m_data.AngleSounds.size()];
}

//------------------------------------------------------------------------------

int Graphic::angleToOrientation(float angle) const noexcept
{
    // The graphics start pointing south, and goes clock-wise
    angle = fmod(- angle - M_PI_2, 2*M_PI);
    if (angle < 0) angle += 2*M_PI;

    return int(std::round(m_data.AngleCount * angle / (2*M_PI))) % m_data.AngleCount;
}

float Graphic::orientationToAngle(float orientation) const noexcept
{
    float angle = 2. * M_PI * orientation / m_data.AngleCount;
    angle = fmod(- angle - M_PI_2, 2*M_PI);
    if (angle < 0) angle += 2*M_PI;
    return angle;
}

const genie::SlpFramePtr &Graphic::getFrame(uint32_t frame_num, float angle) const noexcept
{
    return slp_->getFrame(calcFrameInfo(frame_num, angle).frameNum);
}

Graphic::FrameInfo Graphic::calcFrameInfo(uint32_t num, float angle) const noexcept
{
    FrameInfo ret;

    ret.frameNum = num;
    if (m_data.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angle);

        if (m_data.MirroringMode && lookupAngle > m_data.AngleCount/2) {
            ret.mirrored = true;
            lookupAngle = m_data.AngleCount - lookupAngle;
        }
        ret.frameNum += lookupAngle * m_data.FrameCount;
    }

    if (ret.frameNum >= slp_->getFrameCount()) {
//        WARN << "trying to look up" << ret.frameNum << "but we only have" << slp_->getFrameCount();
        ret.frameNum = 0;
    }

    return ret;
}
