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
#include "global/Constants.h"
#include "core/Utility.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <resource/AssetManager.h>
#include <resource/Resource.h>

#include <genie/resource/SlpFrame.h>

#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <SFML/Graphics/Shape.hpp>
#include <resource/DataManager.h>
#include <unordered_set>

Map::Map() //: map_txt_(0)
{
//    DBG << DataManager::Inst().datFile().TerrainBlock.TileSizes.size();
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
    grass.terrain_ = AssetManager::Inst()->getTerrain(0);

    tiles_.resize(cols_ * rows_, grass);

    for (int i=6; i<10; i++) {
        getTileAt(0, i).terrain_ = AssetManager::Inst()->getTerrain(2);
        getTileAt(1, i).terrain_ = AssetManager::Inst()->getTerrain(2);
        getTileAt(2, i).terrain_ = AssetManager::Inst()->getTerrain(1);
    }
    for (int i=4; i<6; i++) {
        getTileAt(i, 10).terrain_ = AssetManager::Inst()->getTerrain(1);
    }

    for (int i=3; i<6; i++) {
        getTileAt(14, i).elevation_ = 1;
    }

    for (int i=3; i<6; i++) {
        getTileAt(15, i).elevation_ = 1;
    }

    getTileAt(13, 4).elevation_ = 1;
    getTileAt(16, 4).elevation_ = 1;
    getTileAt(17, 4).elevation_ = 1;
    getTileAt(18, 5).elevation_ = 1;
}

void Map::create(genie::ScnMap mapDescription)
{
    DBG << "tile count:" << mapDescription.tiles.size();
    DBG << "size:" << mapDescription.width << "x" << mapDescription.height;
    tiles_.clear();

    rows_ = mapDescription.width;
    cols_ = mapDescription.height;

    tiles_.resize(cols_ * rows_);

    for (size_t i = 0; i < tiles_.size(); i++) {
        const int col = i % cols_;
        const int row = i / rows_;
        genie::MapTile tile = mapDescription.tiles[i];

        getTileAt(row, col).elevation_ = tile.elevation;
        getTileAt(row, col).terrain_ = AssetManager::Inst()->getTerrain(tile.terrainID);
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
    return rows_ * Constants::TILE_SIZE;
}

int Map::width()
{
    return cols_ * Constants::TILE_SIZE;
}

float Map::elevationAt(const MapPos &position)
{
    const int tileX = position.x / Constants::TILE_SIZE;
    const int tileY = position.y / Constants::TILE_SIZE;
    const MapTile &tile = getTileAt(tileX, tileY);
    const float localX = position.x / Constants::TILE_SIZE - tileX;
    const float localY = position.y / Constants::TILE_SIZE - tileY;

    float elevation = tile.elevation_;

    switch(tile.slopes.self) {
    case Slope::NorthWestUp:
        elevation += 1. - localX;
        break;
    case Slope::SouthEastUp:
        elevation += localX;
        break;
    case Slope::SouthWestUp:
        elevation += 1. - localY;
        break;
    case Slope::NorthEastUp:
        elevation += localY;
        break;
    case Slope::EastUp:
        elevation += localX * localY;
        break;
    case Slope::WestUp:
        elevation += (1. - localX) * (1. - localY);
        break;
    case Slope::NorthUp:
        elevation += (1. - localX) * localY;
        break;
    case Slope::SouthUp:
        elevation += localX * (1. - localY);
        break;
    case Slope::NorthWestEastUp:
        elevation += 1. - localX * (1. - localY);
        break;
    case Slope::SouthWestEastUp:
        elevation += 1. - (1. - localX) * localY;
        break;
    case Slope::NorthSouthEastUp:
        elevation += 1. - (1. - localX) * (1. - localY);
        break;
    case Slope::NorthSouthWestUp:
        elevation += 1. - localX * localY;
        break;
    case Slope::Flat:
        break;
    default:
        WARN << "Unhanhdled slope" << tile.slopes.self;
        break;
    }
    return elevation * DataManager::Inst().terrainBlock().ElevHeight;
}

MapTile &Map::getTileAt(unsigned int col, unsigned int row)
{
    unsigned int index = row * cols_ + col;

    if (IS_UNLIKELY(index >= tiles_.size())) {
//        WARN << "Trying to get MapTile (" << col << "x" << row << ") out of bounds (" << cols_ << "x" << rows_ << ")";
        static MapTile nulltile;
        return nulltile;
    }

    return tiles_[index];
}

void Map::setTileAt(unsigned col, unsigned row, unsigned id)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        WARN << "Trying to get MapTile out of range!";
        return;
    }

    tiles_[index].terrain_ = AssetManager::Inst()->getTerrain(id);
    m_updated = true;
}

void Map::updateTileAt(const int col, const int row, unsigned id)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        WARN << "Trying to get MapTile out of range!";
        return;
    }

    tiles_[index].terrain_ = AssetManager::Inst()->getTerrain(id);

    for (int col_ = std::max(col - 1, 0); col_ < std::min(col + 2, cols_); col_++) {
        for (int row_ = std::max(row - 1, 0); row_ < std::min(row + 2, rows_); row_++) {
            updateTileBlend(col_, row_);
        }
    }

    m_updated = true;
}

void Map::removeEntityAt(unsigned int col, unsigned int row, const int entityId)
{
    MapTile &tile = getTileAt(col, row);

    std::vector<std::weak_ptr<Entity>>::iterator it=tile.entities.begin();
    for (;it!=tile.entities.end(); it++) {
        if (!it->expired() && it->lock()->id == entityId) {
            tile.entities.erase(it);
            break;
        }
    }
}

void Map::addEntityAt(unsigned int col, unsigned int row, const EntityPtr &entity)
{
    // just to be sure
    removeEntityAt(col, row, entity->id);

    getTileAt(col, row).entities.push_back(entity);
}

void Map::updateMapData()
{
    TIME_THIS;

    for (MapTile &tile : tiles_) {
        tile.reset();
    }

    for (int col = 0; col < cols_; col++) {
        for (int row = 0; row < rows_; row++) {
            updateTileBlend(col, row);
        }
    }

    TIME_TICK;
    for (int col = 0; col < cols_; col++) {
        for (int row = 0; row < rows_; row++) {
            updateTileSlopes(col, row);
        }
    }
    m_updated = true;
}

enum Direction : uint8_t {
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

void Map::updateTileBlend(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    const genie::Terrain &tileData = tile.terrain_->data();

//    if (tileData.SLP < 0) {
//        log.error("Invalid tile data");
//        return;
//    }

    int32_t tileId = tile.terrain_->id;

    std::unordered_map<uint8_t, int> blendDirections;
    std::unordered_set<uint8_t> neighborIds;

    std::unordered_map<uint8_t, int32_t> blendPriorities;

    std::unordered_map<uint8_t, TerrainPtr> neighborTerrains;

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
            if (neighbor.elevation_ == -1) {
                continue;
            }

            if (neighbor.elevation_ > tile.elevation_) {
                neighborsAbove |= direction;
            } else if (neighbor.elevation_ < tile.elevation_) {
                neighborsBelow |= direction;
            }

            const int32_t neighborId = neighbor.terrain_->id;
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

    if (neighborsAbove & West && neighborsAbove & South) {
        tile.slopes.self = Slope::NorthWestEastUp;
    } else if (neighborsAbove & East && neighborsAbove & North) {
        tile.slopes.self = Slope::SouthWestEastUp;
    } else if (neighborsAbove & West && neighborsAbove & North) {
        tile.slopes.self = Slope::NorthSouthWestUp;
    } else if (neighborsAbove & East && neighborsAbove & South) {
        tile.slopes.self = Slope::NorthSouthEastUp;
    } else if (neighborsAbove == NorthWest) {
        tile.slopes.self = Slope::WestUp;
    } else if (neighborsAbove == NorthEast) {
        tile.slopes.self = Slope::SouthUp;
    } else if (neighborsAbove == SouthWest) {
        tile.slopes.self = Slope::NorthUp;
    } else if (neighborsAbove == SouthEast) {
        tile.slopes.self = Slope::EastUp;
    } else if (neighborsAbove & North) {
        tile.slopes.self = Slope::SouthWestUp;
    } else if (neighborsAbove & South) {
        tile.slopes.self = Slope::NorthEastUp ;
    } else if (neighborsAbove & East) {
        tile.slopes.self = Slope::SouthEastUp;
    } else if (neighborsAbove & West) {
        tile.slopes.self = Slope::NorthWestUp;
    }

    tile.yOffset = DataManager::datFile().TerrainBlock.TileSizes[tile.slopes.self.toGenie()].DeltaY;

    if (tile.slopes.self != Slope::Flat) {
        return;
    }

    if (neighborIds.empty()) {
        return;
    }

    std::vector<uint8_t> idsToDraw(neighborIds.begin(), neighborIds.end());
    std::sort(idsToDraw.begin(), idsToDraw.end(), [&](const uint8_t a, const uint8_t b){
        return blendPriorities[a] < blendPriorities[b];
    });

    tile.textures.push_back(tile.terrain_->texture(tileX, tileY));

    for (const uint8_t id : idsToDraw) {
        Blend blends;

        uint8_t direction = blendDirections[id];
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

        const TerrainPtr &neighbor = neighborTerrains[id];
        blends.blendMode = Terrain::blendMode(tileData.BlendType, neighbor->data().BlendType);
        blends.terrainId = neighbor->id;
        blends.x = tileX;
        blends.y = tileX;

        tile.blends.push_back(blends);
    }
}

void Map::updateTileSlopes(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    if (tile.slopes.self == Slope::Flat) {
        return;
    }
    const genie::Terrain &tileData = tile.terrain_->data();
    if (tileData.SLP == -1) {
        tile.slopes.self = Slope::Flat;
        return;
    }

    tile.slopes.north = slopeAt(tileX - 1, tileY + 1);
    tile.slopes.south = slopeAt(tileX + 1, tileY - 1);

    tile.slopes.west = slopeAt(tileX - 1, tileY - 1);
    tile.slopes.east = slopeAt(tileX + 1, tileY + 1);

    tile.slopes.southWest = slopeAt(tileX, tileY - 1);
    tile.slopes.southEast = slopeAt(tileX + 1, tileY);

    tile.slopes.northWest = slopeAt(tileX - 1, tileY);
    tile.slopes.northEast = slopeAt(tileX, tileY + 1);

    // Preload
//    tile.terrain_->slopedImage(tile.slopes, tileX, tileY);
}

Slope Map::slopeAt(const int x, const int y)
{
    if (IS_UNLIKELY(x < 0 || y < 0 || x >= cols_ || y >= rows_)) {
        return Slope::Flat;
    }

    return getTileAt(x, y).slopes.self;
}

