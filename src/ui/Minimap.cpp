#include "Minimap.h"
#include "mechanics/Map.h"
#include <functional>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "render/SfmlRenderTarget.h"
#include "resource/DataManager.h"
#include "global/Constants.h"

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

    m_updated = true;

    updateCamera();

}

void Minimap::updateUnits()
{
    m_updated = true;
}

void Minimap::updateTerrain()
{
    m_updated = true;
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


bool Minimap::init()
{
    return m_texture.create(m_rect.width, m_rect.height);
}

void Minimap::handleEvent(sf::Event /*event*/)
{
}

bool Minimap::update(Time /*time*/)
{
    if (m_lastCameraPos != m_renderTarget->camera()->m_target) {
        updateCamera();
        m_lastCameraPos = m_renderTarget->camera()->m_target;
    }

    if (!m_updated || !m_map) {
        return false;
    }
    if (m_texture.getSize().x != m_rect.width || m_texture.getSize().y != m_rect.height) {
        m_texture.create(m_rect.width, m_rect.height);
    }

    m_texture.clear(sf::Color::Transparent);

    sf::CircleShape background(m_rect.width/ 2, 4);
    background.setScale(1, m_rect.height / m_rect.width);
    background.setFillColor(sf::Color::Black);
    m_texture.draw(background);

    const MapRect mapDimensions(0, 0, m_map->getCols(), m_map->getRows());
    const float scaleX = m_rect.boundingMapRect().width / mapDimensions.width / 2;
    const float scaleY = m_rect.boundingMapRect().height / mapDimensions.height / 2;
    sf::CircleShape tileShape(scaleY, 4);
    tileShape.setScale(1, m_rect.height / m_rect.width);
    const ScreenPos center(m_rect.width/2, m_rect.height/2);
    for (int col = 0; col < m_map->getCols(); col++) {
        for (int row = 0; row < m_map->getRows(); row++) {
            const MapTile &tile = m_map->getTileAt(col, row);
            const genie::Terrain &terrain = DataManager::Inst().getTerrain(tile.terrainId);
            tileShape.setFillColor(sf::Color(terrain.Colors[0], terrain.Colors[1], terrain.Colors[2]));

            // WTF TODO FIXME why the fuck is flipping row and col the correct here..
            const ScreenPos pos = MapPos(row * scaleX, col * scaleY).toScreen();
            tileShape.setPosition(pos.x, pos.y + center.y - scaleY / 2);
            m_texture.draw(tileShape);

        }
    }


    m_updated = false;

    m_texture.display();
    return true;
}

void Minimap::draw()
{
    m_renderTarget->draw(m_texture.getTexture(), m_rect.topLeft());

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
