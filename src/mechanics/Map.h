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

#pragma once

#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "MapTile.h"
#include "core/Constants.h"
#include "core/SignalEmitter.h"
#include "core/Utility.h"
#include "mechanics/Entity.h"

namespace genie {
class ScnMap;
}  // namespace genie
struct MapPos;

struct Entity;
using EntityPtr = std::shared_ptr<Entity>;

class MapNode
{
public:
    unsigned int row, col;
    int8_t elevation;
    int32_t x_pos, y_pos, z_pos;
};

class Map : public SignalEmitter<Map>
{
public:
    enum class Signals {
        UnitsChanged,
        TerrainChanged
    };

    enum MapSize {
        Tiny = 72,
        Small = 96,
        Medium = 120,
        Large = 144,
        Huge = 200,
        Gigantic = Constants::MAP_MAX_SIZE,
    };
    /*
   * A tiny-size map? 72 x 72.
   * A small-size map? 96 x 96.
   * A medium-size map? 120 x 120.
   * A large-size map? 144 x 144.
   * A huge-size map? 200 x 200.
   * A gigantic-size map? 255 x 255.
   */

    Map();
    virtual ~Map();

    void setupBasic() noexcept;
    void setupAllunitsMap() noexcept;

    void create(const genie::ScnMap &mapDescription) noexcept;

    inline int getRows() const noexcept { return rows_; }
    inline int getCols() const noexcept { return cols_; }

    inline int height() const noexcept { return rows_ * Constants::TILE_SIZE; }
    inline int width() const noexcept { return cols_ * Constants::TILE_SIZE; }

    float elevationAt(const MapPos &position) noexcept;

    const MapTile &getTileAt(unsigned int col, unsigned int row) const noexcept {
        const unsigned int index = row * cols_ + col;
        if (IS_UNLIKELY(index >= tiles_.size())) {
            assert(col < cols_ && row < rows_);
            return MapTile::null;
        }
        return tiles_.at(index);
    }

    MapTile &getTileAt(unsigned int col, unsigned int row) noexcept {
        const unsigned int index = row * cols_ + col;
        if (IS_UNLIKELY(index >= tiles_.size())) {
            assert(col < cols_ && row < rows_);
            return MapTile::null;
        }
        return tiles_.at(index);
    }

    void setTileAt(unsigned col, unsigned row, unsigned id) noexcept;
    void updateTileAt(const int col, const int row, unsigned id) noexcept;

    void removeEntityAt(unsigned int col, unsigned int row, const int entityId) noexcept;
    void addEntityAt(int col, int row, const EntityPtr &entity) noexcept;

    inline const std::vector<std::weak_ptr<Entity>> &entitiesAt(unsigned int col, unsigned int row) const noexcept {
        unsigned int index = row * cols_ + col;
        if (IS_UNLIKELY(index >= m_tileUnits.size())) {
            static const std::vector<std::weak_ptr<Entity>> nullVector;
            return nullVector;
        }
        return m_tileUnits[index];
    }

    inline const std::vector<std::weak_ptr<Entity>> entitiesBetween(int firstCol, int firstRow, int lastCol, int lastRow) const noexcept {
        std::vector<std::weak_ptr<Entity>> entities;
        for (int col=firstCol; col<lastCol; col++) {
            for (int row=firstRow; row<lastRow; row++) {
                entities.insert(entities.end(), entitiesAt(col, row).begin(), entitiesAt(col, row).end());
            }
        }
        return entities;
    }

    void updateMapData() noexcept;

    bool tilesUpdated() const noexcept { return m_updated; }
    void flushDirty() noexcept { m_updated = false; }

    inline bool isValidTile(const unsigned col, const unsigned row) const {
        if (IS_UNLIKELY(row * cols_ + col >= tiles_.size())) {
            return false;
        } else {
            return true;
        }
    }
    inline bool isValidPosition(const MapPos &position) {
        return position.x >= 0 && position.y >= 0 && position.x < width() && position.y < height();
    }

private:
    void updateTileBlend(int tileX, int tileY) noexcept;
    void updateTileSlopes(int tileX, int tileY) noexcept;

    inline Slope slopeAt(const int col, const int row) const noexcept {
        const unsigned int index = row * cols_ + col;
        if (IS_UNLIKELY(index >= tiles_.size())) {
            return Slope::Flat;
        }
        return tiles_[index].slopes.self;
    }

    // cols_ = x, rows_ = y
    int rows_ = 0, cols_ = 0;

    typedef std::vector<MapTile> MapTileArray;
    MapTileArray tiles_;

    std::vector<std::vector<std::weak_ptr<Entity>>> m_tileUnits;

    bool m_updated = false;
};

typedef std::shared_ptr<Map> MapPtr;

