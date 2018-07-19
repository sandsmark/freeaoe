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
#include "ResourceManager.h"

#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <genie/resource/Color.h>

namespace res {

const sf::Texture Graphic::nullImage;

//------------------------------------------------------------------------------
Graphic::Graphic(const genie::Graphic &data) :
    data_(data)
{
    if (data_.SLP < 0) {
        WARN << data_.Name << "doesn't have a SLP id" << data_.ID << data_.Deltas.size();
        return;
    }

    slp_ = ResourceManager::Inst()->getSlp(data_.SLP, ResourceManager::ResourceType::Graphics);

    if (!slp_) {
//        log.debug("Failed to get slp % for ", data_.SLP, data_.Name);
        return;
    }
}

//------------------------------------------------------------------------------
Graphic::~Graphic()
{
}

const sf::Texture &Graphic::texture(uint32_t frame, float angleRadians, uint8_t player, const ImageType imageType)
{
    if (!slp_) {
        return nullImage;
    }

    GraphicState state;
    state.frame = frame;
    state.playerId = player;
    state.type = imageType;

    const FrameInfo frameInfo = calcFrameInfo(frame, angleRadians);
    state.frame = frameInfo.frameNum;
    state.flipped = frameInfo.mirrored;

    if (m_cache.count(state)) {
        return m_cache[state];
    }

    if (state.frame >= slp_->getFrameCount()) {
        WARN << "trying to look up" << state.frame << "but we only have" << slp_->getFrameCount();
        state.frame = 0;
    }

    const genie::PalFile &palette = ResourceManager::Inst()->getPalette(50500);
    sf::Image img;
    switch(state.type) {
    case ImageType::Base:
        img = Resource::convertFrameToImage(slp_->getFrame(state.frame), palette, state.playerId);
        break;
    case ImageType::Outline: {
        const genie::SlpFramePtr frame = slp_->getFrame(state.frame);
        const genie::SlpFrameData &frameData = frame->img_data;

        const int width = frame->getWidth();
        const int height = frame->getHeight();
        img.create(width, height, sf::Color::Transparent);

        const genie::PlayerColour pc = DataManager::Inst().getPlayerColor(state.playerId);
        const genie::PalFile &palette = ResourceManager::Inst()->getPalette(50500);
        genie::Color outlineColor = palette[pc.UnitOutlineColor];
        const sf::Color outline(outlineColor.r, outlineColor.g, outlineColor.b);

        for (const genie::XY pos : frameData.outline_pc_mask) {
            img.setPixel(pos.x, pos.y, outline);
        }

        break;
    }
    case ImageType::Construction: {
        const genie::PalFile &palette = ResourceManager::Inst()->getPalette(50500);

        const genie::SlpFramePtr frame = slp_->getFrame(state.frame);
        const genie::SlpFrameData &frameData = frame->img_data;

        const uint32_t width = frame->getWidth();
        const uint32_t height = frame->getHeight();

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
    default:
        WARN << "Trying to get invalid image type" << state.type;
        return nullImage;
    }

    if (state.flipped) {
        img.flipHorizontally();
    }

    m_cache[state].loadFromImage(img);

    return m_cache[state];

}

const Size Graphic::size(uint32_t frame_num, float angle) const
{
    if (!slp_) {
        return Size(0, 0);
    }

    genie::SlpFramePtr frame = slp_->getFrame(calcFrameInfo(frame_num, angle).frameNum);

    return Size(frame->getWidth(), frame->getHeight());
}

//------------------------------------------------------------------------------
ScreenPos Graphic::getHotspot(uint32_t frame_num, float angle) const
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

const std::vector<genie::GraphicDelta> Graphic::deltas() const
{
    return data_.Deltas;
}

//------------------------------------------------------------------------------
float Graphic::getFrameRate() const
{
    return data_.FrameDuration;
}

//------------------------------------------------------------------------------
float Graphic::getReplayDelay() const
{
    return data_.ReplayDelay;
}

//------------------------------------------------------------------------------
uint32_t Graphic::getFrameCount() const
{
    return data_.FrameCount;
}

//------------------------------------------------------------------------------
uint32_t Graphic::getAngleCount() const
{
    return data_.AngleCount;
}

bool Graphic::isValid()
{
    return slp_ != nullptr;
}

bool Graphic::runOnce() const
{
    return (data_.SequenceType & genie::Graphic::SequenceOnce);
}

int Graphic::angleToOrientation(float angle) const
{
    // The graphics start pointing south, and goes clock-wise
    angle = - angle - M_PI_2;

    int lookupAngle = std::round(data_.AngleCount * angle / (M_PI * 2.));

    // The angle we get in isn't normalized
    lookupAngle %= data_.AngleCount;
    while (lookupAngle < 0) {
        lookupAngle += data_.AngleCount;
    }

    return lookupAngle;
}

Graphic::FrameInfo Graphic::calcFrameInfo(uint32_t num, float angle) const
{
    FrameInfo ret;
    ret.frameNum = num;
    if (data_.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angle);
        if (data_.MirroringMode && lookupAngle > data_.AngleCount/2) {
            ret.mirrored = true;
            lookupAngle = data_.AngleCount - lookupAngle;
        }
        ret.frameNum += lookupAngle * data_.FrameCount;
    }

    if (ret.frameNum >= slp_->getFrameCount()) {
//        WARN << "trying to look up" << ret.frameNum << "but we only have" << slp_->getFrameCount();
        ret.frameNum = 0;
    }

    return ret;
}

}
