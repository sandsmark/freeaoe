#include "Farm.h"
#include <genie/dat/Unit.h>
#include <genie/resource/SlpFile.h>
#include "global/Constants.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Map.h"

Farm::Farm(const genie::Unit &data_, int playerId, std::shared_ptr<Civilization> civilization, const std::shared_ptr<Map> &map) :
    Unit(data_, playerId, civilization),
    m_map(map)
{
    m_farmRenderer.setGraphic(defaultGraphics);
}

void Farm::setCreationProgress(float progress)
{
    if (progress == m_creationProgress) {
        return;
    }

    m_creationProgress = std::min(progress, float(data.Creatable.TrainTime));

    int terrainToSet = -1;

    if (progress >= data.Creatable.TrainTime) {
        terrainToSet = FarmFinished;
    } else if (progress >= 2 * data.Creatable.TrainTime / 3) {
        terrainToSet = FarmConstruct2;
    } else if (progress > data.Creatable.TrainTime / 3) {
        terrainToSet = FarmConstruct1;
    } else {
        terrainToSet = FarmConstruct0;
    }

    if (terrainToSet == m_currentTerrain) {
        return;
    }

    std::shared_ptr<Map> map = m_map.lock();
    if (!map) {
        WARN << "map went away";
        return;
    }

    const int tileX = position.x / Constants::TILE_SIZE;
    const int tileY = position.y / Constants::TILE_SIZE;
    int width = data.Size.x;
    int height = data.Size.y;
    for (int x = 0; x < width*2; x++) {
        for (int y = 0; y < height*2; y++) {
            map->updateTileAt(tileX - width + x, tileY - height + y, terrainToSet);
        }
    }

    m_currentTerrain = terrainToSet;
    m_updated = true;
}

bool Farm::update(Time time)
{
    bool updated = Unit::update(time);

    if (m_updated) {
        m_updated = false;
        return true;
    }

    return updated;
}

ScreenRect Farm::rect() const
{
    ScreenRect rect;
    rect.x = -Constants::TILE_SIZE_HORIZONTAL;
    rect.y = -Constants::TILE_SIZE_VERTICAL;
    rect.width = Constants::TILE_SIZE_HORIZONTAL * 2;
    rect.height = Constants::TILE_SIZE_VERTICAL * 2;
    return rect;
}

FarmRender::FarmRender()
{
    const genie::PalFile &palette = ResourceManager::Inst()->getPalette(50500);

    genie::SlpFilePtr slpFile = ResourceManager::Inst()->getSlp(15023);
    if (!slpFile) {
        WARN << "failed to get slp for farm";
        return;
    }

    const genie::SlpFramePtr frame = slpFile->getFrame(0);
    if (!frame) {
        WARN << "failed to get farm frame";
        return;
    }

    m_hotspot = ScreenPos(frame->hotspot_x, frame->hotspot_y) * 2;

    const genie::SlpFrameData &frameData = frame->img_data;

    const uint32_t width = frame->getWidth();
    const uint32_t height = frame->getHeight();

    // fuck msvc
    std::vector<Uint8> pixelsBuf(width * height * 4 * 4);
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

    sf::Image img;
    img.create(width, height, pixels);
    m_texture.loadFromImage(img);
}

void FarmRender::render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const comp::RenderType pass)
{
    if (pass != comp::RenderType::ConstructAvailable) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(m_texture);

    const ScreenPos pos = screenPos - ScreenPos(Constants::TILE_SIZE_HORIZONTAL / 2, Constants::TILE_SIZE_VERTICAL / 2);

    ScreenPos offset;
    offset = ScreenPos(0, Constants::TILE_SIZE_VERTICAL/2);
    sprite.setPosition(pos - offset);
    renderTarget.draw(sprite);
    sprite.setPosition(pos + offset);
    renderTarget.draw(sprite);

    offset = ScreenPos(Constants::TILE_SIZE_HORIZONTAL/2, 0);
    sprite.setPosition(pos + offset - m_hotspot);
    renderTarget.draw(sprite);
    sprite.setPosition(pos - offset - m_hotspot);
    renderTarget.draw(sprite);
}
