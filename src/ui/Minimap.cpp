#include "Minimap.h"
#include "mechanics/Map.h"
#include <functional>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "render/SfmlRenderTarget.h"
#include "resource/DataManager.h"

Minimap::Minimap(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget),
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

}

void Minimap::updateUnits()
{
    m_updated = true;
}

void Minimap::updateTerrain()
{
    m_updated = true;
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
    if (/*!m_updated ||*/ !m_map) {
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

//    const float tileWidth = m_rect.width / m_map->getCols();
//    const float tileHeight = m_rect.height / m_map->getRows();
    const MapRect mapRect(0, 0, m_map->getCols(), m_map->getRows());
    const ScreenRect mapScreenRect = mapRect.toScreen();
    const float scaleX = m_rect.width / mapScreenRect.width/2;
    const float scaleY = m_rect.height / mapScreenRect.height/2;
    sf::RectangleShape rect(sf::Vector2f(scaleX, scaleY));
//    sf::RectangleShape rect(mapRect.size());
//    const std::vector<genie::Color> &colors = AssetManager::Inst()->getPalette().colors_;
//    DBG << tileWidth << tileHeight << rect.getSize().x << rect.getSize().y;
    const ScreenPos center(m_rect.width/2, m_rect.height/2);
    const MapPos mapCenter(mapRect.center());
    DBG << scaleX << scaleY;
    for (int col = 0; col < m_map->getCols(); col++) {
        for (int row = 0; row < m_map->getRows(); row++) {
            const MapTile &tile = m_map->getTileAt(col, row);
            const genie::Terrain &terrain = DataManager::Inst().getTerrain(tile.terrainId);
            rect.setFillColor(sf::Color(terrain.Colors[0], terrain.Colors[1], terrain.Colors[2]));

            const ScreenPos pos = MapPos(mapCenter.x - col * 10, mapCenter.y - row * 10).toScreen();
            rect.setPosition(- pos.x, center.y + pos.y);
            m_texture.draw(rect);

        }
    }
    m_texture.display();
    Size viewSize = m_renderTarget->camera()->m_viewportSize;
    rect.setSize(Size(viewSize.width / m_rect.width, viewSize.height / m_rect.height));
    ScreenPos cameraPos = m_renderTarget->camera()->m_target.toScreen();
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1);
    rect.setPosition(ScreenPos(cameraPos.x * (m_rect.width / viewSize.width), cameraPos.y * (m_rect.height / viewSize.height)));
//    DBG << rect.getSize() << rect.getPosition() << viewSize << scaleX << scaleY << cameraPos;
    m_texture.draw(rect);

    m_updated = false;
    return true;
}

void Minimap::draw()
{
    m_renderTarget->draw(m_texture.getTexture(), m_rect.topLeft());
}
