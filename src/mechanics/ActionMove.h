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

#include "core/IAction.h"
#include "Unit.h"
#include "Map.h"
#include <genie/dat/TerrainRestriction.h>
#include <bitset>
#include "global/Constants.h"

class ActionMove : public IAction
{

public:
#ifdef DEBUG
    static std::vector<MapPos> testedPoints;
#endif
    virtual ~ActionMove();

    UpdateResult update(Time time) override;

    static std::shared_ptr<ActionMove> moveUnitTo(const Unit::Ptr &unit, MapPos destination, const MapPtr &map, UnitManager *unitManager);

private:
    ActionMove(MapPos destination, const MapPtr &map, const Unit::Ptr &unit, UnitManager *unitManager);

    MapPos findClosestWalkableBorder(const MapPos &target, int coarseness);

    std::vector<MapPos> findPath(MapPos start, MapPos end, int coarseness);
    bool isPassable(const int x, const int y, int coarseness = 0);

    void updatePath();

    MapPtr m_map;
    MapPos dest_;
    std::vector<MapPos> m_path;
    MapPos m_currentTarget;
    std::vector<float> m_terrainMoveMultiplier;
    float speed_;

    bool target_reached;
    std::bitset<Constants::TILE_SIZE * Map::Gigantic * Map::Gigantic> m_passable;
    std::bitset<Constants::TILE_SIZE * Map::Gigantic * Map::Gigantic> m_passableCached;
    bool m_passableDirty = false;
};

