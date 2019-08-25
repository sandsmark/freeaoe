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

#include "core/Types.h"
#include "core/Utility.h"
#include "AssetManager.h"
#include "DataManager.h"

#include <genie/resource/Color.h>

sf::Image Resource::convertFrameToImage(const genie::SlpFramePtr &frame)
{
    return convertFrameToImage(frame, AssetManager::Inst()->getPalette(50500));
}

//------------------------------------------------------------------------------
sf::Image Resource::convertFrameToImage(const genie::SlpFramePtr &frame,
                                         const genie::PalFile &palette, const int playerColor)
{
    if (!frame) {
        sf::Image img;
        img.create(10, 10, sf::Color::Red);
        return img;
    }

    const uint32_t width = frame->getWidth();
    const uint32_t height = frame->getHeight();
    if (!width || !height) {
        sf::Image img;
        img.create(1, 1, sf::Color::Transparent);
        return img;
    }
    const genie::SlpFrameData &frameData = frame->img_data;
    const int area = width * height;


    // fuck msvc
    std::vector<Uint8> pixelsBuf(area * 4);
    Uint8 *pixels = pixelsBuf.data();

    if (frame->is32bit()) {
        const std::vector<uint32_t> &bgraSrc = frameData.bgra_channels;
        assert(area <= bgraSrc.size());
        for (int i=0; i<area; i++) {
            const int bgra = bgraSrc[i];
            *pixels++ = (bgra >> 16) & 0xFF; // r
            *pixels++ = (bgra >> 8) & 0xFF; // g
            *pixels++ = bgra & 0xFF; // b
            *pixels++ = (bgra >> 24) & 0xFF; //a
        }
    } else {
        const std::vector<genie::Color> &colors = palette.colors_;
        const std::vector<uint8_t> &pixelindexes = frameData.pixel_indexes;
        const std::vector<uint8_t> &alphachannel = frameData.alpha_channel;
        for (int i=0; i<area; i++) {
            const genie::Color &col = colors[pixelindexes[i]];
            *pixels++ = col.r;
            *pixels++ = col.g;
            *pixels++ = col.b;
            *pixels++ = alphachannel[i];
        }

        pixels = pixelsBuf.data();
        if (playerColor >= 0) {
            const genie::PlayerColour &pc = DataManager::Inst().getPlayerColor(playerColor);
            for (const genie::PlayerColorXY mask : frameData.player_color_mask) {
                const genie::Color &color = palette[mask.index + pc.PlayerColorBase];

                const size_t pixelPos = (mask.y * width + mask.x) * 4;
                pixels[pixelPos    ] = color.r;
                pixels[pixelPos + 1] = color.g;
                pixels[pixelPos + 2] = color.b;
            }
        }
    }

    sf::Image img;
    img.create(width, height, pixelsBuf.data());

    return img;
}
