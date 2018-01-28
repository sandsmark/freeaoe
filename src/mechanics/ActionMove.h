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

namespace comp {
class MapObject;
}

namespace act {

class MoveOnMap : public IAction
{

public:
    virtual ~MoveOnMap();

    virtual bool update(Time time);

    static bool moveUnitTo(EntityPtr entity, MapPos destination, MapPtr map);

private:
    MoveOnMap(MapPos destination, MapPtr map);

    std::vector<MapPos> findPath(const MapPos &start, const MapPos &end, int coarseness);
    bool isPassable(int x, int y);

    static Logger &log;

    MapPtr m_map;
    MapPos dest_;
    std::vector<MapPos> m_path;
    std::shared_ptr<comp::MapObject> m_mapObject;
    MapPos m_currentTarget;
    std::vector<float> m_terrainMoveMultiplier;
    float speed_;

    Time last_update_;

    bool target_reached;
};
}

#endif // ACTIONMOVE_H
