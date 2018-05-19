/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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

#include "MapRenderer.h"
#include "IRenderTarget.h"
#include "global/Constants.h"
#include <resource/ResourceManager.h>
#include <resource/DataManager.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

MapRenderer::MapRenderer() :
    m_camChanged(true),
    m_xOffset(0),
    m_yOffset(0),
    m_rRowBegin(0),
    m_rRowEnd(0),
    m_rColBegin(0),
    m_rColEnd(0),
    m_textureTarget(m_mapRenderTexture)
{
}

MapRenderer::~MapRenderer()
{
}

bool MapRenderer::update(Time time)
{
    if (!m_map) {
        return false;
    }

    const MapPos cameraPos = renderTarget_->camera()->targetPosition();

    if (!m_camChanged && m_lastCameraPos == cameraPos &&
        m_mapRenderTexture.getSize() == renderTarget_->getSize()) {
        return false;
    }

    //TODO: split up (refactor)

//     Get the absolute map positions of the rendertarget corners
    const ScreenPos camCenter(renderTarget_->getSize().x / 2.0, renderTarget_->getSize().y / 2.0);

    // relative map positions (from center) //only changes if renderTargets resolution does
    const MapPos center = camCenter.toMap();
    const MapPos bottomLeft = ScreenPos(0, renderTarget_->getSize().y).toMap();
    const MapPos topRight = ScreenPos(renderTarget_->getSize().x, 0).toMap();
    const MapPos bottomRight = ScreenPos(renderTarget_->getSize().x, renderTarget_->getSize().y).toMap();

    // absolute map positions
    MapPos topLeftMp = cameraPos - center;
    MapPos botRightMp = cameraPos + (bottomRight - center);

    MapPos topRightMp = cameraPos + (topRight - center);
    MapPos botLeftMp = cameraPos + (bottomLeft - center);

//    std::cout << "nulC " << nullCenterMp.x << " " << nullCenterMp.y << std::endl;
//    std::cout << "topLeftMp " << topLeftMp.x << " " << topLeftMp.y << std::endl;
//    std::cout << "botRightMp " << botRightMp.x << " " << botRightMp.y << std::endl;

    // get column and row boundaries for rendering
    m_rColBegin = botLeftMp.x / Constants::TILE_SIZE;
    if (m_rColBegin > m_map->getCols()) {
        std::cout << "E: Somethings fishy... (rColBegin_ > map_->getCols())" << std::endl;
    }
    m_rColBegin = std::clamp(m_rColBegin, 0, m_map->getCols());

    m_rColEnd = topRightMp.x / Constants::TILE_SIZE;
    m_rColEnd++; //round up
    if (m_rColEnd < 0) {
        std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    m_rColEnd = std::clamp(m_rColEnd, 0, m_map->getCols());

    m_rRowBegin = topLeftMp.y / Constants::TILE_SIZE;
    if (m_rRowBegin > m_map->getRows()) {
        std::cout << "E: Somethings fishy... (rRowBegin > map_->getRows())" << std::endl;
    }
    m_rRowBegin = std::clamp(m_rRowBegin, 0, m_map->getRows());

    m_rRowEnd = botRightMp.y / Constants::TILE_SIZE;
    m_rRowEnd++; // round up
    if (m_rRowEnd < 0) {
        std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    m_rRowEnd = std::clamp(m_rRowEnd, 0, m_map->getRows());

    // Calculating screen offset to MapPos(rColBegin, rColEnd):
    const MapPos offsetMp(m_rColBegin * Constants::TILE_SIZE, m_rRowBegin * Constants::TILE_SIZE);
    ScreenPos offsetSp = (offsetMp - topLeftMp).toScreen();

    m_xOffset = offsetSp.x;
    m_yOffset = offsetSp.y;

    m_lastCameraPos = cameraPos;
    m_camChanged = false;

    updateTexture();

    return true;
}

void MapRenderer::display(void)
{
    if (m_mapRenderTexture.getSize() != renderTarget_->getSize()) {
        updateTexture();
    }

    renderTarget_->draw(m_mapRenderTexture.getTexture(), ScreenPos(0, 0));
}

void MapRenderer::setMap(MapPtr map)
{
    m_map = map;

    m_rRowBegin = m_rColBegin = 0;
    m_rRowEnd = m_map->getRows();
    m_rColEnd = m_map->getCols();

    m_camChanged = true;
}

void MapRenderer::updateTexture()
{
    if (m_mapRenderTexture.getSize().x != renderTarget_->getSize().x || m_mapRenderTexture.getSize().y != renderTarget_->getSize().y) {
        m_mapRenderTexture.create(renderTarget_->getSize().x, renderTarget_->getSize().y);
    }

    m_mapRenderTexture.clear();

    if (!m_mapRenderTexture.getSize().x || !m_mapRenderTexture.getSize().y) {
        return;
    }

    sf::CircleShape outline(Constants::TILE_SIZE, 4);
    outline.setScale(1, 0.5);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(3);
    outline.setOutlineColor(sf::Color(255, 255, 255, 64));

//    for (int col = m_rColEnd-1; col >= 0; col--) {
    for (int col = 0; col < m_rColEnd; col++) {
        for (int row = m_rRowEnd-1; row >= 0; row--) {
            MapTile &mapTile = m_map->getTileAt(col, row);

            //TODO: MapPos to screenpos (Tile 0,0 is drawn at MapPos 0,0
            MapRect rect;
            rect.x = col * Constants::TILE_SIZE;
            rect.y = row * Constants::TILE_SIZE;
            rect.z = mapTile.z;
            rect.width = Constants::TILE_SIZE;
            rect.height = Constants::TILE_SIZE;

            // col and row are in map coordinates, so the top corners when rotated 45° we don't need to draw
            if (!renderTarget_->camera()->isVisible(rect)) {
                continue;
            }

//            rect.x -= m_rColBegin * Constants::TILE_SIZE;
//            rect.y -= m_rRowBegin * Constants::TILE_SIZE;
            ScreenPos spos = renderTarget_->camera()->absoluteScreenPos(rect.topLeft());
//            ScreenPos spos = rect.topLeft().toScreen();
//            spos.x += m_xOffset;
//            spos.y += m_yOffset;
            spos.y -= Constants::TILE_SIZE_VERTICAL / 2;

            if (!mapTile.terrain_) {
                sf::RectangleShape rect;
                rect.setFillColor(sf::Color(255, 0, 0, 32));
                rect.setPosition(spos);
                rect.setSize(sf::Vector2f(Constants::TILE_SIZE_HORIZONTAL, Constants::TILE_SIZE_VERTICAL));
                m_textureTarget.draw(rect);
                continue;
            }


            if (mapTile.slopes.self == res::TileSlopes::Flat) {
                m_textureTarget.draw(mapTile.terrain_->texture(col, row), spos);

                for (const res::Blend b : mapTile.blends) {
                    m_textureTarget.draw(b.terrain->blendImage(b, col, row), spos);
                }
            } else {
                m_textureTarget.draw(mapTile.terrain_->slopedImage(mapTile.slopes, col, row), spos);
            }

            outline.setPosition(spos.x, spos.y);
//            m_textureTarget.draw(outline);
        }
    }

    m_mapRenderTexture.display();
}
