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

#include "Resource.h"

#include <global/Types.h>
#include <genie/resource/Color.h>
#include "ResourceManager.h"
#include "DataManager.h"

namespace res {

//------------------------------------------------------------------------------
Resource::Resource(Uint32 id, Type type) :
    id_(id), type_(type), loaded_(false)
{
}

//------------------------------------------------------------------------------
Resource::~Resource()
{
    unload();
}

//------------------------------------------------------------------------------
Uint32 Resource::getId() const
{
    return id_;
}

//------------------------------------------------------------------------------
Resource::Type Resource::getType() const
{
    return type_;
}

//------------------------------------------------------------------------------
bool Resource::isLoaded() const
{
    return loaded_;
}

sf::Image Resource::convertFrameToImage(const genie::SlpFramePtr frame)
{
    return convertFrameToImage(frame, ResourceManager::Inst()->getPalette(50500));
}

//------------------------------------------------------------------------------
bool Resource::load()
{
    setLoaded(true);

    return true;
}

//------------------------------------------------------------------------------
void Resource::unload()
{
    setLoaded(false);
}

//------------------------------------------------------------------------------
void Resource::setLoaded(bool loaded)
{
    loaded_ = loaded;
}

//------------------------------------------------------------------------------
sf::Image Resource::convertFrameToImage(const genie::SlpFramePtr frame,
                                         const genie::PalFile &palette, const int playerId)
{
    if (!frame) {
        sf::Image img;
        img.create(10, 10, sf::Color::Red);
        return img;
    }

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    const genie::SlpFrameData &frameData = frame->img_data;

    sf::Image img;
    img.create(width, height, sf::Color::Red);

    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];
            assert(paletteIndex < palette.size());
            const genie::Color &g_color = palette[paletteIndex];
            img.setPixel(col, row, sf::Color(g_color.r,
                                             g_color.g,
                                             g_color.b,
                                             frameData.alpha_channel[row * width + col]
                                             ));
        }
    }

    const sf::Color shadow(0, 0, 0, 128);
    for (const genie::XY pos : frameData.shadow_mask) {
        img.setPixel(pos.x, pos.y, shadow);
    }

    genie::PlayerColour pc  = DataManager::Inst().getPlayerColor(playerId);
    if (playerId > 0) {
        for (const genie::PlayerColorXY mask : frameData.player_color_mask) {
            const genie::Color &color = palette[mask.index + pc.PlayerColorBase];
            img.setPixel(mask.x, mask.y, sf::Color(color.r, color.g, color.b));
        }
    }

    return img;
}
}
