#include "Minimap.h"

#include "core/Constants.h"
#include "core/Logger.h"
#include "core/Utility.h"
#include "mechanics/Map.h"
#include "mechanics/MapTile.h"
#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "render/Camera.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"

#include <genie/Types.h>
#include <genie/dat/Terrain.h>
#include <genie/dat/Unit.h>
#include <genie/resource/Color.h>
#include <genie/resource/PalFile.h>

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <functional>
#include <vector>

#include <assert.h>

Minimap::Minimap(const IRenderTargetPtr &renderTarget) :
    m_renderTarget(renderTarget),
    m_rect(865, 815, 400, 200)
{

}

void Minimap::setMap(const std::shared_ptr<Map> &map)
{
    if (map == m_map) {
        return;
    }

    if (!map) {
        WARN << "null map";
        return;
    }

    // FIXME disconnect this shit
    assert(!m_map);
    m_map = map;
    map->connect(Map::Signals::UnitsChanged, std::bind(&Minimap::updateUnits, this));
    map->connect(Map::Signals::TerrainChanged, std::bind(&Minimap::updateTerrain, this));

    m_unitsUpdated = true;

    m_lastCameraPos = MapPos(-1, -1);
    m_terrainUpdated = true;

}

void Minimap::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    if (unitManager == m_unitManager) {
        return;
    }

    if (!unitManager) {
        WARN << "null unit manager";
    }

    m_unitManager = unitManager;
    m_unitsUpdated = true;
}

void Minimap::setVisibilityMap(const std::shared_ptr<VisibilityMap> &visibilityMap)
{
    if (visibilityMap == m_visibilityMap) {
        return;
    }

    m_visibilityMap = visibilityMap;
}

void Minimap::updateUnits()
{
    m_unitsUpdated = true;
}

void Minimap::updateTerrain()
{
    m_terrainUpdated = true;
}

void Minimap::updateCamera()
{
    const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());
    const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
    const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;

    const Size viewSize = m_renderTarget->camera()->m_viewportSize;
    const MapPos cameraMapPos(m_renderTarget->camera()->m_target.y / Constants::TILE_SIZE, m_renderTarget->camera()->m_target.x / Constants::TILE_SIZE);
    const ScreenPos cameraPos = cameraMapPos.toScreen();
    const ScreenRect fullBoundingRect = MapRect(0, 0, mapDimensions.width * Constants::TILE_SIZE, mapDimensions.height * Constants::TILE_SIZE).boundingScreenRect();
    const ScreenPos center(m_rect.width/2, m_rect.height/2);

    m_cameraRect.width = m_rect.width * viewSize.width / fullBoundingRect.width;
    m_cameraRect.height = m_rect.height * viewSize.height / fullBoundingRect.height;
    m_cameraRect.x = m_rect.x + cameraPos.x * scaleX - m_cameraRect.width / 2;
    m_cameraRect.y = m_rect.y + cameraPos.y * scaleY + center.y - m_cameraRect.height / 2;
}

Drawable::Color Minimap::unitColor(const std::shared_ptr<Unit> &unit)
{
    if (unit->selected) {
        return Drawable::White;
    }

    switch(m_mode) {
    case MinimapMode::Normal:
        //TODO
        break;
    case MinimapMode::Diplomatic:
        if (unit->playerId == UnitManager::GaiaID) {
            return Drawable::Color(128, 192, 128);
        } else if (unit->playerId == 1) { ///TODO fixme get the human player
            return Drawable::Blue;
        } else {
            return Drawable::Red;
        }
        break;
    case MinimapMode::Economic:
        //TODO
        break;
    default:
        break;
    }

    return Drawable::Red;
}


bool Minimap::init()
{
    m_terrainTexture = m_renderTarget->createTextureTarget(m_rect.size());
    DBG << "creating texture target with size" << m_rect.size();
    m_terrainUpdated = true;
    return m_terrainTexture != nullptr;
}

bool Minimap::handleEvent(sf::Event event)
{
    ScreenPos pos;
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
        pos = ScreenPos(event.mouseButton.x, event.mouseButton.y);
    } else if (event.type == sf::Event::MouseMoved && m_mousePressed) {
        pos = ScreenPos(event.mouseMove.x, event.mouseMove.y);
    } else {
        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed && m_rect.contains(pos)) {
        m_mousePressed = true;
    } else if (event.type == sf::Event::MouseButtonReleased && m_mousePressed) {
        m_mousePressed = false;
        return true;
    }

    if (!m_rect.contains(pos)) {
        return m_mousePressed;
    }

    // normalize to 0,0
    pos.x -= m_rect.x;
    pos.y -= m_rect.y;

    pos.y = m_rect.height/2 - pos.y; // from the center

    const MapRect mapDimensions(0, 0, m_map->getCols() * Constants::TILE_SIZE, m_map->getRows() * Constants::TILE_SIZE);
    const ScreenRect fullBoundingRect = mapDimensions.boundingScreenRect();
    pos.x = fullBoundingRect.width * pos.x / m_rect.width;
    pos.y = fullBoundingRect.height * pos.y / m_rect.height;

    const MapPos mapPos = mapDimensions.bounded(pos.toMap());
    m_renderTarget->camera()->setTargetPosition(mapPos);

    return true;
}

bool Minimap::update(Time /*time*/)
{
    if (IS_UNLIKELY(!m_visibilityMap)) {
        WARN << "no visibility map set";
        return false;
    }

    if (m_lastCameraPos != m_renderTarget->camera()->m_target) {
        updateCamera();
        m_lastCameraPos = m_renderTarget->camera()->m_target;
    }

    if (!m_map || (!m_unitsUpdated && !m_terrainUpdated)) {
        return false;
    }

    const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());

    if (m_terrainUpdated) {
        DBG << "redrawing terrain";
        if (!m_terrainTexture ||  m_terrainTexture->getSize() != m_rect.size()) {
            DBG << "recreating terrain";
            m_terrainTexture = m_renderTarget->createTextureTarget(m_rect.size());
        }

        m_terrainTexture->clear(Drawable::Transparent);

        const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
        const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;

        Drawable::Circle background;
        background.aspectRatio = m_rect.height / m_rect.width;
        background.radius = std::floor(m_rect.width / 2);
        background.pointCount = 4;
        background.fillColor = Drawable::Black;
        background.filled = true;
        m_terrainTexture->draw(background);

        Drawable::Circle tileShape;
        tileShape.aspectRatio =  m_rect.height / m_rect.width;
        tileShape.radius = scaleY;
        tileShape.filled = true;
        tileShape.pointCount = 4;
        const ScreenPos center(m_rect.width/2, m_rect.height/2);

        const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette(50500).getColors();
        for (int col = 0; col < m_map->getCols(); col++) {
            for (int row = 0; row < m_map->getRows(); row++) {
                const VisibilityMap::Visibility visibility = m_visibilityMap->visibilityAt(col, row);
                if (visibility == VisibilityMap::Unexplored) {
                    continue;
                }

                const MapTile &tile = m_map->getTileAt(col, row);
                const genie::Terrain &terrain = DataManager::Inst().getTerrain(tile.terrainId);
                const genie::Color &color = colors[terrain.Colors[0]];
                if (visibility == VisibilityMap::Explored) {
                    tileShape.fillColor = Drawable::Color(color.r/2, color.g/2, color.b/2);
                } else {
                    tileShape.fillColor = Drawable::Color(color.r, color.g, color.b);
                }

                // WTF TODO FIXME why the fuck is flipping row and col the correct here..
                const ScreenPos pos = MapPos(row * scaleX, col * scaleY).toScreen();
                tileShape.center = ScreenPos(pos.x, pos.y + center.y - scaleY / 2);
                m_terrainTexture->draw(tileShape);

            }
        }

        m_terrainTexture->display();

        m_terrainUpdated = false;
    }

    if (m_unitsUpdated && m_unitManager) {
        TIME_THIS;

        if (!m_unitsTexture || m_unitsTexture->getSize() != m_rect.size()) {
            m_unitsTexture = m_renderTarget->createTextureTarget(m_rect.size());
        }
        m_unitsTexture->clear(Drawable::Transparent);


        const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());
        const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
        const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;

        const ScreenPos center(m_rect.width/2, m_rect.height/2);

        Drawable::Circle diamondSprite;
        diamondSprite.pointCount = 4;
        diamondSprite.radius = scaleY;
        diamondSprite.aspectRatio = m_rect.height / m_rect.width;
        diamondSprite.filled = true;

        Drawable::Rect rectangleSprite;
        rectangleSprite.filled = true;

        const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette(50500).getColors();

        for (const Unit::Ptr &unit : m_unitManager->units()) {
            const VisibilityMap::Visibility visibility = m_visibilityMap->visibilityAt(unit->position());
            if (visibility == VisibilityMap::Unexplored) {
                continue;
            }
            if (visibility == VisibilityMap::Explored && unit->playerId != UnitManager::GaiaID) {
                continue;
            }

            const genie::Unit::MinimapModes mode = genie::Unit::MinimapModes(unit->data()->MinimapMode);
            if (mode == genie::Unit::MinimapInvisible) {
                continue;
            }
            if (mode == genie::Unit::MinimapFlying) {
                continue;
            }

            if (mode != genie::Unit::MinimapUnit && mode != genie::Unit::MinimapBuilding && mode != genie::Unit::MinimapLargeTerrain) {
                DBG << "Unhandled minimap mode" << int(mode) << unit->data()->MinimapColor;
                continue;
            }

            const MapPos mapPos = unit->position();
            ScreenPos pos = MapPos(mapPos.y / Constants::TILE_SIZE, mapPos.x / Constants::TILE_SIZE - 1).toScreen();
            float size = std::max(unit->data()->OutlineSize.x * scaleX * 2, 2.f);
            pos.x = pos.x * scaleX - size/2;
            pos.y = pos.y * scaleY + center.y - size/2;

            // WARN: according to genieutils this is the inverted of what the game officially does,
            // but squares on the minimap look soooo ugly
            if (mode == genie::Unit::MinimapBuilding) {
                rectangleSprite.rect = ScreenRect(pos, Size(size, size));
                rectangleSprite.fillColor = unitColor(unit);
                m_unitsTexture->draw(rectangleSprite);
            } else if (mode == genie::Unit::MinimapUnit) {
                diamondSprite.fillColor = unitColor(unit);
                diamondSprite.center = pos;
                diamondSprite.radius = size;
                m_unitsTexture->draw(diamondSprite);
            } else if (mode == genie::Unit::MinimapLargeTerrain) {
                rectangleSprite.rect = ScreenRect(pos, Size(size, size));
                const genie::Color &color = colors[unit->data()->MinimapColor];
                rectangleSprite.fillColor = Drawable::Color(color.r, color.g, color.b);
                m_unitsTexture->draw(rectangleSprite);
            }
        }
        m_unitsTexture->display();
        m_unitsUpdated = false;
    }

    return true;
}

void Minimap::draw()
{
    m_renderTarget->draw(m_terrainTexture, m_rect.topLeft());
    m_renderTarget->draw(m_unitsTexture, m_rect.topLeft());

    if (m_rect.isEmpty()) {
        return;
    }

    const ScreenRect cameraRect = m_cameraRect.intersected(m_rect);
    if (cameraRect.isEmpty()) {
        return;
    }

    Drawable::Rect rect;
    rect.rect = ScreenRect(ScreenPos(cameraRect.x, cameraRect.y + 1), Size(cameraRect.size()));
    rect.fillColor = Drawable::Transparent;
    rect.filled = true;
    rect.borderSize = 1;

    rect.borderColor = Drawable::Black;
    m_renderTarget->draw(rect);

    rect.rect.setTopLeft(cameraRect.topLeft());
    rect.borderColor = Drawable::White;
    m_renderTarget->draw(rect);
}
