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

MapRenderer::MapRenderer()
{

    //   xOffset_ = 400;//-1200;
    //   yOffset_ = 300;//-1500;

    xOffset_ = 0; //-1200;
    yOffset_ = 0; //-1500;

    camChanged_ = false;

    rColBegin_ = rColEnd_ = rRowBegin_ = rRowEnd_ = 0;
}

MapRenderer::~MapRenderer()
{
}

void MapRenderer::update(Time time)
{
    if (camChanged_ == false && lastCameraPos_ != camera_->getTargetPosition()) // check for camera change
        camChanged_ = true;

    if (map_.get() != 0 && camChanged_) //TODO: split up (refactor)
    {
        MapPos cameraPos = camera_->getTargetPosition();

        // Get the absolute map positions of the rendertarget corners
        ScreenPos camCenter;
        camCenter.x = renderTarget_->getSize().x / 2.0;
        camCenter.y = renderTarget_->getSize().y / 2.0;

        // relative map positions (from center) //only changes if renderTargets resolution does
        MapPos nullCenterMp = screenToMapPos(camCenter);
        //     MapPos nulltopLeftMp = screenToMapPos(ScreenPos(0,0));
        MapPos nullbotLeftMp = screenToMapPos(ScreenPos(0, renderTarget_->getSize().y));
        MapPos nullTopRightMp = screenToMapPos(ScreenPos(renderTarget_->getSize().x, 0));
        MapPos nullBotRightMp = screenToMapPos(ScreenPos(renderTarget_->getSize().x, renderTarget_->getSize().y));

        // absolute map positions
        MapPos topLeftMp = cameraPos - nullCenterMp;
        MapPos botRightMp = cameraPos + (nullBotRightMp - nullCenterMp);

        MapPos topRightMp = cameraPos + (nullTopRightMp - nullCenterMp);
        MapPos botLeftMp = cameraPos + (nullbotLeftMp - nullCenterMp);

        std::cout << "nulC " << nullCenterMp.x << " " << nullCenterMp.y << std::endl;
        std::cout << "topLeftMp " << topLeftMp.x << " " << topLeftMp.y << std::endl;
        std::cout << "botRightMp " << botRightMp.x << " " << botRightMp.y << std::endl;

        // get column and row boundaries for rendering
        rColBegin_ = botLeftMp.x / Map::TILE_SIZE; //int = round down //TODO Platform independent?

        if (rColBegin_ < 0)
            rColBegin_ = 0;
        if (rColBegin_ > map_->getCols()) {
            rColBegin_ = map_->getCols();
            std::cout << "E: Somethings fishy... (rColBegin_ > map_->getCols())" << std::endl;
        }

        rColEnd_ = topRightMp.x / Map::TILE_SIZE;
        rColEnd_++; //round up

        if (rColEnd_ < 0) {
            rColEnd_ = 0;
            std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
        }
        if (rColEnd_ > map_->getCols())
            rColEnd_ = map_->getCols();

        rRowBegin_ = topLeftMp.y / Map::TILE_SIZE;

        if (rRowBegin_ < 0)
            rRowBegin_ = 0;
        if (rRowBegin_ > map_->getRows()) {
            std::cout << "E: Somethings fishy... (rRowBegin > map_->getRows())" << std::endl;
            rRowBegin_ = map_->getRows();
        }

        rRowEnd_ = botRightMp.y / Map::TILE_SIZE;
        rRowEnd_++; // round up

        if (rRowEnd_ < 0) {
            rRowEnd_ = 0;
            std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
        }
        if (rRowEnd_ > map_->getRows())
            rRowEnd_ = map_->getRows();

        // Calculating screen offset to MapPos(rColBegin, rColEnd):

        MapPos offsetMp;
        offsetMp.x = rColBegin_ * Map::TILE_SIZE;
        offsetMp.y = rRowBegin_ * Map::TILE_SIZE;
        offsetMp.z = 0;

        ScreenPos offsetSp = mapToScreenPos(offsetMp - topLeftMp);

        std::cout << "\nrColBegin: " << rColBegin_ << std::endl;
        std::cout << "rColEnd: " << rColEnd_ << std::endl;
        std::cout << "rRowEnd: " << rRowEnd_ << std::endl;

        std::cout << "\noffsetMp = " << offsetMp.x << " " << offsetMp.y << std::endl;
        std::cout << "offsetSp = " << offsetSp.x << " " << offsetSp.y << std::endl;

        xOffset_ = offsetSp.x;
        yOffset_ = offsetSp.y;

        lastCameraPos_ = camera_->getTargetPosition();
        camChanged_ = false;
    }
}

void MapRenderer::display(void)
{
    //TODO: change to RenderTexture if it's working correctly
    for (unsigned int col = rColBegin_; col < rColEnd_; col++) {
        for (unsigned int row = rRowBegin_; row < rRowEnd_; row++) {
            res::TerrainPtr t = ResourceManager::Inst()->getTerrain(map_->getTileAt(col, row).terrain_id_);

            //TODO: MapPos to screenpos (Tile 0,0 is drawn at MapPos 0,0
            MapPos mpos(0, 0, 0);

            mpos.x += (col - rColBegin_) * Map::TILE_SIZE;
            mpos.y += (row - rRowBegin_) * Map::TILE_SIZE;

            ScreenPos spos = mapToScreenPos(mpos);

            spos.x += xOffset_;
            spos.y += yOffset_;

            spos.y -= Map::TILE_SIZE_VERTICAL / 2;

            sf::Image img = t->image(col, row);

            renderTarget_->draw(img, spos);
        }
    }
}

void MapRenderer::setMap(MapPtr map)
{
    map_ = map;

    rRowBegin_ = rColBegin_ = 0;
    rRowEnd_ = map_->getRows();
    rColEnd_ = map_->getCols();
}

MapPos MapRenderer::getMapPosition(ScreenPos pos)
{
    ScreenPos camCenter;
    camCenter.x = renderTarget_->getSize().x / 2.0;
    camCenter.y = renderTarget_->getSize().y / 2.0;

    // relative map positions (from center)
    MapPos nullCenterMp = screenToMapPos(camCenter);

    MapPos nullPos = screenToMapPos(pos);

    MapPos absMapPos = camera_->getTargetPosition() + (nullPos - nullCenterMp);

    return absMapPos;
}

void MapRenderer::setCamera(CameraPtr camera)
{
    camera_ = camera;
    camChanged_ = true;
}
