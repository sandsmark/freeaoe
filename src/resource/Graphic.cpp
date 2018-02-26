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

const sf::Image Graphic::nullImage;

//------------------------------------------------------------------------------
Graphic::Graphic(const genie::Graphic &data) :
    data_(data)
{
    slp_ = ResourceManager::Inst()->getSlp(data_.SLP, ResourceManager::ResourceType::Graphics);

    if (!slp_) {
        log.debug("Failed to get slp for id %d", data_.SLP);
        return;
    }
}

//------------------------------------------------------------------------------
Graphic::~Graphic()
{
}

//------------------------------------------------------------------------------
const sf::Image &Graphic::getImage(uint32_t frame_num, float angle)
{
    if (!slp_) {
        return nullImage;
    }

    bool mirrored = false;
    if (data_.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angle);
        if (lookupAngle > data_.AngleCount/2) {
            mirrored = true;
            lookupAngle = data_.AngleCount - lookupAngle;
        }
        frame_num += lookupAngle * data_.FrameCount;
    }

    std::unordered_map<int, sf::Image> &cache = mirrored ? m_flippedImages : m_images;

    if (cache.count(frame_num)) {
        return cache[frame_num];
    }

    if (frame_num >= slp_->getFrameCount()) {
        log.error("trying to look up %, but we only have %", frame_num, slp_->getFrameCount());
        frame_num = 0;
    }

    sf::Image img = Resource::convertFrameToImage(slp_->getFrame(frame_num));

    if (mirrored) {
        img.flipHorizontally();
    }
    cache[frame_num] = img;

    return cache[frame_num];
}

const sf::Image &Graphic::overlayImage(uint32_t frame_num, float angle, uint8_t playerId)
{
    if (!slp_) {
        log.error("Failed to load slp");
        return nullImage;
    }

    genie::PlayerColour pc = DataManager::Inst().getPlayerColor(playerId);
    genie::PalFilePtr palette = ResourceManager::Inst()->getPalette(50500);

    bool mirrored = false;
    if (data_.AngleCount > 1) {
        int lookupAngle = angleToOrientation(angle);
        if (lookupAngle > data_.AngleCount/2) {
            mirrored = true;
            lookupAngle = data_.AngleCount - lookupAngle;
        }
        frame_num += lookupAngle * data_.FrameCount;
    }

    if (frame_num >= slp_->getFrameCount()) {
        log.error("trying to look up %d, but we only have %", frame_num, slp_->getFrameCount());
        frame_num = 0;
    }

    if (m_overlays.count(frame_num)) {
        return m_overlays[frame_num];
    }

    const genie::SlpFramePtr frame = slp_->getFrame(frame_num);
    const genie::SlpFrameData &frameData = frame->img_data;

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    sf::Image img;
    img.create(width, height, sf::Color::Transparent);

    genie::Color outlineColor = (*palette)[pc.UnitOutlineColor];
    const sf::Color outline(outlineColor.r, outlineColor.g, outlineColor.b);
    for (const genie::XY pos : frameData.outline_pc_mask) {
        img.setPixel(pos.x, pos.y, outline);
    }

    if (mirrored) {
        img.flipHorizontally();
    }
    m_overlays[frame_num] = img;

    return m_overlays[frame_num];
}

//------------------------------------------------------------------------------
ScreenPos Graphic::getHotspot(uint32_t frame_num, bool mirrored) const
{
    if (frame_num >= slp_->getFrameCount()) {
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
    while (lookupAngle > data_.AngleCount) {
        lookupAngle -= data_.AngleCount;
    }
    while (lookupAngle < 0) {
        lookupAngle += data_.AngleCount;
    }

    return lookupAngle;
}

}
