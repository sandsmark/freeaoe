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

#include <global/Logger.h>
#include <genie/dat/Terrain.h>
#include <global/Types.h>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <map>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <core/Entity.h>
#include <resource/Terrain.h>
#include <genie/script/scn/MapDescription.h>

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

struct MapTile
{
    void reset() {
        yOffset = 0;
        slopes = TileSlopes();
        textures.clear();
        blends.clear();
    }

    uint32_t terrainId() const {
        return terrain_->id;
    }

    unsigned int elevation_;
    int yOffset;
    TerrainPtr terrain_;

    std::vector<sf::Texture> textures;
    std::vector<Blend> blends;
    std::vector<EntityPtr> entities;

    TileSlopes slopes;
};

class Map
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

    Map();
    virtual ~Map();

    void setUpSample();

    void create(genie::ScnMap mapDescription);

    int getRows();
    int getCols();

    int height();
    int width();

    float elevationAt(const MapPos &position);

    MapTile &getTileAt(unsigned int col, unsigned int row);
    void setTileAt(unsigned col, unsigned row, unsigned id);
    void updateTileAt(const int col, const int row, unsigned id);

    void removeEntityAt(unsigned int col, unsigned int row, const EntityPtr &entity);
    void addEntityAt(unsigned int col, unsigned int row, const EntityPtr &entity);

    void updateMapData();

    bool tilesUpdated() const { return m_updated; }
    void flushDirty() { m_updated = false; }

private:
    void updateTileBlend(int tileX, int tileY);
    void updateTileSlopes(int tileX, int tileY);
    Slope slopeAt(const int x, const int y);

    // cols_ = x, rows_ = y
    int rows_, cols_;

    typedef std::vector<MapTile> MapTileArray;
    MapTileArray tiles_;

    bool m_updated = false;
};

typedef std::shared_ptr<Map> MapPtr;

