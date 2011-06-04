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


#include "MapRenderer.h"
#include <SFML/Graphics/Sprite.hpp>
#include <resource/Graphic.h>
#include <resource/ResourceManager.h>

MapRenderer::MapRenderer()
{

}

MapRenderer::~MapRenderer()
{

}

void MapRenderer::setMap(Map* map)
{
  map_ = map; 
  
  int x, y;
  x = y = 0;
  
  for (int col = 0; col < map->getCols(); col++)
  {
    for (int row = 0; row < map->getRows(); row++)
    {
      sf::Sprite spr;
      
      spr.SetX(x);
      spr.SetY(y);
      
      GenieTerrain ter = map->getTerrain(col, row);
      
      std::auto_ptr<Graphic> ptr = 
        ResourceManager::Inst()->getGraphic(ter.slp_id);
      /*
      spr.SetImage(*ptr->getImage());
      
      this->Draw(spr);*/
      
      x += 50;
      
    }
    
    x = 0;
    y += 50;
  }
}

