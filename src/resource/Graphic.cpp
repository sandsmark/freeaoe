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

Logger &Graphic::log = Logger::getLogger("freeaoe.resource.Graphic");

const sf::Texture Graphic::nullImage;

//------------------------------------------------------------------------------
Graphic::Graphic(const genie::Graphic &data) :
    data_(data)
{
    if (data_.SLP < 0) {
        log.debug("% doesn't have a SLP id", data_.Name);
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

    if (data_.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angleRadians);

        if (data_.MirroringMode && lookupAngle > data_.AngleCount/2) {
            state.flipped = true;
            lookupAngle = data_.AngleCount - lookupAngle;
        }
        state.frame += lookupAngle * data_.FrameCount;
    }

    if (m_cache.count(state)) {
        return m_cache[state];
    }

    if (state.frame >= slp_->getFrameCount()) {
        log.error("trying to look up %, but we only have %", state.frame, slp_->getFrameCount());
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
    default:
        log.error("Trying to get invalid image type %", state.type);
        return nullImage;
    }

    if (state.flipped) {
        img.flipHorizontally();
    }

    m_cache[state].loadFromImage(img);

    return m_cache[state];

}

const Size Graphic::size(uint32_t frame_num) const
{
    if (!slp_) {
        return Size(0, 0);
    }
    if (frame_num >= slp_->getFrameCount()) {
        log.error("trying to look up %d, but we only have %", frame_num, slp_->getFrameCount());
        frame_num = 0;
    }

    genie::SlpFramePtr frame = slp_->getFrame(frame_num);

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

    bool mirrored = false;
    if (data_.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angle);
        if (data_.MirroringMode && lookupAngle > data_.AngleCount/2) {
            mirrored = true;
            lookupAngle = data_.AngleCount - lookupAngle;
        }
        frame_num += lookupAngle * data_.FrameCount;
    }

    if (frame_num >= slp_->getFrameCount()) {
        log.error("trying to look up %d, but we only have %", frame_num, slp_->getFrameCount());
        frame_num = 0;
    }

    genie::SlpFramePtr frame = slp_->getFrame(frame_num);

    int32_t hot_spot_x = frame->hotspot_x;

    if (mirrored)
        hot_spot_x = frame->getWidth() - hot_spot_x;

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

}
