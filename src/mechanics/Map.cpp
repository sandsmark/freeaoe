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
#include "core/Constants.h"
#include "core/Utility.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <resource/AssetManager.h>
#include <resource/Resource.h>
#include <mechanics/Unit.h>

#include <genie/resource/SlpFrame.h>

#include <SFML/Graphics/Shape.hpp>

#include <ctime>
#include <cstdlib>
#include <stdexcept>
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

void Map::setupBasic()
{
    cols_ = 20;
    rows_ = 20;

    tiles_.clear();

    MapTile grass;
    grass.elevation = 0;
    grass.terrainId = 0;

    tiles_.resize(cols_ * rows_, grass);
    m_tileUnits.resize(cols_ * rows_);

    for (int i=6; i<10; i++) {
        getTileAt(0, i).terrainId = 2;
        getTileAt(1, i).terrainId = 2;
        getTileAt(2, i).terrainId = 2;
    }
    for (int i=4; i<6; i++) {
        getTileAt(i, 10).terrainId = 1;
    }

    for (int i=3; i<6; i++) {
        getTileAt(14, i).elevation = 1;
    }

    for (int i=3; i<6; i++) {
        getTileAt(15, i).elevation = 1;
    }

    getTileAt(13, 4).elevation = 1;
    getTileAt(16, 4).elevation = 1;
    getTileAt(13, 4).terrainId = 2;
    getTileAt(17, 4).elevation = 1;
    getTileAt(18, 5).elevation = 1;
}

void Map::setupAllunitsMap()
{
    cols_ = 30;
    rows_ = 30;

    tiles_.clear();

    MapTile water;
    water.elevation = 0;
    water.terrainId = 1;

    tiles_.resize(cols_ * rows_, water);
    m_tileUnits.resize(cols_ * rows_);

    // add some grass
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 15; j++) {
            getTileAt(i, j).elevation = 0;
            getTileAt(i, j).terrainId = 0;
        }
    }

    // creates hill
    auto elevate = [&] (int x, int y, int cols, int rows) {
        for (int i = x - 1; i < x + cols + 1; i++) {
            getTileAt(i, y - 1).elevation = 1;
            getTileAt(i, y - 1).terrainId = 0;
        }

        for (int i = y; i < y + rows; i++) {
            getTileAt(x-1, i).elevation = 1;
            getTileAt(x-1, i).terrainId = 0;

            for (int j = x; j < x + cols; j++) {

                getTileAt(j, i).elevation = 2;
                getTileAt(j, i).terrainId = 0;

            }
            getTileAt(x+cols, i).elevation = 1;
            getTileAt(x+cols, i).terrainId = 0;
        }

        for (int i = x - 1; i < x + cols + 1; i++) {
            getTileAt(i, y + rows).elevation = 1;
            getTileAt(i, y + rows).terrainId = 0;
        }
    };

    elevate(5, 5, 10, 5);
    elevate(5, 17, 10, 5);
    elevate(5, 14, 1, 1);
}

void Map::create(genie::ScnMap mapDescription)
{
    DBG << "tile count:" << mapDescription.tiles.size();
    DBG << "size:" << mapDescription.width << "x" << mapDescription.height;
    tiles_.clear();

    rows_ = mapDescription.width;
    cols_ = mapDescription.height;

    tiles_.resize(cols_ * rows_);
    m_tileUnits.resize(cols_ * rows_);

    for (size_t i = 0; i < tiles_.size(); i++) {
        const int col = i % cols_;
        const int row = i / rows_;
        genie::MapTile tile = mapDescription.tiles[i];

        getTileAt(row, col).elevation = tile.elevation;
        getTileAt(row, col).terrainId = tile.terrainID;
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

    float elevation = tile.elevation;

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

    tiles_[index].terrainId = id;
    m_updated = true;
}

void Map::updateTileAt(const int col, const int row, unsigned id)
{
    unsigned int index = row * cols_ + col;

    if (index >= tiles_.size()) {
        WARN << "Trying to get MapTile out of range!";
        return;
    }

    tiles_[index].terrainId = id;
    tiles_[index].frame = AssetManager::Inst()->getTerrain(tiles_[index].terrainId)->coordinatesToFrame(col, row);
    for (int col_ = std::max(col - 1, 0); col_ < std::min(col + 2, cols_); col_++) {
        for (int row_ = std::max(row - 1, 0); row_ < std::min(row + 2, rows_); row_++) {
            getTileAt(col_, row_).reset();
        }
    }

    for (int col_ = std::max(col - 1, 0); col_ < std::min(col + 2, cols_); col_++) {
        for (int row_ = std::max(row - 1, 0); row_ < std::min(row + 2, rows_); row_++) {
            updateTileBlend(col_, row_);
        }
    }
    for (int col_ = std::max(col - 1, 0); col_ < std::min(col + 2, cols_); col_++) {
        for (int row_ = std::max(row - 1, 0); row_ < std::min(row + 2, rows_); row_++) {
            updateTileSlopes(col, row);
        }
    }

    m_updated = true;
}

void Map::removeEntityAt(unsigned int col, unsigned int row, const int entityId)
{
    unsigned int index = row * cols_ + col;

    if (IS_UNLIKELY(index >= m_tileUnits.size())) {
        WARN << "Trying to remove unit out of range" << col << row;
        return;
    }

    std::vector<std::weak_ptr<Entity>>::iterator it=m_tileUnits[index].begin();
    while (it != m_tileUnits[index].end()) {
        if (it->expired()) {
            it = m_tileUnits[index].erase(it);
            continue;
        }
        EntityPtr entity = it->lock();
        if (!entity) {
            it = m_tileUnits[index].erase(it);
            continue;
        }

        if (entity->id == entityId) {
            m_tileUnits[index].erase(it);

            emit(Signals::UnitsChanged);

            return;
        }

        it++;
    }
}

void Map::addEntityAt(unsigned int col, unsigned int row, const EntityPtr &entity)
{
    unsigned int index = row * cols_ + col;

    if (IS_UNLIKELY(index >= m_tileUnits.size())) {
        WARN << "Trying to add unit out of range" << col << row;
        return;
    }

    // just to be sure
    removeEntityAt(col, row, entity->id);

    m_tileUnits[index].push_back(entity);

    emit(Signals::UnitsChanged);

    if (!entity->isUnit()) {
        return;
    }

    Unit::Ptr unit = Entity::asUnit(entity);
    const int newTerrain = unit->data()->Building.FoundationTerrainID;

    if (newTerrain < 0) {
        return;
    }

    const int width = unit->data()->Size.x;
    const int height = unit->data()->Size.y;
    for (int x = 0; x < width*2; x++) {
        for (int y = 0; y < height*2; y++) {
            setTileAt(col + x - width, row + y - width, newTerrain);
        }
    }
}

const std::vector<std::weak_ptr<Entity> > &Map::entitiesAt(unsigned int col, unsigned int row) const
{
    unsigned int index = row * cols_ + col;

    if (IS_UNLIKELY(index >= m_tileUnits.size())) {
        WARN << "Trying to get MapTile out of range!";
        static const std::vector<std::weak_ptr<Entity>> nullVector;
        return nullVector;
    }

    return m_tileUnits[index];
}

const std::vector<std::weak_ptr<Entity>> Map::entitiesBetween(int firstCol, int firstRow, int lastCol, int lastRow) const
{
    std::vector<std::weak_ptr<Entity>> entities;
    for (int col=firstCol; col<lastCol; col++) {
        for (int row=firstRow; row<lastRow; row++) {
            entities.insert(entities.end(), entitiesAt(col, row).begin(), entitiesAt(col, row).end());
        }
    }
    return entities;
}

void Map::updateMapData()
{
    TIME_THIS;

    for (int col = 0; col < cols_; col++) {
        for (int row = 0; row < rows_; row++) {
            MapTile &tile = tiles_[row * cols_ + col];
            tile.reset();
            tile.frame = AssetManager::Inst()->getTerrain(tile.terrainId)->coordinatesToFrame(col, row);
        }
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

    emit(Signals::TerrainChanged);
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
    const genie::Terrain &tileData = DataManager::Inst().getTerrain(tile.terrainId);

    int32_t tileId = tile.terrainId;

    std::unordered_map<uint8_t, int> blendDirections;
    std::unordered_set<uint8_t> neighborIds;

    std::unordered_map<uint8_t, int32_t> blendPriorities;

//    std::unordered_map<uint8_t, genie::Terrain*> neighborTerrains;

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
            if (neighbor.elevation == -1) {
                continue;
            }

            if (neighbor.elevation > tile.elevation) {
                neighborsAbove |= direction;
            } else if (neighbor.elevation < tile.elevation) {
                neighborsBelow |= direction;
            }

            const int32_t neighborId = neighbor.terrainId;
            if (tileId == neighborId) {
                continue;
            }

            const genie::Terrain &neighborData = DataManager::Inst().getTerrain(neighbor.terrainId);

            if (tileData.BlendPriority >= neighborData.BlendPriority) {
                continue;
            }
            blendPriorities[neighborId] = neighborData.BlendPriority;
//            neighborTerrains[neighborId] = &neighborData;

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

    tile.yOffset = DataManager::Inst().terrainBlock().TileSizes[tile.slopes.self.toGenie()].DeltaY;

//    if (tile.slopes.self != Slope::Flat) {
//        return;
//    }

    if (neighborIds.empty()) {
        return;
    }

    std::vector<uint8_t> idsToDraw(neighborIds.begin(), neighborIds.end());
    std::sort(idsToDraw.begin(), idsToDraw.end(), [&](const uint8_t a, const uint8_t b){
        return blendPriorities[a] < blendPriorities[b];
    });

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

        const genie::Terrain &neighbor = DataManager::Inst().getTerrain(id); //neighborTerrains[id];

        blends.blendMode = Terrain::blendMode(tileData.BlendType, neighbor.BlendType);
        blends.terrainId = id;
        blends.frame = AssetManager::Inst()->getTerrain(id)->coordinatesToFrame(tileX, tileY);

        tile.blends.push_back(blends);
    }
}

void Map::updateTileSlopes(int tileX, int tileY)
{
    MapTile &tile = getTileAt(tileX, tileY);
    if (tile.slopes.self == Slope::Flat) {
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

