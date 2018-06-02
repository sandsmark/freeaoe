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

sf::Texture Resource::convertFrameToImage(const genie::SlpFramePtr frame)
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
sf::Texture Resource::convertFrameToImage(const genie::SlpFramePtr frame,
                                         const genie::PalFile &palette, const int playerId)
{
    if (!frame) {
        sf::Image img;
        img.create(10, 10, sf::Color::Red);
        sf::Texture t;
        t.loadFromImage(img);
        return t;
    }

    const int width = frame->getWidth();
    const int height = frame->getHeight();
    const genie::SlpFrameData &frameData = frame->img_data;

    const std::vector<genie::Color> colors = palette.colors_;
    const std::vector<uint8_t> alpha = frameData.alpha_channel;

    Uint8 pixels[width * height * 4];

    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            const uint8_t paletteIndex = frameData.pixel_indexes[row * width + col];

            assert(paletteIndex < colors.size());
            const genie::Color &g_color = colors[paletteIndex];

            const size_t pixelPos = (row * width + col) * 4;
            pixels[pixelPos + 0] = g_color.r;
            pixels[pixelPos + 1] = g_color.g;
            pixels[pixelPos + 2] = g_color.b;
            pixels[pixelPos + 3] = alpha[row * width + col];
        }
    }
    for (const genie::XY pos : frameData.shadow_mask) {
        pixels[pos.y * width + pos.x + 3] = 128;
    }

//    const sf::Color shadow(0, 0, 0, 128);
//    for (const genie::XY pos : frameData.shadow_mask) {
//        img.setPixel(pos.x, pos.y, shadow);
//    }

    if (playerId > 0) {
        genie::PlayerColour pc  = DataManager::Inst().getPlayerColor(playerId);
        for (const genie::PlayerColorXY mask : frameData.player_color_mask) {
            const genie::Color &color = palette[mask.index + pc.PlayerColorBase];
            const size_t pixelPos = (mask.y * width + mask.x) * 4;
            pixels[pixelPos + 0] = color.r;
            pixels[pixelPos + 1] = color.g;
            pixels[pixelPos + 2] = color.b;
//            img.setPixel(mask.x, mask.y, sf::Color(color.r, color.g, color.b));
        }
    }

    sf::Texture img;
    img.create(width, height);
    img.update(pixels);

    return img;
}
}
