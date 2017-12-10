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
#include <resource/ResourceManager.h>
#include <SFML/Graphics/Sprite.hpp>

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

    const MapPos cameraPos = renderTarget_->camera()->getTargetPosition();

    if (!m_camChanged && m_lastCameraPos == cameraPos) { // check for camera change
        return false;
    }

    //TODO: split up (refactor)

    // Get the absolute map positions of the rendertarget corners
    ScreenPos camCenter;
    camCenter.x = renderTarget_->getSize().x / 2.0;
    camCenter.y = renderTarget_->getSize().y / 2.0;

    // relative map positions (from center) //only changes if renderTargets resolution does
    MapPos nullCenterMp = camCenter.toMap();
    //     MapPos nulltopLeftMp = screenToMapPos(ScreenPos(0,0));
    MapPos nullbotLeftMp = ScreenPos(0, renderTarget_->getSize().y).toMap();
    MapPos nullTopRightMp = ScreenPos(renderTarget_->getSize().x, 0).toMap();
    MapPos nullBotRightMp = ScreenPos(renderTarget_->getSize().x, renderTarget_->getSize().y).toMap();

    // absolute map positions
    MapPos topLeftMp = cameraPos - nullCenterMp;
    MapPos botRightMp = cameraPos + (nullBotRightMp - nullCenterMp);

    MapPos topRightMp = cameraPos + (nullTopRightMp - nullCenterMp);
    MapPos botLeftMp = cameraPos + (nullbotLeftMp - nullCenterMp);

//    std::cout << "nulC " << nullCenterMp.x << " " << nullCenterMp.y << std::endl;
//    std::cout << "topLeftMp " << topLeftMp.x << " " << topLeftMp.y << std::endl;
//    std::cout << "botRightMp " << botRightMp.x << " " << botRightMp.y << std::endl;

    // get column and row boundaries for rendering
    m_rColBegin = botLeftMp.x / Map::TILE_SIZE; //int = round down //TODO Platform independent?

    if (m_rColBegin < 0)
        m_rColBegin = 0;
    if (m_rColBegin > m_map->getCols()) {
        m_rColBegin = m_map->getCols();
        std::cout << "E: Somethings fishy... (rColBegin_ > map_->getCols())" << std::endl;
    }

    m_rColEnd = topRightMp.x / Map::TILE_SIZE;
    m_rColEnd++; //round up

    if (m_rColEnd < 0) {
        m_rColEnd = 0;
        std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    if (m_rColEnd > m_map->getCols())
        m_rColEnd = m_map->getCols();

    m_rRowBegin = topLeftMp.y / Map::TILE_SIZE;

    if (m_rRowBegin < 0)
        m_rRowBegin = 0;
    if (m_rRowBegin > m_map->getRows()) {
        std::cout << "E: Somethings fishy... (rRowBegin > map_->getRows())" << std::endl;
        m_rRowBegin = m_map->getRows();
    }

    m_rRowEnd = botRightMp.y / Map::TILE_SIZE;
    m_rRowEnd++; // round up

    if (m_rRowEnd < 0) {
        m_rRowEnd = 0;
        std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    if (m_rRowEnd > m_map->getRows())
        m_rRowEnd = m_map->getRows();

    // Calculating screen offset to MapPos(rColBegin, rColEnd):

    MapPos offsetMp;
    offsetMp.x = m_rColBegin * Map::TILE_SIZE;
    offsetMp.y = m_rRowBegin * Map::TILE_SIZE;
    offsetMp.z = 0;

    ScreenPos offsetSp = (offsetMp - topLeftMp).toScreen();

//    std::cout << "\nrColBegin: " << m_rColBegin << std::endl;
//    std::cout << "rColEnd: " << m_rColEnd << std::endl;
//    std::cout << "rRowEnd: " << m_rRowEnd << std::endl;

//    std::cout << "\noffsetMp = " << offsetMp.x << " " << offsetMp.y << std::endl;
//    std::cout << "offsetSp = " << offsetSp.x << " " << offsetSp.y << std::endl;

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
}

MapPos MapRenderer::getMapPosition(ScreenPos pos)
{
    ScreenPos camCenter;
    camCenter.x = renderTarget_->getSize().x / 2.0;
    camCenter.y = renderTarget_->getSize().y / 2.0;

    pos.y = renderTarget_->getSize().y - pos.y;

    // relative map positions (from center)
    MapPos nullCenterMp = camCenter.toMap();

    MapPos nullPos = pos.toMap();

    MapPos relPos;
    relPos.x = nullPos.x - nullCenterMp.x;
    relPos.y = nullPos.y - nullCenterMp.y;

    MapPos absMapPos = renderTarget_->camera()->getTargetPosition() + relPos;//(nullPos - nullCenterMp);

    return absMapPos;
}

void MapRenderer::updateTexture()
{
    if (m_mapRenderTexture.getSize().x != renderTarget_->getSize().x || m_mapRenderTexture.getSize().y != renderTarget_->getSize().y) {
        m_mapRenderTexture.create(renderTarget_->getSize().x, renderTarget_->getSize().y, false);
    }

    m_mapRenderTexture.clear();

    if (!m_mapRenderTexture.getSize().x || !m_mapRenderTexture.getSize().y) {
        return;
    }

    for (unsigned int col = m_rColBegin; col < m_rColEnd; col++) {
        for (unsigned int row = m_rRowBegin; row < m_rRowEnd; row++) {
            res::TerrainPtr t = ResourceManager::Inst()->getTerrain(m_map->getTileAt(col, row).terrain_id_);

            //TODO: MapPos to screenpos (Tile 0,0 is drawn at MapPos 0,0
            MapPos mpos(0, 0, 0);

            mpos.x += (col - m_rColBegin) * Map::TILE_SIZE;
            mpos.y += (row - m_rRowBegin) * Map::TILE_SIZE;

            ScreenPos spos = mpos.toScreen();

            spos.x += m_xOffset;
            spos.y += m_yOffset;

            spos.y -= Map::TILE_SIZE_VERTICAL / 2;

            m_textureTarget.draw(t->image(col, row), spos);
        }
    }
}
