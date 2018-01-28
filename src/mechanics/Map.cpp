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

#include <genie/resource/SlpFrame.h>

#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <SFML/Graphics/Shape.hpp>
#include <resource/DataManager.h>
#include <unordered_set>

Logger &Map::log = Logger::getLogger("freeaoe.Map");

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
    cols_ = 10;
    rows_ = 10;

    tiles_.clear();

    MapTile grass;
    grass.elevation_ = 0;
    grass.terrain_ = ResourceManager::Inst()->getTerrain(0);

    tiles_.resize(cols_ * rows_, grass);

    res::TerrainPtr water_dat = ResourceManager::Inst()->getTerrain(1);
    std::cout << "animframes " << grass.terrain_->data().AnimationFrames << std::endl;

    for (int i=1; i<8; i++) {
        tiles_[2 * 10 + i].elevation_ = 1;
    }

    tiles_[53].terrain_ = water_dat;
    tiles_[54].terrain_ = water_dat;
    tiles_[55].terrain_ = water_dat;
    tiles_[56].terrain_ = water_dat;
    tiles_[63].terrain_ = water_dat;
    tiles_[65].terrain_ = water_dat;
    tiles_[66].terrain_ = water_dat;
    tiles_[73].terrain_ = water_dat;
}

void Map::create(genie::ScnMap mapDescription)
{
    std::cout << "tile count " << mapDescription.tiles.size() << std::endl;
    std::cout << "size: " << mapDescription.width << "x" << mapDescription.height << std::endl;
    tiles_.clear();

    cols_ = mapDescription.width;
    rows_ = mapDescription.height;

    tiles_.resize(cols_ * rows_);

    for (int i = 0; i < tiles_.size(); i++) {
        genie::MapTile tile = mapDescription.tiles[i];

        tiles_[i].elevation_ = tile.elevation;

        tiles_[i].terrain_ = ResourceManager::Inst()->getTerrain(tile.terrainID);
    }
}

unsigned int Map::getCols()
{
    return cols_;
}

unsigned int Map::getRows()
{
    return rows_;
}

unsigned int Map::height()
{
    return rows_ * TILE_SIZE;
}

unsigned int Map::width()
{
    return cols_ * TILE_SIZE;
}

MapTile &Map::getTileAt(unsigned int col, unsigned int row)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        log.error("Trying to get MapTile out of index!");
        static MapTile nulltile;
        return nulltile;
    }

    return tiles_[index];
}

void Map::setTileAt(unsigned col, unsigned row, unsigned id)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        log.error("Trying to get MapTile out of index!");
        return;
    }

    tiles_[index].terrain_ = ResourceManager::Inst()->getTerrain(id);
}

void Map::updateMapData()
{
    for (MapTile &tile : tiles_) {
        tile.reset();
    }

    for (unsigned int col = 0; col < cols_; col++) {
        for (unsigned int row = 0; row < rows_; row++) {
            updateTileBlend(col, row);
        }
    }
}

enum Direction : int {
    None = 0,
    West = 1 << 0,
    North = 1 << 1,
    East = 1 << 2,
    South = 1 << 3,
    NorthWest = 1 << 4,
    NorthEast = 1 << 5,
    SouthWest = 1 << 6,
    SouthEast = 1 << 7,
};

enum BlendTile {
    LowerLeft1 = 0,
    UpperLeft1 = 4,
    LowerRight1 = 8,
    UpperRight1 = 12,

    Right = 16,
    Down = 17,
    Up = 18,
    Left = 19,

    UpperRightAndLowerLeft = 20,
    UpperLeftAndLowerRight = 21,

    OnlyRight = 22,
    OnlyDown = 23,
    OnlyUp = 24,
    OnlyLeft = 25,

    KeepUpperLeft = 26,
    KeepUpperRight = 27,
    KeepLowerRight = 28,
    KeepLowerLeft = 29,
    All = 30,
};

void Map::updateTileBlend(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    const genie::Terrain &tileData = tile.terrain_->data();
    uint32_t tileId = tile.terrain_->getId();

    std::unordered_map<uint8_t, int> blendDirections;
    std::unordered_set<uint8_t> neighborIds;

    std::unordered_map<uint8_t, int32_t> blendPriorities;

    std::unordered_map<uint8_t, res::TerrainPtr> neighborTerrains;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (!dx && !dy) {
                continue;
            }

            if (tileX + dx < 0 || tileX + dx >= cols_) {
                continue;
            }
            if (tileY + dy < 0 || tileY + dy >= rows_) {
                continue;
            }


            MapTile &neighbor = getTileAt(tileX + dx, tileY + dy);
            const uint8_t neighborId = neighbor.terrain_->getId();
            if (tileId == neighborId) {
                continue;
            }
            const genie::Terrain &neighborData = neighbor.terrain_->data();

            if (tileData.BlendPriority >= neighborData.BlendPriority) {
                continue;
            }
            blendPriorities[neighborId] = neighborData.BlendPriority;
            neighborTerrains[neighborId] = neighbor.terrain_;

            neighborIds.insert(neighborId);
            Direction direction = None;
            if (dx < 0) {
                if (dy > 0) {
                    direction = SouthWest;
                } else if (dy < 0) {
                    direction = NorthWest;
                } else {
                    direction = West;
                }
            } else if (dx > 0) {
                if (dy > 0) {
                    direction = SouthEast;
                } else if (dy < 0) {
                    direction = NorthEast;
                } else {
                    direction = East;
                }
            } else {
                if (dy > 0) {
                    direction = South;
                } else {
                    direction = North;
                }
            }

            blendDirections[neighborId] |= direction;
        }
    }

    if (neighborIds.empty()) {
        return;
    }

    std::vector<uint8_t> idsToDraw(neighborIds.begin(), neighborIds.end());
    std::sort(idsToDraw.begin(), idsToDraw.end(), [&](const uint8_t a, const uint8_t b){
        return blendPriorities[a] < blendPriorities[b];
    });

    sf::Image blendImage = tile.terrain_->image(tileX, tileY);

    for (const uint8_t id : idsToDraw) {
        std::vector<BlendTile> blends;
        res::TerrainPtr terrain = neighborTerrains[id];

        int direction = blendDirections[id];
        if (direction & South) {
            direction &= ~SouthWest;
            direction &= ~SouthEast;
        }
        if (direction & North) {
            direction &= ~NorthWest;
            direction &= ~NorthEast;
        }
        if (direction & West) {
            direction &= ~NorthWest;
            direction &= ~SouthWest;
        }
        if (direction & East) {
            direction &= ~NorthEast;
            direction &= ~SouthEast;
        }

        if (direction & NorthWest) {
            blends.push_back(Left);
        }
        if (direction & NorthEast) {
            blends.push_back(Up);
        }
        if (direction & SouthWest) {
            blends.push_back(Down);
        }
        if (direction & SouthEast) {
            blends.push_back(Right);
        }

        int blendFrame = -1;
        switch (direction & 0xF) {
        case None:
            break;
        case East:
            blendFrame = UpperLeft1;
            break;
        case South:
            blendFrame = LowerLeft1;
            break;
        case West:
            blendFrame = LowerRight1;
            break;
        case North:
            blendFrame = UpperRight1;
            break;

        case East | West:
            blendFrame = UpperRightAndLowerLeft;
            break;
        case North | South:
            blendFrame = UpperLeftAndLowerRight;
            break;

        case North | East:
            blendFrame = OnlyDown;
            break;
        case North | West:
            blendFrame = OnlyRight;
            break;
        case South | West:
            blendFrame = OnlyUp;
            break;
        case South | East:
            blendFrame = OnlyLeft;
            break;

        case South | East | West:
            blendFrame = KeepUpperLeft;
            break;
        case North | East | West:
            blendFrame = KeepUpperRight;
            break;
        case North | South | West:
            blendFrame = KeepLowerRight;
            break;
        case North | South | East:
            blendFrame = KeepLowerLeft;
            break;

        case North | South | East | West:
            blendFrame = All;
            break;

        default:
            log.warn("Unhandled terrain borders: 0x%x (raw: 0x%x)", direction, blendDirections[id]);
            break;
        }

        if (blendFrame >= 0) {
            blends.push_back(BlendTile(blendFrame));
        }

        for (const BlendTile blend : blends) {
            terrain->blendImage(&blendImage, int(blend), res::Terrain::blendMode(tileData.BlendType, terrain->data().BlendType), tileX, tileY);
        }
    }

    if (blendImage.getSize().x == 0 || blendImage.getSize().y == 0) {
        log.error("Failed to create blend image");
        return;
    }

    tile.blendOverlay.loadFromImage(blendImage);
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
    
    if (true || (*it)->col == 7 && (*it)->row == 3)
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
  for (MapTileArray::iterator it = tiles_.begin(); it != tiles_.end(); it++)
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
