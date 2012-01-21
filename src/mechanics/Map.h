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

#include <global/Logger.h>
#include <geniedat/Terrain.h>
#include <global/Types.h>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <map>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <core/Entity.h>
#include <resource/Terrain.h>

namespace sf {
class Shape;
}

class MapNode
{
public:
  unsigned int row, col;
  sf::Int8 elevation;
  sf::Int32 x_pos, y_pos, z_pos;
};

class MapTile
{
public:
  MapNode *north, *east, *south, *west;
  
  unsigned int elevation_;
  gdat::Terrain terrain_;
  unsigned int terrain_id_;
};

class Map : public Entity
{

public:  
  /*
   * A tiny-size map? 72 x 72.
   * A small-size map? 96 x 96.
   * A medium-size map? 120 x 120.
   * A large-size map? 144 x 144.
   * A huge-size map? 200 x 200.
   * A gigantic-size map? 255 x 255. 
   */
  
  static const unsigned int TILE_SIZE = 48;
  
  // Isometric sizes:
  static const unsigned int TILE_SIZE_VERTICAL = 48;
  static const unsigned int TILE_SIZE_HORIZONTAL = 96;
  static const unsigned int TILE_SIZE_HEIGHT = 24;        //Mountain
  
  Map();
  virtual ~Map();
  
  void setUpSample();
  
  unsigned int getRows();
  unsigned int getCols();
  
  MapTile getTileAt(unsigned int col, unsigned int row);
  
  // old stuff down ------------------------------------------------------------
  /*
  gdat::Terrain getTerrain(unsigned int col, unsigned int row) { return terrain_[col][row]; }
  
  //TODO: Outsource to RenderMap!
  void draw(sf::RenderTarget *render_target);
  */
  
private:
  
  static Logger &log;
  
  // cols_ = x, rows_ = y
  unsigned int rows_, cols_;
  
  typedef std::vector<MapTile> MapTileArray;
  MapTileArray tiles_;
  
  // old stuff down ------------------------------------------------------------
  /*
  gdat::Terrain terrain_[4][4];
  sf::RenderTexture *map_txt_;
  sf::Texture *s_map_txt_;
  
  sf::Int32 x_offset_;
  sf::Int32 y_offset_;
  
  //std::vector<MapNode *> nodes_;
  typedef std::pair<unsigned int, unsigned int> ColRowPair;
  typedef std::map< ColRowPair , MapNode * > NodeMap;
  NodeMap nodes_;
  
  
  unsigned int node_rows_;
  unsigned int node_cols_;
  
  /// Creates the node grid
  void makeGrid(bool topDown = false);
  
  void makeTiles(void);
  
  void updateElevation(MapNode *node, sf::Int32 elevation);
  void updateElevations(void);
  
  void addNodeToShape(sf::Shape *shape, MapNode *node, sf::Color *point_col);
  
  MapNode *getNodeByCoords(unsigned int col, unsigned int row);
  */
};

typedef boost::shared_ptr<Map> MapPtr;

#endif // MAP_H
