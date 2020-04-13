#include "IRenderTarget.h"

#include "resource/DataManager.h"
#include "resource/AssetManager.h"
#include <genie/resource/Color.h>
#include <genie/resource/SlpFrame.h>
#include <genie/resource/PalFile.h>

#include "render/Camera.h"

IRenderTarget::IRenderTarget() : m_camera(std::make_shared<Camera>())
{ }

IRenderTarget::~IRenderTarget() {}

Drawable::Image::Ptr IRenderTarget::convertFrameToImage(const genie::SlpFramePtr &frame)
{
    return convertFrameToImage(frame, AssetManager::Inst()->getPalette(50500));
}

Drawable::Image::Ptr IRenderTarget::convertFrameToImage(const genie::SlpFramePtr &frame, const genie::PalFile &palette, const int playerId) const
{
    if (!frame) {
        return createImage(Size(), nullptr);
    }

    const uint32_t width = frame->getWidth();
    const uint32_t height = frame->getHeight();
    const genie::SlpFrameData &frameData = frame->img_data;
    const int area = width * height;
    if (area == 0) {
        WARN << "Invalid SLP frame";
        return createImage(Size(), nullptr);
    }

    if (frame->is32bit()) {
        TIME_THIS;
        std::vector<uint32_t> pixelsBuf = frameData.bgra_channels;

        // BGRA to RGBA, idk if it's that efficient with fancy c++ for loops but it's not too slow at least
        for (uint32_t &pixel : pixelsBuf) {
            pixel = ((pixel & 0x000000ff) << 24)
                    | ((pixel & 0x0000ff00) << 8)
                    | ((pixel & 0x00ff0000) >> 8)
                    | ((pixel & 0xff000000) >> 24);
        }

        return createImage(Size(width, height), reinterpret_cast<uint8_t*>(pixelsBuf.data()));
    }

    // fuck msvc
    std::vector<Uint8> pixelsBuf(area * 4);
    Uint8 *pixels = pixelsBuf.data();

    const std::vector<genie::Color> &colors = palette.colors_;
    const std::vector<uint8_t> &pixelindexes = frameData.pixel_indexes;
    const std::vector<uint8_t> &alphachannel = frameData.alpha_channel;
    assert(pixelindexes.size() == area);
    assert(alphachannel.size() == area);
    for (int i=0; i<area; i++) {
        const genie::Color &col = colors[pixelindexes[i]];
        *pixels++ = col.r;
        *pixels++ = col.g;
        *pixels++ = col.b;
        *pixels++ = alphachannel[i];
    }

    pixels = pixelsBuf.data();
    if (playerId >= 0) {
        genie::PlayerColour pc = DataManager::Inst().getPlayerColor(playerId);
        for (const genie::PlayerColorXY mask : frameData.player_color_mask) {
            const genie::Color &color = palette[mask.index + pc.PlayerColorBase];

            const size_t pixelPos = (mask.y * width + mask.x) * 4;
            pixels[pixelPos    ] = color.r;
            pixels[pixelPos + 1] = color.g;
            pixels[pixelPos + 2] = color.b;
        }
    }

    return createImage(Size(width, height), pixels);
}

Drawable::Text::~Text() {  }

Drawable::Image::~Image() {  }
