#include "Minimap.h"
#include "mechanics/Map.h"
#include <functional>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "render/SfmlRenderTarget.h"
#include "resource/DataManager.h"
#include "global/Constants.h"
#include "mechanics/UnitManager.h"

Minimap::Minimap(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget),
//    m_rect(0, 0, 400, 200)
    m_rect(865, 815, 400, 200)
{

}

void Minimap::setMap(const std::shared_ptr<Map> &map)
{
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

}

void Minimap::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    if (!unitManager) {
        WARN << "null unit manager";
    }

    m_unitManager = unitManager;
    m_unitsUpdated = true;
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

sf::Color Minimap::unitColor(const std::shared_ptr<Unit> &unit)
{
    if (unit->selected) {
        return sf::Color::White;
    }

    switch(m_mode) {
    case MinimapMode::Normal:
        //TODO
        break;
    case MinimapMode::Diplomatic:
        if (unit->playerId == 0) {
            return sf::Color(128, 192, 128);
        } else if (unit->playerId == 1) { ///TODO fixme get the human player
            return sf::Color::Blue;
        } else {
            return sf::Color::Red;
        }
        break;
    case MinimapMode::Economic:
        //TODO
        break;
    default:
        break;
    }

    return sf::Color::Red;
}


bool Minimap::init()
{
    return m_terrainTexture.create(m_rect.width, m_rect.height);
}

void Minimap::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return;
    }

    ScreenPos pos(event.mouseButton.x, event.mouseButton.y);
    // normalize to 0,0
    pos.x -= m_rect.x;
    pos.y -= m_rect.y;

    pos.y = m_rect.height/2 - pos.y; // from the center

    const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());
    const ScreenRect fullBoundingRect = MapRect(0, 0, mapDimensions.width * Constants::TILE_SIZE, mapDimensions.height * Constants::TILE_SIZE).boundingScreenRect();
    pos.x = fullBoundingRect.width * pos.x / m_rect.width;
    pos.y = fullBoundingRect.height * pos.y / m_rect.height;

    m_renderTarget->camera()->setTargetPosition(pos.toMap());
}

bool Minimap::update(Time /*time*/)
{
    if (m_lastCameraPos != m_renderTarget->camera()->m_target) {
        updateCamera();
        m_lastCameraPos = m_renderTarget->camera()->m_target;
    }

    if (!m_map || (!m_unitsUpdated && !m_terrainUpdated)) {
        return false;
    }

    const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());

    if (m_terrainUpdated) {
        if (m_terrainTexture.getSize().x != m_rect.width || m_terrainTexture.getSize().y != m_rect.height) {
            m_terrainTexture.create(m_rect.width, m_rect.height);
        }

        m_terrainTexture.clear(sf::Color::Transparent);

        const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
        const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;

        sf::CircleShape background(m_rect.width/ 2, 4);
        background.setScale(1, m_rect.height / m_rect.width);
        background.setFillColor(sf::Color::Black);
        m_terrainTexture.draw(background);

        sf::CircleShape tileShape(scaleY, 4);
        tileShape.setScale(1, m_rect.height / m_rect.width);
        const ScreenPos center(m_rect.width/2, m_rect.height/2);

        const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette(50500).getColors();
        for (int col = 0; col < m_map->getCols(); col++) {
            for (int row = 0; row < m_map->getRows(); row++) {
                const MapTile &tile = m_map->getTileAt(col, row);
                const genie::Terrain &terrain = DataManager::Inst().getTerrain(tile.terrainId);
                const genie::Color &color = colors[terrain.Colors[0]];
                tileShape.setFillColor(sf::Color(color.r, color.g, color.b));

                // WTF TODO FIXME why the fuck is flipping row and col the correct here..
                const ScreenPos pos = MapPos(row * scaleX, col * scaleY).toScreen();
                tileShape.setPosition(pos.x, pos.y + center.y - scaleY / 2);
                m_terrainTexture.draw(tileShape);

            }
        }

        m_terrainTexture.display();

        m_terrainUpdated = false;
    }

    if (m_unitsUpdated && m_unitManager) {
        TIME_THIS;

        if (m_unitsTexture.getSize().x != m_rect.width || m_unitsTexture.getSize().y != m_rect.height) {
            m_unitsTexture.create(m_rect.width, m_rect.height);
        }

        m_unitsTexture.clear(sf::Color::Transparent);


        const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());
        const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
        const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;

        const ScreenPos center(m_rect.width/2, m_rect.height/2);

        sf::CircleShape diamondSprite(scaleY, 4);
        diamondSprite.setScale(1, m_rect.height / m_rect.width);

        sf::RectangleShape rectangleSprite;

        const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette(50500).getColors();

        for (const Unit::Ptr &unit : m_unitManager->units()) {
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

            if (mode == genie::Unit::MinimapBuilding) {
                diamondSprite.setFillColor(unitColor(unit));
                diamondSprite.setPosition(pos);
                diamondSprite.setRadius(size);
                m_unitsTexture.draw(diamondSprite);
            } else if (mode == genie::Unit::MinimapUnit) {
                rectangleSprite.setSize(sf::Vector2f(size, size));
                rectangleSprite.setPosition(pos);
                rectangleSprite.setFillColor(unitColor(unit));
                m_unitsTexture.draw(rectangleSprite);
            } else if (mode == genie::Unit::MinimapLargeTerrain) {
                rectangleSprite.setSize(sf::Vector2f(size, size));
                rectangleSprite.setPosition(pos);
                const genie::Color &color = colors[unit->data()->MinimapColor];
                rectangleSprite.setFillColor(sf::Color(color.r, color.g, color.b));
                m_unitsTexture.draw(rectangleSprite);
            }
        }
        m_unitsTexture.display();
        m_unitsUpdated = false;
    }

    return true;
}

void Minimap::draw()
{
    m_renderTarget->draw(m_terrainTexture.getTexture(), m_rect.topLeft());
    m_renderTarget->draw(m_unitsTexture.getTexture(), m_rect.topLeft());

    const ScreenRect cameraRect = m_cameraRect.intersected(m_rect);

    sf::RectangleShape rect;
    rect.setSize(cameraRect.size());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);

    rect.setOutlineColor(sf::Color::Black);
    rect.setPosition(cameraRect.x, cameraRect.y + 1);
    m_renderTarget->draw(rect);

    rect.setPosition(cameraRect.topLeft());
    rect.setOutlineColor(sf::Color::White);
    m_renderTarget->draw(rect);
}
