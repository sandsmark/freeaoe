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

#ifndef ACTIONMOVE_H
#define ACTIONMOVE_H

#include "core/IAction.h"
#include "core/Entity.h"
#include "Map.h"
#include <genie/dat/TerrainRestriction.h>

class UnitManager;

namespace act {

class MoveOnMap : public IAction
{

public:
    virtual ~MoveOnMap();

    virtual bool update(Time time);

    static std::shared_ptr<MoveOnMap> moveUnitTo(Unit::Ptr unit, MapPos destination, MapPtr map, UnitManager *unitManager);

private:
    std::vector<MapRect> getOtherUnits(const Unit::Ptr &unit);

    MoveOnMap(MapPos destination, MapPtr map, Unit::Ptr unit, UnitManager *unitManager);

    std::vector<MapPos> findPath(const MapPos &start, const MapPos &end, int coarseness);
    bool isPassable(const int x, const int y, const int width, const int height, const std::vector<MapRect> &others);


    MapPtr m_map;
    MapPos dest_;
    std::vector<MapPos> m_path;
    UnitManager *m_unitManager;
    MapPos m_currentTarget;
    std::vector<float> m_terrainMoveMultiplier;
    float speed_;

    Time last_update_;

    bool target_reached;
    std::weak_ptr<Unit> m_unit;
};
}

#endif // ACTIONMOVE_H
