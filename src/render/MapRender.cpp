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
#include "IRenderTarget.h"
#include <resource/ResourceManager.h>
#include <SFML/Graphics/Sprite.hpp>

namespace comp
{

MapRender::MapRender()
{

  xOffset_ = 0;//-1200;
  yOffset_ = 0;//-1500;
}

MapRender::~MapRender()
{

}

void MapRender::update(Time time)
{
    IComponent::update(time);
}

void MapRender::drawOn(IRenderTarget& renderer)
{
  /*
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
      
      spos.x += xOffset_;
      spos.y += yOffset_;

      sf::Image img = t->getImage();
      
      renderer.draw(img, spos);
    }
  } 
  
  */
  ScreenPos pos(xOffset_, yOffset_);
  
//   renderer.draw(mapImage_, pos);
  renderer.draw(mapTexture_.getTexture(), pos);
  
  
}

void MapRender::setMap(MapPtr map)
{
  map_ = map;
  
  //ARrg TODO Pls change before commit :(
//   MapPos h(map_->getCols()*Map::TILE_SIZE, map_->getRows() * Map::TILE_SIZE, 0);
//   MapPos w((map_->getCols() + 1) * Map::TILE_SIZE, 0, 0);
  
  int rowColCount = map_->getCols() + map_->getRows();
  
  int width = rowColCount * Map::TILE_SIZE_HORIZONTAL/2;
  int height = rowColCount * Map::TILE_SIZE_VERTICAL/2;

  int xOffset = map_->getRows() * Map::TILE_SIZE_HORIZONTAL/2;
  int yOffset = 0;
  
  std::cout << "Rendering map (rows x cols): " << std::dec 
            <<map_->getRows() << "x" << map_->getCols() << std::endl;
  std::cout << "Rendering map: " << width << "x" << height << std::endl;
  
  if (!mapTexture_.create(width, height))
    std::cerr << "Couldn't create map texture!" << std::endl;
  
  mapTexture_.clear(sf::Color::Transparent);
  
//   mapImage_.create(width, height, sf::Color::Transparent);
  
  for (unsigned int col =0; col < map_->getCols(); col++)
  {
    for (unsigned int row = 0; row < map_->getRows(); row++)
    {
      res::TerrainPtr t = ResourceManager::Inst()->getTerrain(map_->getTileAt(col,row).terrain_id_);

      MapPos mpos(0,0,0);
      
      mpos.x += col*Map::TILE_SIZE;
      mpos.y += row*Map::TILE_SIZE;
      
      ScreenPos spos = mapToScreenPos(mpos);
      
      spos.x += xOffset;
      spos.y += yOffset;

      sf::Image img = t->getImage();
      
      // TODO use render texture if it's working again
//       mapImage_.copy(img, spos.x, spos.y, sf::IntRect(0,0,0, 0), true);
      
      sf::Texture texture;
      texture.loadFromImage(img);
      
      sf::Sprite sprite;
      sprite.setTexture(texture);
      sprite.setPosition(spos);
      
      mapTexture_.draw(sprite);
    }
  }  
  
//   mapImage_.saveToFile("map.png");
  mapTexture_.getTexture().copyToImage().saveToFile("map.png");
  
}



}
