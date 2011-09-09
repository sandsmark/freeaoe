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

Map::Map()
{

}

Map::~Map()
{
  for (std::vector< MapNode* >::iterator it = nodes_.begin();
       it != nodes_.end(); it ++)
       delete (*it);
}

void Map::setUpSample()
{
  node_cols_ = 10;
  node_rows_ = 10;
  
  makeGrid();
  
}

sf::Uint32 Map::getCols()
{
  return  node_cols_;
}

sf::Uint32 Map::getRows()
{
  return node_rows_;
}

void Map::draw(sf::RenderTarget* render_target)
{
  sf::Uint32 x_offset = 512;
  sf::Uint32 y_offset = 100;
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
  
  for (std::vector< MapNode* >::iterator it = nodes_.begin();
       it != nodes_.end(); it ++)
  {
    spr.SetX((*it)->x_pos + x_offset);
    spr.SetY((*it)->y_pos + y_offset);
    
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
    } */
    
    render_target->Draw(spr);
  }

}

void Map::makeGrid(void )
{
  for (int col = 0; col < node_cols_; col ++)
  {
    for (int row = 0; row < node_rows_; row ++)
    {
      MapNode *node = new MapNode();
      
      node->col = col;
      node->row = row;
      
      node->x_pos = ( node->col - node->row ) * ( Map::TILE_WIDTH / 2 );
      node->y_pos = ( node->col + node->row ) * ( Map::TILE_HEIGHT / 2);
      
      nodes_.push_back(node);
    }
  }
}


