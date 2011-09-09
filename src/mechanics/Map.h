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


#ifndef MAP_H
#define MAP_H
#include <data/GenieTerrain.h>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class MapNode
{
public:
  sf::Uint32 row, col;
  sf::Uint32 x_pos, y_pos;
};

class Map
{

public:
  static const sf::Uint32 TILE_HEIGHT = 48;
  static const sf::Uint32 TILE_WIDTH = 96;
  
  Map();
  virtual ~Map();
  
  void setUpSample();
  
  sf::Uint32 getRows();
  sf::Uint32 getCols();
  
  GenieTerrain getTerrain(unsigned int col, unsigned int row) { return terrain_[col][row]; }
  
  //TODO: Outsource to RenderMap!
  void draw(sf::RenderTarget *render_target);
  
private:
  GenieTerrain terrain_[4][4];
  
  std::vector<MapNode *> nodes_;
  
  sf::Uint32 node_rows_;
  sf::Uint32 node_cols_;
  
  /// Creates the node grid
  void makeGrid(void);
};

#endif // MAP_H
