/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#include "Map.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <resource/ResourceManager.h>

#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <SFML/Graphics/Shape.hpp>
#include <resource/DataManager.h>

Logger& Map::log = Logger::getLogger("freeaoe.Map");

Map::Map() //: map_txt_(0)
{

}

Map::~Map()
{
  /*
  for (NodeMap::iterator it = nodes_.begin();
       it != nodes_.end(); it ++)
       delete it->second;
  */
}

void Map::setUpSample()
{
  cols_ = 4;
  rows_ = 4;
  
  tiles_.clear();
  
  MapTile grass;
  grass.elevation_ = 0;
  grass.terrain_ = DataManager::Inst().getTerrain(0);
  
  tiles_.resize(cols_ * rows_);
  
  gdat::Terrain water_dat = DataManager::Inst().getTerrain(1);
  
  tiles_[7].terrain_ = water_dat;
  tiles_[9].terrain_ = water_dat;
  tiles_[10].terrain_ = water_dat;
  tiles_[11].terrain_ = water_dat;
  
  
  /*makeGrid(true);
  makeTiles();
  updateElevations();
  */
}

unsigned int Map::getCols()
{
  return  cols_;
}

unsigned int Map::getRows()
{
  return rows_;
}

MapTile Map::getTileAt(unsigned int col, unsigned int row)
{
  unsigned int index = row * cols_ + col;
  
  if (index >= tiles_.size())
    log.error("Trying to get MapTile out of index!");
  else
  {
    return tiles_[index];
  }
}


/*
void Map::addNodeToShape(sf::Shape *shape, MapNode *node, sf::Color *point_col)
{
  if (node)
  {
    shape->AddPoint(node->x_pos + x_offset_, 
                    node->y_pos - node->z_pos + y_offset_, *point_col,
                    sf::Color::Blue
                   );
  }
}

void Map::draw(sf::RenderTarget* render_target)
{
  x_offset_ = 512;
  y_offset_ = 0;
/*
  sf::Image img;

  img.Create(5,3,sf::Color(0,0,0,0));
  img.SetPixel(2,0,sf::Color(255,0,0));
  img.SetPixel(1,1,sf::Color(255,0,0));
  img.SetPixel(3,1,sf::Color(255,0,0));
  img.SetPixel(0,2,sf::Color(255,0,0));
  img.SetPixel(4,2,sf::Color(255,0,0));
  sf::Texture txt;
  txt.LoadFromImage(img);
  
  sf::Sprite spr;
  spr.SetTexture(txt);
  
  for (NodeMap::iterator it = nodes_.begin(); it != nodes_.end(); it ++)
  {
    spr.SetX((it->second)->x_pos + x_offset_);
    spr.SetY((it->second)->y_pos + y_offset_);
    
    /*if (true || (*it)->col == 7 && (*it)->row == 3)
    {
      sf::Texture ter;
      ter.LoadFromImage(*ResourceManager::Inst()->getSlp(15000)->getImage());

      sf::Sprite spr2;
      spr2.SetTexture(ter);
      spr2.SetX((*it)->x_pos - Map::TILE_WIDTH/2);
      spr2.SetY((*it)->y_pos);
      
      spr2.SetTexture(ter);
      render_target->Draw(spr2);
    } 
    /
    
    render_target->Draw(spr); 
  } *
  
  for (MapTileArray::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
    sf::Shape shape;
    
    sf::Color point(0,255,0);
    
    addNodeToShape(&shape, (*it)->north, &point);
    addNodeToShape(&shape, (*it)->east, &point);
    addNodeToShape(&shape, (*it)->south, &point);
    addNodeToShape(&shape, (*it)->west, &point);
    
    //shape.EnableFill(false);
    shape.EnableOutline(true);
    shape.SetOutlineThickness(1);
    
    render_target->Draw(shape);
  }*

}
/*
void Map::makeGrid(bool topDown )
{
           
  for (int col = 0; col < node_cols_; col ++)
  {
    for (int row = 0; row < node_rows_; row ++)
    {
      MapNode *node = new MapNode();
      
      node->col = col;
      node->row = row;
      node->elevation = 0;
      
      //if ( rand() % 3 == 1 )
      //  node->elevation = (rand() % 4);
      
      if (topDown)
      {
        node->x_pos = node->col * Map::TILE_SIZE;
        node->y_pos = node->row * Map::TILE_SIZE;
      }
      else
      {
        node->x_pos = (node->col - node->row) * (Map::TILE_SIZE_HORIZONTAL / 2);
        node->y_pos = (node->col + node->row) * (Map::TILE_SIZE_VERTICAL / 2);
        node->z_pos = 0;//Map::TILE_SIZE_HEIGHT/2;
        //if (node->elevation == 0)
        //  node->z_pos = -1 * (Map::TILE_SIZE_HEIGHT / 2);
        //else
          //node->z_pos = node->elevation * (Map::TILE_SIZE_HEIGHT / 2);
      }

      
      nodes_[ColRowPair(col, row)] = node;
    }
  }
}

void Map::makeTiles(void )
{
  srand(time(0));
  
  for (int col = 0; col < node_cols_; col ++)
  {
    for (int row = 0; row < node_rows_; row ++)
    {
      MapTile tile;
      
      tile.north = getNodeByCoords(col, row);
      tile.east = getNodeByCoords(col + 1, row);
      tile.south = getNodeByCoords(col + 1, row + 1);
      tile.west = getNodeByCoords(col, row + 1);
      
      //if (rand() % 4 == 0)
      //  tile->elevation = (rand() % 2);
      
      tiles_.push_back(tile);
    }
  }
}

void Map::updateElevation(MapNode* node, Int32 elevation)
{
  if (node && node->z_pos > elevation)
    node->z_pos = elevation;
}


void Map::updateElevations(void )
{
/*  for (MapTileArray::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
    Int32 elev;
    
    if ((*it).elevation == 0)
      elev = (TILE_SIZE_HEIGHT/2);
    else
      elev = (*it)->elevation * (-(TILE_SIZE_HEIGHT/2));
    
    updateElevation((*it)->north, elev);
    updateElevation((*it)->east, elev);
    updateElevation((*it)->south, elev);
    updateElevation((*it)->west, elev);
  }*
}
/*

MapNode* Map::getNodeByCoords(sf::Uint32 col, sf::Uint32 row)
{
  MapNode *node = 0;
  
  try
  {
    node = nodes_.at(ColRowPair(col, row));
  }
  catch (std::out_of_range e)
  {
    node = 0;
  }
  
  return node;
}

*/

