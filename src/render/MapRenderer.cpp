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
  
  xOffset_ = 0;//-1200;
  yOffset_ = 0;//-1500;
  
  cameraPos_.x = 192;
  cameraPos_.y = 0;
  cameraPos_.z = 0;
  
  camChanged_ = true;
}

MapRenderer::~MapRenderer()
{

}

void MapRenderer::update(Time time)
{
  if (map_.get() != 0 && camChanged_)
  {
    // Get the absolute map positions of the rendertarget corners
    ScreenPos camCenter;
    camCenter.x = renderTarget_->getSize().x/2.0;
    camCenter.y = renderTarget_->getSize().y/2.0;
    
    // relative map positions (from center) //only changes if renderTargets resolution does
    MapPos nullCenterMp = screenToMapPos(camCenter);
    MapPos nulltopLeftMp = screenToMapPos(ScreenPos(0,0));
    MapPos nullbotLeftMp = screenToMapPos(ScreenPos(0, renderTarget_->getSize().y));
    MapPos nullTopRightMp = screenToMapPos(ScreenPos(renderTarget_->getSize().x, 0));
    MapPos nullBotRightMp = screenToMapPos(ScreenPos(renderTarget_->getSize().x, renderTarget_->getSize().y));
    
    // absolute map positions
    MapPos topLeftMp = cameraPos_ - nullCenterMp;
    MapPos botRightMp = cameraPos_ + (nullBotRightMp - nullCenterMp);
    
    MapPos topRightMp = cameraPos_ + (nullTopRightMp - nullCenterMp);
    MapPos botLeftMp = cameraPos_ + (nullbotLeftMp - nullCenterMp);
    
    std::cout << "nulC " << nullCenterMp.x << " " << nullCenterMp.y << std::endl;
    std::cout << "topLeftMp " << topLeftMp.x << " " << topLeftMp.y << std::endl;
    std::cout << "botRightMp " << botRightMp.x << " " << botRightMp.y << std::endl;
    
    // get column and row boundaries for rendering
    rColBegin_ = topLeftMp.x/Map::TILE_SIZE; //int = round down //TODO Plattform independent?
    
    if (rColBegin_ < 0) rColBegin_ = 0;
    if (rColBegin_ > map_->getCols()) 
    {
      rColBegin_ = map_->getCols();
      std::cout << "E: Somethings fishy... (rColBegin_ > map_->getCols())" << std::endl;
    }
    
    rColEnd_ = botRightMp.x/Map::TILE_SIZE;
    rColEnd_ ++; //round up
    
    if (rColEnd_ < 0) 
    {
      rColEnd_ = 0;
      std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    if (rColEnd_ > map_->getCols()) rColEnd_ = map_->getCols();
    
    rRowBegin_ = topRightMp.y/Map::TILE_SIZE;
    
    if (rRowBegin_ < 0) rRowBegin_ = 0;
    if (rRowBegin_ > map_->getRows())
    {
      std::cout << "E: Somethings fishy... (rRowBegin > map_->getRows())" << std::endl;
      rRowBegin_ = map_->getRows();
    }
    
    rRowEnd_ = botLeftMp.y/Map::TILE_SIZE;
    rRowEnd_ ++; // round up
    
    if (rRowEnd_ < 0)
    {
      rRowEnd_ = 0;
      std::cout << "E: Somethings fishy... (rColEnd_ < 0)" << std::endl;
    }
    if (rRowEnd_ > map_->getRows()) rRowEnd_ = map_->getRows();
    
    // Calculating screen offset to MapPos(rColBegin, rColEnd):
    
    MapPos offsetMp;
    offsetMp.x = rColBegin_*Map::TILE_SIZE;
    offsetMp.y = rRowBegin_*Map::TILE_SIZE;
    offsetMp.z = 0;
    
    ScreenPos offsetSp = mapToScreenPos(offsetMp - topLeftMp);
    
    std::cout << "\nrColBegin: " << rColBegin_ << std::endl;
    std::cout << "rColEnd: " << rColEnd_ << std::endl;
    std::cout << "rRowEnd: " << rRowEnd_ << std::endl;
    
    std::cout << "\noffsetMp = " << offsetMp.x << " " << offsetMp.y << std::endl;
    std::cout << "offsetSp = " << offsetSp.x << " " << offsetSp.y << std::endl;
    
    xOffset_ = offsetSp.x;
    yOffset_ = offsetSp.y;
    
    camChanged_ = false;
    
  }
}

void MapRenderer::display(void)
{
  //TODO: very ugly code for testing purposes
  for (unsigned int col = rColBegin_; col < rColEnd_; col++)
  {
    for (unsigned int row = rRowBegin_; row < rRowEnd_; row++)
    {
      res::TerrainPtr t = ResourceManager::Inst()->getTerrain(map_->getTileAt(col, row).terrain_id_);

      //TODO: MapPos to screenpos (Tile 0,0 is drawn at MapPos 0,0
      MapPos mpos(0,0,0);
      
      mpos.x += (col - rColBegin_)*Map::TILE_SIZE;
      mpos.y += (row - rRowBegin_)*Map::TILE_SIZE;
      
      ScreenPos spos = mapToScreenPos(mpos);
      
      spos.x += xOffset_;
      spos.y += yOffset_;

      spos.x -= Map::TILE_SIZE_HORIZONTAL/2;
      
      sf::Image img = t->getImage();
      
      renderTarget_->draw(img, spos);
    }
  } 
  
  
  /*
  ScreenPos pos(xOffset_, yOffset_);
  
//   renderer.draw(mapImage_, pos);
  renderTarget_->draw(mapTexture_.getTexture(), pos);
  */
  
}

void MapRenderer::setMap(MapPtr map)
{
  map_ = map;
  
  //ARrg TODO Pls change before commit :(
//   MapPos h(map_->getCols()*Map::TILE_SIZE, map_->getRows() * Map::TILE_SIZE, 0);
//   MapPos w((map_->getCols() + 1) * Map::TILE_SIZE, 0, 0);
  /*
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
  */
  
}

MapPos MapRenderer::getMapPosition(ScreenPos pos)
{
  ScreenPos camCenter;
  camCenter.x = renderTarget_->getSize().x/2.0;
  camCenter.y = renderTarget_->getSize().y/2.0;
  
  // relative map positions (from center)
  MapPos nullCenterMp = screenToMapPos(camCenter);
  
  MapPos nullPos = screenToMapPos(pos);
  
  MapPos absMapPos = cameraPos_ + (nullPos - nullCenterMp);
  
//   return MapPos(map_->getCols()*Map::TILE_SIZE, 0, 0) + absMapPos;
  return absMapPos;
}

