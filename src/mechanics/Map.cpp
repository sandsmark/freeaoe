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

Map::Map() : map_txt_(0)
{

}

Map::~Map()
{
  for (NodeMap::iterator it = nodes_.begin();
       it != nodes_.end(); it ++)
       delete it->second;
}

void Map::setUpSample()
{
  node_cols_ = 20;
  node_rows_ = 20;
  
  makeGrid();
  makeTiles();
  
}

sf::Uint32 Map::getCols()
{
  return  node_cols_;
}

sf::Uint32 Map::getRows()
{
  return node_rows_;
}

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
  } */
  
  for (TileArray::iterator it = tiles_.begin(); it != tiles_.end(); it++)
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
  }

}

void Map::makeGrid(void )
{
      srand(time(0));     
  for (int col = 0; col < node_cols_; col ++)
  {
    for (int row = 0; row < node_rows_; row ++)
    {
      MapNode *node = new MapNode();
      
      node->col = col;
      node->row = row;
      
      if ( rand() % 3 == 1 )
        node->height = (rand() % 3) - 1;
      
      node->x_pos = (node->col - node->row) * (Map::TILE_SIZE_HORIZONTAL / 2);
      node->y_pos = (node->col + node->row) * (Map::TILE_SIZE_VERTICAL / 2);
      node->z_pos = node->height * (Map::TILE_SIZE_HEIGHT / 2);

      
      nodes_[ColRowPair(col, row)] = node;
    }
  }
}

void Map::makeTiles(void )
{
  for (int col = 0; col < node_cols_; col ++)
  {
    for (int row = 0; row < node_rows_; row ++)
    {
      MapTile *tile = new MapTile();
      
      tile->north = getNodeByCoords(col, row);
      tile->east = getNodeByCoords(col + 1, row);
      tile->south = getNodeByCoords(col + 1, row + 1);
      tile->west = getNodeByCoords(col, row + 1);
      
      tiles_.push_back(tile);
    }
  }
}


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



