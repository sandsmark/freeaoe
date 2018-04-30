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
#include <resource/Resource.h>

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
    cols_ = 20;
    rows_ = 20;

    tiles_.clear();

    MapTile grass;
    grass.elevation_ = 0;
    grass.terrain_ = ResourceManager::Inst()->getTerrain(2);

    tiles_.resize(cols_ * rows_, grass);

    res::TerrainPtr water_dat = ResourceManager::Inst()->getTerrain(1);

    for (int i=3; i<6; i++) {
        getTileAt(15, i).elevation_ = 1;
    }
    for (int i=3; i<6; i++) {
        getTileAt(16, i).elevation_ = 1;
    }

    getTileAt(6, 6).terrain_ = water_dat;
    getTileAt(6, 10).terrain_ = water_dat;
    getTileAt(6, 5).terrain_ = water_dat;
    getTileAt(4, 5).terrain_ = water_dat;
//    getTileAt(5, 5).terrain_ = water_dat;
    getTileAt(5, 6).terrain_ = water_dat;
    getTileAt(3, 7).terrain_ = water_dat;
    getTileAt(4, 7).terrain_ = water_dat;
    getTileAt(5, 7).terrain_ = water_dat;
    getTileAt(6, 7).terrain_ = water_dat;
    getTileAt(7, 7).terrain_ = water_dat;
//    getTileAt(5, 8).terrain_ = water_dat;
    getTileAt(5, 9).terrain_ = water_dat;
    getTileAt(6, 9).terrain_ = water_dat;
    getTileAt(4, 10).terrain_ = water_dat;
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

int Map::getCols()
{
    return cols_;
}

int Map::getRows()
{
    return rows_;
}

int Map::height()
{
    return rows_ * TILE_SIZE;
}

int Map::width()
{
    return cols_ * TILE_SIZE;
}

float Map::elevationAt(const MapPos &position)
{
    return getTileAt(position.x / Map::TILE_SIZE, position.y / Map::TILE_SIZE).elevation_ * DataManager::Inst().terrainBlock().ElevHeight;
}

MapTile &Map::getTileAt(unsigned int col, unsigned int row)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        log.error("Trying to get MapTile (%x%) out of bounds!", col, row);
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
    TIME_THIS;

    for (MapTile &tile : tiles_) {
        tile.reset();
    }

    for (unsigned int col = 0; col < cols_; col++) {
        for (unsigned int row = 0; row < rows_; row++) {
            updateTileBlend(col, row);
        }
    }

    for (unsigned int col = 0; col < cols_; col++) {
        for (unsigned int row = 0; row < rows_; row++) {
            updateTileSlopes(col, row);
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

using res::Blend;

void Map::updateTileBlend(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    const genie::Terrain &tileData = tile.terrain_->data();

//    if (tileData.SLP < 0) {
//        log.error("Invalid tile data");
//        return;
//    }

    uint32_t tileId = tile.terrain_->getId();

    std::unordered_map<uint8_t, int> blendDirections;
    std::unordered_set<uint8_t> neighborIds;

    std::unordered_map<uint8_t, int32_t> blendPriorities;

    std::unordered_map<uint8_t, res::TerrainPtr> neighborTerrains;

    uint8_t neighborsAbove = 0;
    uint8_t neighborsBelow = 0;

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

            MapTile &neighbor = getTileAt(tileX + dx, tileY + dy);

            if (neighbor.elevation_ > tile.elevation_) {
                neighborsAbove |= direction;
            } else if (neighbor.elevation_ < tile.elevation_) {
                neighborsBelow |= direction;
            }

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

            blendDirections[neighborId] |= direction;
        }
    }

//    if (neighborsAbove & West) {
//        neighborsAbove &= ~NorthWest;
//        neighborsAbove &= ~SouthWest;
//    }

//        if (direction & South) {
//            direction &= ~SouthWest;
//            direction &= ~SouthEast;
//        }
//        if (direction & North) {
//            direction &= ~NorthWest;
//            direction &= ~NorthEast;
//        }
//        if (direction & West) {
//            direction &= ~NorthWest;
//            direction &= ~SouthWest;
//        }
//        if (direction & East) {
//            direction &= ~NorthEast;
//            direction &= ~SouthEast;
//        }

    tile.z = tile.elevation_ * DataManager::Inst().terrainBlock().ElevHeight;
    if (neighborsBelow == None) {
        if (neighborsAbove & North) {
            tile.slope = genie::SlopeSouthWestUp;
        } else if (neighborsAbove & South) {
            tile.slope = genie::SlopeNorthEastUp ;
            tile.z += DataManager::Inst().terrainBlock().ElevHeight;
        } else if (neighborsAbove & East) {
            tile.slope = genie::SlopeSouthEastUp;
        } else if (neighborsAbove & West) {
            tile.slope = genie::SlopeNorthWestUp;
            tile.z += DataManager::Inst().terrainBlock().ElevHeight;
        } else if (neighborsAbove == NorthWest) {
            tile.slope = genie::SlopeWestUp;
        } else if (neighborsAbove == NorthEast) {
            tile.slope = genie::SlopeSouthUp;
        } else if (neighborsAbove == SouthWest) {
            tile.slope = genie::SlopeNorthUp;
            tile.z += DataManager::Inst().terrainBlock().ElevHeight;
        } else if (neighborsAbove == SouthEast) {
            tile.slope = genie::SlopeEastUp;
        }
    }

    if (tile.slope) {
        return;
    }

    if (neighborIds.empty()) {
        return;
    }

    std::vector<uint8_t> idsToDraw(neighborIds.begin(), neighborIds.end());
    std::sort(idsToDraw.begin(), idsToDraw.end(), [&](const uint8_t a, const uint8_t b){
        return blendPriorities[a] < blendPriorities[b];
    });

    sf::Texture t;
    t.loadFromImage(tile.terrain_->image(tileX, tileY));
    tile.textures.push_back(t);

    for (const uint8_t id : idsToDraw) {
        Blend blends;

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
            blends.addBlend(Blend::Left);
        }
        if (direction & NorthEast) {
            blends.addBlend(Blend::Down);
        }
        if (direction & SouthWest) {
            blends.addBlend(Blend::Up);
        }
        if (direction & SouthEast) {
            blends.addBlend(Blend::Right);
        }

        if (direction & East) {
            blends.addBlend(Blend::LowerLeft1);
        }
        if (direction & South) {
            blends.addBlend(Blend::UpperLeft1);
        }
        if (direction & West) {
            blends.addBlend(Blend::UpperRight1);
        }
        if (direction & North) {
            blends.addBlend(Blend::LowerRight1);
        }



        switch (direction & 0xF) {
        case None:
            break;
//        case East:
//            blendFrame = LowerLeft1;
//            break;
//        case South:
//            blendFrame = UpperLeft1;
//            break;
//        case West:
//            blendFrame = UpperRight1;
//            break;
//        case North:
//            blendFrame = LowerRight1;
//            break;

        case East | West:
            blends.addBlend(Blend::UpperLeftAndLowerRight);
            break;
        case North | South:
            blends.addBlend(Blend::UpperRightAndLowerLeft);
            break;

        case North | East:
            blends.addBlend(Blend::OnlyUp);
            break;
        case North | West:
            blends.addBlend(Blend::OnlyRight);
            break;
        case South | West:
            blends.addBlend(Blend::OnlyDown);
            break;
        case South | East:
            blends.addBlend(Blend::OnlyLeft);
            break;
            //// OK ///////

        case South | East | West:
            blends.addBlend(Blend::KeepLowerLeft);
            break;
        case North | East | West:
            blends.addBlend(Blend::KeepUpperRight);
            break;
        case North | South | West:
            blends.addBlend(Blend::KeepLowerRight);
            break;
        case North | South | East:
            blends.addBlend(Blend::KeepUpperLeft);
            break;

        case North | South | East | West:
            blends.addBlend(Blend::All);
            break;

        default:
//            log.warn("Unhandled terrain borders: 0x%x (raw: 0x%x)", direction, blendDirections[id]);
            break;
        }

        res::TerrainPtr neighbor = neighborTerrains[id];
        blends.blendMode = res::Terrain::blendMode(tileData.BlendType, neighbor->data().BlendType);

        tile.textures.push_back(neighbor->blendImage(blends, tileX, tileY));
    }
}

void Map::updateTileSlopes(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    if (!tile.slope) {
        return;
    }
    const genie::Terrain &tileData = tile.terrain_->data();
    if (tileData.SLP == -1) {
        return;
    }

    const genie::Slope slopeNorth = slopeAt(tileX - 1, tileY + 1);
    const genie::Slope slopeSouth = slopeAt(tileX + 1, tileY - 1);

    const genie::Slope slopeWest = slopeAt(tileX - 1, tileY - 1);
    const genie::Slope slopeEast = slopeAt(tileX + 1, tileY + 1);

    const genie::Slope slopeSouthWest = slopeAt(tileX, tileY - 1);
    const genie::Slope slopeSouthEast = slopeAt(tileX + 1, tileY);

    const genie::Slope slopeNorthWest = slopeAt(tileX - 1, tileY);
    const genie::Slope slopeNorthEast = slopeAt(tileX, tileY + 1);


    std::vector<genie::Pattern> patterns;
    switch (tile.slope) {
    case genie::SlopeSouthUp:
    case genie::SLOPE_S_UP2:
        patterns.push_back(genie::DiagDownPattern);

        if (slopeSouth == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern18);
        }

        if ((slopeNorthWest == genie::SlopeFlat) + (slopeNorth == genie::SlopeFlat) + (slopeNorthEast == genie::SlopeFlat) > 1) {
            patterns.push_back(genie::Pattern19);
        }

        if (slopeNorthWest == genie::SlopeFlat || slopeNorthWest == genie::SlopeNorthUp || slopeNorthWest == genie::SlopeWestUp || slopeNorthWest == genie::SlopeNorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopeNorthEast != genie::SlopeFlat && slopeNorthEast != genie::SlopeNorthUp && slopeNorthEast != genie::SlopeEastUp && slopeNorthEast != genie::SlopeNorthEastUp) {
            if (slopeEast != genie::SlopeFlat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfRightPattern);
        }

        if (slopeNorthEast == genie::SlopeSouthWestEastUp || slopeSouthEast == genie::SlopeSouthWestEastUp || slopeEast == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern22);
        }
        if (slopeNorthWest == genie::SlopeSouthWestEastUp || slopeSouthWest == genie::SlopeSouthWestEastUp || slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern21);
        }

        break;

    case genie::SlopeNorthUp:
    case genie::SLOPE_N_UP2:
        patterns.push_back(genie::DiagDownPattern);
        if (slopeNorth == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern16);
        }
        if ((slopeSouthWest == genie::SlopeFlat) + (slopeSouth == genie::SlopeFlat) + (slopeSouthEast == genie::SlopeFlat) > 1) {
            patterns.push_back(genie::Pattern17);
        }

        if (slopeSouthWest == genie::SlopeFlat || slopeSouthWest == genie::SlopeSouthUp || slopeNorthWest == genie::SlopeWestUp || slopeSouthWest == genie::SlopeSouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopeSouthEast != genie::SlopeFlat && slopeSouthEast != genie::SlopeSouthUp && slopeSouthEast != genie::SlopeEastUp && slopeSouthEast != genie::SlopeSouthEastUp) {
            if (slopeEast != genie::SlopeFlat) {
                patterns.push_back(genie::Pattern28);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }
        if (slopeNorthWest == genie::SlopeNorthWestEastUp || slopeSouthWest == genie::SlopeNorthWestEastUp || slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopeNorthEast == genie::SlopeNorthWestEastUp || slopeSouthEast == genie::SlopeNorthWestEastUp || slopeEast == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern22);
        }

        break;
    case genie::SlopeWestUp:
    case genie::SLOPE_W_UP2:
        patterns.push_back(genie::FlatPattern);
        if (slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern12);
        }

        if ((slopeNorthEast == genie::SlopeFlat) + (slopeEast == genie::SlopeFlat) + (slopeSouthEast == genie::SlopeFlat) > 1) {
            patterns.push_back(genie::Pattern13);
        }

        if (slopeNorthEast == genie::SlopeFlat || slopeNorthEast == genie::SlopeNorthUp || slopeNorthEast == genie::SlopeEastUp || slopeSouthWest == genie::SlopeNorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else if (slopeNorth == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern34);
        }

        if (slopeSouthEast != genie::SlopeFlat && slopeSouthEast != genie::SlopeSouthUp && slopeNorthEast != genie::SlopeEastUp && slopeNorthEast != genie::SlopeSouthEastUp) {
            if (slopeSouth != genie::SlopeFlat) {
                patterns.push_back(genie::Pattern35);
            }
        } else {
            patterns.push_back(genie::HalfUpPattern);
        }


        break;
    case genie::SlopeEastUp:
    case genie::SLOPE_E_UP2:
        patterns.push_back(genie::BlackPattern);

        if (slopeEast == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern14);
        }

        if ((slopeNorthWest == genie::SlopeFlat) + (slopeWest == genie::SlopeFlat) + (slopeSouthWest == genie::SlopeFlat) > 1) {
            patterns.push_back(genie::Pattern15);
        }

        if (slopeSouthWest == genie::SlopeFlat || slopeSouthWest == genie::SlopeSouthUp || slopeSouthWest == genie::SlopeWestUp || slopeSouthWest == genie::SlopeSouthWestUp) {
            patterns.push_back(genie::LeftPattern);
        } else if (slopeSouth == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopeNorthWest != genie::SlopeFlat && slopeNorthWest != genie::SlopeNorthUp && slopeNorthWest != genie::SlopeWestUp && slopeNorthWest != genie::SlopeNorthWestUp) {
            if (slopeNorth != genie::SlopeFlat) {
                patterns.push_back(genie::Pattern36);
            }
        } else {
            patterns.push_back(genie::DownPattern);
        }

        break;
    case genie::SlopeSouthWestUp:
        patterns.push_back(genie::FlatPattern);
        if (slopeSouthWest == genie::SlopeFlat || slopeSouthWest == genie::SlopeNorthUp || slopeSouthWest == genie::SlopeEastUp || slopeSouthWest == genie::SlopeNorthEastUp) {
            patterns.push_back(genie::HalfLeftPattern);
        } else {
            if (slopeWest == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern12);
            }

            if (slopeSouth == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern35);
            }
        }

        if (slopeNorthEast == genie::SlopeFlat || slopeNorthEast == genie::SlopeNorthUp || slopeNorthEast == genie::SlopeEastUp || slopeNorthEast == genie::SlopeNorthEastUp) {
            patterns.push_back(genie::HalfRightPattern);
        } else {
            if (slopeNorth == genie::SlopeFlat || slopeNorth == genie::SlopeSouthUp) {
                patterns.push_back(genie::Pattern34);
            }
            if (slopeEast == genie::SlopeFlat || slopeEast == genie::SlopeEastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopeSouth == genie::SlopeSouthUp && slopeSouthWest == genie::SlopeWestUp) {
            patterns.push_back(genie::Pattern35);
        }

        if (slopeSouthWest == genie::SlopeSouthUp && slopeWest == genie::SlopeWestUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopeNorthEast == genie::SlopeSouthWestEastUp || slopeSouthEast == genie::SlopeSouthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopeNorthWest == genie::SlopeSouthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopeEast == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern28);
        }

        break;
    case genie::SlopeNorthWestUp:
        patterns.push_back(genie::FlatPattern);
        if (slopeNorthWest == genie::SlopeFlat || slopeNorthWest == genie::SlopeSouthUp || slopeNorthWest == genie::SlopeEastUp || slopeNorthWest == genie::SlopeSouthEastUp) {
            patterns.push_back(genie::HalfDownPattern);
        } else {
            if (slopeWest == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern12);
            }
            if (slopeNorth == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern34);
            }
        }

        if (slopeSouthEast == genie::SlopeFlat || slopeSouthEast == genie::SlopeSouthUp || slopeSouthEast == genie::SlopeEastUp || slopeSouthEast == genie::SlopeSouthEastUp) {
            patterns.push_back(genie::HalfUpPattern);
        } else {
            if (slopeSouth == genie::SlopeFlat || slopeSouth == genie::SlopeSouthUp) {
                patterns.push_back(genie::Pattern35);
            }

            if (slopeEast == genie::SlopeFlat || slopeEast == genie::SlopeEastUp) {
                patterns.push_back(genie::Pattern28);
            }
        }

        if (slopeSouthWest == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern23);
        }

        if (slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopeNorthEast == genie::SlopeNorthWestEastUp) {
            patterns.push_back(genie::Pattern22);
        }

        if (slopeEast == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern28);
        }

        if (slopeNorth == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern34);
        }

        if (slopeWest == genie::SlopeWestUp && slopeNorthWest == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern12);
        }

        if (slopeNorthWest == genie::SlopeWestUp && slopeNorth == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern34);
        }

        break;
    case genie::SlopeSouthEastUp:
        patterns.push_back(genie::BlackPattern);

        if (slopeNorthWest == genie::SlopeFlat || slopeNorthWest == genie::SlopeNorthUp || slopeNorthWest == genie::SlopeWestUp || slopeNorthWest == genie::SlopeNorthWestUp) {
            patterns.push_back(genie::DownPattern);
        } else if (slopeWest == genie::SlopeFlat || slopeWest == genie::SlopeWestUp) {
            patterns.push_back(genie::Pattern26);
        }

        if (slopeNorth == genie::SlopeFlat || slopeNorth == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopeSouthEast == genie::SlopeFlat || slopeSouthEast == genie::SlopeSouthUp || slopeSouthEast == genie::SlopeEastUp || slopeSouthEast == genie::SlopeSouthEastUp) {
            patterns.push_back(genie::UpPattern);
        } else {
            if (slopeEast == genie::SlopeFlat){
                patterns.push_back(genie::Pattern14);
            }
            if (slopeSouth == genie::SlopeFlat){
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopeSouth == genie::SlopeSouthUp && slopeSouthEast == genie::SlopeEastUp) {
            patterns.push_back(genie::Pattern37);
        }

        if (slopeSouthEast == genie::SlopeSouthUp && slopeEast == genie::SlopeEastUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopeNorthEast == genie::SlopeSouthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopeWest == genie::SlopeSouthUp) {
            patterns.push_back(genie::Pattern21);
        }

        if (slopeNorthWest == genie::SlopeSouthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }

        break;
    case genie::SlopeNorthEastUp:
        patterns.push_back(genie::BlackPattern);

        if (slopeSouthWest == genie::SlopeFlat || slopeSouthWest == genie::SlopeSouthWestUp || slopeSouthWest == genie::SlopeWestUp || slopeSouthWest == genie::SlopeSouthUp) {
            patterns.push_back(genie::LeftPattern);
        } else {
            if (slopeWest == genie::SlopeFlat || slopeWest == genie::SlopeWestUp) {
                patterns.push_back(genie::Pattern26);
            }
            if (slopeSouth == genie::SlopeFlat || slopeSouth == genie::SlopeSouthUp) {
                patterns.push_back(genie::Pattern37);
            }
        }

        if (slopeNorthEast == genie::SlopeFlat || slopeNorthEast == genie::SlopeSouthUp || slopeNorthEast == genie::SlopeWestUp || slopeNorthEast == genie::SlopeSouthWestUp) {
            patterns.push_back(genie::RightPattern);
        } else {
            if(slopeNorth == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern36);
            }
            if (slopeEast == genie::SlopeFlat) {
                patterns.push_back(genie::Pattern14);
            }
        }

        if (slopeEast == genie::SlopeEastUp || slopeNorthEast == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern14);
        }

        if (slopeNorthEast == genie::SlopeEastUp || slopeNorth == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern36);
        }

        if (slopeSouthEast == genie::SlopeNorthUp) {
            patterns.push_back(genie::Pattern20);
        }

        if (slopeNorthWest == genie::SlopeNorthWestEastUp) {
            patterns.push_back(genie::Pattern21);
        }
        if (slopeWest == genie::SlopeFlat) {
            patterns.push_back(genie::Pattern26);
        }

        break;
    default:
        break;
    }


    sf::Image img = res::Resource::convertFrameToImage(ResourceManager::Inst()->getTemplatedSlp(tileData.SLP, tile.slope, patterns));
    sf::Texture t;
    t.loadFromImage(img);
    tile.textures.clear();
    tile.textures.push_back(t);
    return;

}

const genie::Slope Map::slopeAt(const int x, const int y)
{
    if (x < 0 || y < 0) {
        return genie::SlopeFlat;
    }

    return getTileAt(x, y).slope;
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
