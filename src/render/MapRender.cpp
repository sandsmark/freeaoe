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


#include "MapRender.h"
#include <resource/ResourceManager.h>

namespace comp
{

MapRender::MapRender()
{

  x_offset_ = 200;
  y_offset_ = 0;
}

MapRender::~MapRender()
{

}

void MapRender::update(Time time)
{
    IComponent::update(time);
}

void MapRender::drawOn(GameRenderer& renderer)
{
  //TODO: very ugly code for testing purposes
  for (unsigned int col =0; col < map_->getCols(); col++)
  {
    for (unsigned int row = 0; row < map_->getRows(); row++)
    {
      res::TerrainPtr t = ResourceManager::Inst()->getTerrain(map_->getTileAt(col,row).terrain_id_);

      //TODO: MapPos to screenpos (Tile 0,0 is drawn at MapPos 0,0
      MapPos mpos(0,0,0);
      
      mpos.x += col*Map::TILE_SIZE;
      mpos.y += row*Map::TILE_SIZE;
      
      ScreenPos spos = mapToScreenPos(mpos);
      
      spos.x += x_offset_;
      spos.y += y_offset_;

      sf::Image img = t->getImage();
      
      renderer.draw(img, spos);
    }
  }
}

void MapRender::setMap(MapPtr map)
{
  map_ = map;
}



}
