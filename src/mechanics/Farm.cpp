#include "Farm.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/../ResourceUsage.h>
#include <genie/dat/unit/Creatable.h>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <algorithm>

#include "Map.h"
#include "Unit.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "core/Utility.h"
#include "resource/AssetManager.h"
#include "resource/Graphic.h"

class UnitManager;
struct Player;

Farm::Farm(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager) :
    Building(data_, player_, unitManager),
    m_farmRenderer(Size(data_.Size))
{
    if (!m_farmRenderer.setGraphic(defaultGraphics)) {
        WARN << "Failed to set graphic";
    }
}

void Farm::setCreationProgress(float progress) noexcept
{
    if (progress == m_creationProgress) {
        return;
    }

    m_creationProgress = std::min(progress, float(data()->Creatable.TrainTime));

    if (progress >= data()->Creatable.TrainTime) {
        setTerrain(FarmFinished);
    } else if (progress >= 2 * data()->Creatable.TrainTime / 3) {
        setTerrain(FarmConstruct2);
    } else if (progress > data()->Creatable.TrainTime / 3) {
        setTerrain(FarmConstruct1);
    } else {
        setTerrain(FarmConstruct0);
    }
}

bool Farm::update(Time time) noexcept
{
    bool updated = Unit::update(time);

    if (util::floatsEquals(resources[genie::ResourceType::FoodStorage], 0)) {
        setTerrain(FarmDead);
    }

    if (m_updated) {
        m_updated = false;
        return true;
    }

    return updated;
}

ScreenRect Farm::rect() const noexcept
{
    ScreenRect rect;
    rect.x = -Constants::TILE_SIZE_HORIZONTAL;
    rect.y = -Constants::TILE_SIZE_VERTICAL;
    rect.width = Constants::TILE_SIZE_HORIZONTAL * 2;
    rect.height = Constants::TILE_SIZE_VERTICAL * 2;
    return rect;
}

bool Farm::checkClick(const ScreenPos &pos) const noexcept
{
    return rect().contains(pos);
}

void Farm::setTerrain(const Farm::TerrainTypes terrainToSet) noexcept
{
    if (terrainToSet == m_currentTerrain) {
        return;
    }

    std::shared_ptr<Map> map = m_map.lock();
    if (!map) {
        WARN << "map went away";
        return;
    }

    const int tileX = position().x / Constants::TILE_SIZE;
    const int tileY = position().y / Constants::TILE_SIZE;
    float width = data()->Size.x;
    float height = data()->Size.y;
    for (int x = -width; x < width; x++) {
        for (int y = -height; y < height; y++) {
            map->updateTileAt(tileX + x, tileY + y, terrainToSet);
        }
    }

    m_currentTerrain = terrainToSet;
    m_updated = true;
}

FarmRender::FarmRender(const Size &size) :
    m_size(size)
{
    genie::SlpFilePtr slpFile = AssetManager::Inst()->getSlp(15023);
    if (!slpFile) {
        WARN << "failed to get slp for farm";
        return;
    }

    const genie::SlpFramePtr frame = slpFile->getFrame(0);
    if (!frame) {
        WARN << "failed to get farm frame";
        return;
    }

    m_availableTexture.loadFromImage(Graphic::slpFrameToImage(frame, 0, ImageType::Construction));
    m_unavailableTexture.loadFromImage(Graphic::slpFrameToImage(frame, 0, ImageType::ConstructionUnavailable));
}

void FarmRender::render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType pass) noexcept
{
    sf::Sprite sprite;
    if (pass == RenderType::ConstructAvailable) {
        sprite.setTexture(m_availableTexture);
    } else if (pass == RenderType::ConstructUnavailable) {
        sprite.setTexture(m_unavailableTexture);
    } else {
        return;
    }


    const ScreenPos pos = screenPos - ScreenPos(Constants::TILE_SIZE_HORIZONTAL / 2., Constants::TILE_SIZE_VERTICAL / 2.);

    const int tileHeight = Constants::TILE_SIZE;
    const int tileWidth = Constants::TILE_SIZE;

    for (int x = -m_size.width; x < m_size.width; x++) {
        for (int y = -m_size.height; y < m_size.height; y++) {
            const ScreenPos offset = MapPos(x*tileWidth, y*tileHeight).toScreen();
            sprite.setPosition(pos + offset);
            renderTarget.draw(sprite);
        }
    }
}
