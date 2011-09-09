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
#include <map>

namespace sf {
class Shape;
}

class MapNode
{
public:
  sf::Uint32 row, col;
  sf::Int32 height;
  sf::Int32 x_pos, y_pos, z_pos;
};

class MapTile
{
public:
  MapNode *north, *east, *south, *west;
};

class Map
{

public:
  static const sf::Uint32 TILE_SIZE_VERTICAL = 48;
  static const sf::Uint32 TILE_SIZE_HORIZONTAL = 96;
  static const sf::Uint32 TILE_SIZE_HEIGHT = 24;        //Mountain
  
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
  
  sf::Uint32 x_offset_;
  sf::Uint32 y_offset_;
  
  //std::vector<MapNode *> nodes_;
  typedef std::pair<sf::Uint32, sf::Uint32> ColRowPair;
  typedef std::map< ColRowPair , MapNode * > NodeMap;
  NodeMap nodes_;
  
  typedef std::vector<MapTile *> TileArray;
  TileArray tiles_;
  
  sf::Uint32 node_rows_;
  sf::Uint32 node_cols_;
  
  /// Creates the node grid
  void makeGrid(void);
  
  void makeTiles(void);
  
  void addNodeToShape(sf::Shape *shape, MapNode *node, sf::Color *point_col);
  
  MapNode *getNodeByCoords(sf::Uint32 col, sf::Uint32 row);
};

#endif // MAP_H
