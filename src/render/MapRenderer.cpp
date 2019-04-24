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
#include "core/Constants.h"
#include "mechanics/Player.h" // for visibilitymap
#include <resource/AssetManager.h>
#include <resource/DataManager.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <mechanics/MapTile.h>

MapRenderer::MapRenderer() :
    m_camChanged(true),
    m_xOffset(0),
    m_yOffset(0),
    m_rRowBegin(0),
    m_rRowEnd(0),
    m_rColBegin(0),
    m_rColEnd(0),
    m_textureTarget(m_mapRenderTexture),
    m_elevationHeight(DataManager::Inst().terrainBlock().ElevHeight)
{
}

MapRenderer::~MapRenderer()
{
}

bool MapRenderer::update(Time /*time*/)
{
    if (!m_map) {
        return false;
    }

    const MapPos cameraPos = renderTarget_->camera()->targetPosition();

    if (!m_camChanged && m_lastCameraPos == cameraPos &&
        Size(m_mapRenderTexture.getSize()) == renderTarget_->getSize() &&
        !m_map->tilesUpdated()) {
        return false;
    }

    // Get the absolute map positions of the rendertarget corners
    const ScreenPos camCenter(renderTarget_->getSize().width / 2.0, renderTarget_->getSize().height / 2.0);

    // relative map positions (from center) //only changes if renderTargets resolution does
    const MapPos center = camCenter.toMap();
    const MapPos bottomLeft = ScreenPos(0, renderTarget_->getSize().height).toMap();
    const MapPos topRight = ScreenPos(renderTarget_->getSize().width, 0).toMap();
    const MapPos bottomRight = ScreenPos(renderTarget_->getSize().width, renderTarget_->getSize().height).toMap();

    // absolute map positions
    MapPos topLeftMp = cameraPos - center;
    MapPos botRightMp = cameraPos + (bottomRight - center);

    MapPos topRightMp = cameraPos + (topRight - center);
    MapPos botLeftMp = cameraPos + (bottomLeft - center);

    // get column and row boundaries for rendering
    m_rColBegin = botLeftMp.x / Constants::TILE_SIZE;
    if (m_rColBegin > m_map->getCols()) {
        WARN << "E: Somethings fishy... (rColBegin_ > map_->getCols())";
    }
    m_rColBegin = std::clamp(m_rColBegin, 0, m_map->getCols());

    m_rColEnd = topRightMp.x / Constants::TILE_SIZE;
    m_rColEnd++; //round up
    if (m_rColEnd < 0) {
        WARN << "E: Somethings fishy... (rColEnd_ < 0)";
    }
    m_rColEnd = std::clamp(m_rColEnd, 0, m_map->getCols());

    m_rRowBegin = topLeftMp.y / Constants::TILE_SIZE;
    if (m_rRowBegin > m_map->getRows()) {
        WARN << "E: Somethings fishy... (rRowBegin > map_->getRows())";
    }
    m_rRowBegin = std::clamp(m_rRowBegin, 0, m_map->getRows());

    m_rRowEnd = botRightMp.y / Constants::TILE_SIZE;
    m_rRowEnd++; // round up
    if (m_rRowEnd < 0) {
        WARN << "E: Somethings fishy... (rColEnd_ < 0)";
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

    m_map->flushDirty();

    return true;
}

void MapRenderer::display()
{
    if (IS_UNLIKELY(!m_visibilityMap)) {
        WARN << "no visibility map set";
        return;
    }

    if (Size(m_mapRenderTexture.getSize()) != renderTarget_->getSize() || m_visibilityMap->isDirty) {
        m_visibilityMap->isDirty = false;

        updateTexture();
    }

    renderTarget_->draw(m_mapRenderTexture.getTexture(), ScreenPos(0, 0));
}

void MapRenderer::setMap(const MapPtr &map)
{
    m_map = map;

    m_rRowBegin = m_rColBegin = 0;
    m_rRowEnd = m_map->getRows();
    m_rColEnd = m_map->getCols();

    m_camChanged = true;
}

void MapRenderer::updateTexture()
{
    if (IS_UNLIKELY(!m_visibilityMap)) {
        WARN << "no visibility map set";
        return;
    }

    if (m_mapRenderTexture.getSize().x != renderTarget_->getSize().width || m_mapRenderTexture.getSize().y != renderTarget_->getSize().height) {
        m_mapRenderTexture.create(renderTarget_->getSize().width, renderTarget_->getSize().height);
    }

    m_mapRenderTexture.clear();

    if (!m_mapRenderTexture.getSize().x || !m_mapRenderTexture.getSize().y) {
        return;
    }

    sf::CircleShape invalidIndicator(Constants::TILE_SIZE, 4);
    invalidIndicator.setScale(1, 0.5);
    invalidIndicator.setFillColor(sf::Color::Red);
    invalidIndicator.setOutlineThickness(3);
    invalidIndicator.setOutlineColor(sf::Color::Transparent);

//    sf::Text text;
//    text.setFont(SfmlRenderTarget::defaultFont());
//    text.setOutlineColor(sf::Color::Transparent);
//    text.setFillColor(sf::Color::White);
//    text.setCharacterSize(12);

    for (int col = m_rColBegin; col < m_rColEnd; col++) {
        for (int row = m_rRowEnd-1; row >= m_rRowBegin; row--) {
            const VisibilityMap::Visibility visibility = m_visibilityMap->visibilityAt(col, row);
            if (visibility == VisibilityMap::Unexplored) {
                continue;
            }

            MapTile &mapTile = m_map->getTileAt(col, row);

            MapRect rect;
            rect.x = col * Constants::TILE_SIZE;
            rect.y = row * Constants::TILE_SIZE;
            rect.z = mapTile.elevation * m_elevationHeight;
            rect.width = Constants::TILE_SIZE;
            rect.height = Constants::TILE_SIZE;

            // col and row are in map coordinates, so the top corners when rotated 45° we don't need to draw
//            if (!renderTarget_->camera()->isVisible(rect)) {
//                continue;
//            }

            ScreenPos spos = renderTarget_->camera()->absoluteScreenPos(rect.topLeft());

            // If we wanted to do this 100% correctly, we would need to use the hotspot from the
            // filtered SLP and then always offset with yOffset, but this is good enough for now.
            spos.y -= Constants::TILE_SIZE_VERTICAL / 2;
            if (mapTile.yOffset > 0) {
                spos.y -= mapTile.yOffset * 2;
            }


            TerrainPtr terrain = AssetManager::Inst()->getTerrain(mapTile.terrainId);

            if (!terrain) {
                invalidIndicator.setPosition(spos);
                m_textureTarget.draw(invalidIndicator);
                continue;
            }

            m_textureTarget.draw(terrain->texture(mapTile), spos);

            // TODO actually load the blkedge and tileedge
            if (m_visibilityMap->visibilityAt(col, row) == VisibilityMap::Explored) {
                m_textureTarget.draw(shadowMask(mapTile.slopes.self.toGenie(), 0), spos);
//                noVisionindicator.setPosition(spos);
//                m_textureTarget.draw(noVisionindicator);
            } else {
                m_textureTarget.draw(shadowMask(mapTile.slopes.self.toGenie(), m_visibilityMap->edgeShadowTile(col, row) * 2 + 1), spos);
            }

//            text.setString(std::to_string(col) + "," + std::to_string(row));
//            text.setPosition(spos.x, spos.y);
//            m_textureTarget.draw(text);
        }
    }

    m_mapRenderTexture.display();
}

const sf::Texture &MapRenderer::shadowMask(const genie::Slope slope, const int edges)
{
    const int cacheIndex = slope * 256 + edges;

    // the STL APIs are a steaming pile of shit: TODO replace them (or just start using Qt)
    // This is "slow", but the alternative is to use an iterator and get a full copy of the texture instead of just a ref
    if (m_shadowCaches.find(cacheIndex) != m_shadowCaches.end()) {
        return m_shadowCaches[cacheIndex];
    }

    const genie::VisibilityMask &mask = AssetManager::Inst()->unexploredVisibilityMask(slope, edges);
    const int width = 96;
    const int height = 96;
    std::vector<uint32_t> pixelsBuf(width * height);

    for (const genie::TileSpan &span : mask.lines) {
        if (IS_UNLIKELY(span.xEnd < span.xStart)) {
            WARN << "bad span" << span.xStart << "to" << span.xEnd;
            continue;
        }
        if (IS_UNLIKELY(width < span.xEnd)) {
            WARN << "bad span" << span.xStart << "to" << span.xEnd;
            continue;
        }
        if (IS_UNLIKELY(height < span.y)) {
            WARN << "bad span" << span.xStart << "to" << span.xEnd;
            continue;
        }
        int count = span.xEnd - span.xStart;
        int offset = span.y * width + span.xStart;
        std::fill_n(pixelsBuf.begin() + offset, count, 0x7f000000);
    }
    sf::Image image;
    image.create(width, height, reinterpret_cast<uint8_t*>(pixelsBuf.data()));
    m_shadowCaches[cacheIndex].loadFromImage(image);

    return m_shadowCaches[cacheIndex];
}
