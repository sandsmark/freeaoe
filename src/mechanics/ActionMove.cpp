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

#include "ActionMove.h"
#include <Engine.h>

#include <unordered_set>
#include <queue>
#include "CompMapObject.h"
#include "CompUnitData.h"
#include "resource/DataManager.h"
#include "global/Constants.h"

namespace { // anonymous namespace, don't export this
struct PathPoint {
    PathPoint() = default;
    PathPoint(const PathPoint &other) :
        x(other.x),
        y(other.y),
        pathLength(other.pathLength),
        distance(other.distance)
    {
    }

    PathPoint(int _x, int _y) : x(_x), y(_y) {}

    int x = 0;
    int y = 0;
    float pathLength = 0;
    float distance = 0;

    bool operator==(const PathPoint &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const PathPoint &other) const {
        return (x != other.x) && (y != other.y);
    }
    bool operator<(const PathPoint &other) const {
        return (other.distance + other.pathLength) < (distance + pathLength);
    }
};
}

template<> struct std::hash<PathPoint>
{
    std::size_t operator()(const PathPoint& point) const
    {
        return point.y * 255 * 96 + point.x;
    }
};

namespace act {

static const float PATHFINDING_HEURISTIC_WEIGHT = 1.;

MoveOnMap::MoveOnMap(MapPos destination, MapPtr map, Unit::Ptr unit, UnitManager *unitManager) :
    IAction(Type::Move),
    m_map(map),
    target_reached(false),
    m_unitManager(unitManager),
    m_unit(unit)
{
    dest_ = destination;
    last_update_ = 0;
}

MoveOnMap::~MoveOnMap()
{
}

bool MoveOnMap::update(Time time)
{
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "My unit got deleted";
        return false;
    }

    if (target_reached || m_path.empty()) {
        target_reached = true;
        unit->removeAction(this);
        return false;
    }

    if (!last_update_) {
        last_update_ = time;
        return true;
    }


    float elapsed = time - last_update_;
    last_update_ = time;
    float movement = elapsed * speed_ * 0.15;


    float distanceLeft = std::hypot(m_path.back().x - unit->position.x, m_path.back().y - unit->position.y);
    while (distanceLeft <= movement && !m_path.empty()) {
        m_path.pop_back();
        if (m_path.empty()) {
            break;
        }
        distanceLeft = std::hypot(m_path.back().x - unit->position.x, m_path.back().y - unit->position.y);
    }

    if (m_path.empty()) {
        target_reached = true;
        unit->removeAction(this);
        return false;
    }

    MapPos nextPos = m_path.back();
    if (!isPassable(nextPos.x, nextPos.y)) {
        m_path = findPath(unit->position, dest_, 1);
        if (m_path.empty()) {
            m_path = findPath(unit->position, dest_, 20);
            if (m_path.empty()) {
                target_reached = true;
                unit->removeAction(this);
            }
        }

        return false;
    }

    const float direction = std::atan2(nextPos.y - unit->position.y, nextPos.x - unit->position.x);
    MapPos newPos = unit->position;
    newPos.x += cos(direction) * movement;
    newPos.y += sin(direction) * movement;

    if (!isPassable(newPos.x, newPos.y)) {
        newPos = nextPos;
    }


    ScreenPos sourceScreen = unit->position.toScreen();
    ScreenPos targetScreen = newPos.toScreen();
    unit->setAngle(std::atan2((targetScreen.y - sourceScreen.y), (targetScreen.x - sourceScreen.x)));
    newPos.z = m_map->elevationAt(newPos);

    unit->position = newPos;

    if (std::hypot(newPos.x - dest_.x, newPos.y - dest_.y) < movement) {
        target_reached = true;
        unit->removeAction(this);
    }

    return true;
}

std::shared_ptr<MoveOnMap> MoveOnMap::moveUnitTo(Unit::Ptr unit, MapPos destination, MapPtr map, UnitManager *unitManager)
{
    if (!unit->data.Speed) {
        DBG << "Handed unit that can't move" << unit->readableName;
        return nullptr;
    }
    std::shared_ptr<MoveOnMap> action (new act::MoveOnMap(destination, map, unit, unitManager));

    action->m_terrainMoveMultiplier = DataManager::Inst().getTerrainRestriction(unit->data.TerrainRestriction).PassableBuildableDmgMultiplier;
    action->speed_ = unit->data.Speed;

    action->m_path = action->findPath(unit->position, destination, 1);

    // Try coarser
    // Uglier, but hopefully faster
    if (action->m_path.empty()) {
        action->m_path = action->findPath(unit->position, destination, 5);
    }

    if (action->m_path.empty()) {
        action->m_path = action->findPath(unit->position, destination, 20);
    }

    if (action->m_path.empty()) {
        DBG << "Failed to find path for" << unit->readableName;
        return nullptr;
    }

    return action;
}


std::vector<MapPos> MoveOnMap::findPath(const MapPos &start, const MapPos &end, int coarseness)
{
    sf::Clock clock;

    std::vector<MapPos> path;

    int startX = std::round(start.x / coarseness);
    int startY = std::round(start.y / coarseness);
    if (!isPassable(startX * coarseness, startY * coarseness)) {
        WARN << "handed unpassable start";
        return path;
    }

    int endX = std::round(end.x / coarseness);
    int endY = std::round(end.y / coarseness);
    if (!isPassable(endX * coarseness, endY * coarseness)) {
        WARN << "handed unpassable target";
        return path;
    }

    PathPoint currentPosition(startX, startY);

    std::unordered_map<PathPoint, PathPoint> cameFrom;

    // STL is a steaming pile of shit
    std::priority_queue<PathPoint> queue;
    currentPosition.distance = std::sqrt((startX - endX) * (startX - endX) + (startY - endY) * (startY - endY));
    currentPosition.pathLength = 0;
    queue.push(currentPosition);

    std::unordered_set<PathPoint> visited;
    visited.insert(currentPosition);

    PathPoint pathPoint;
    int tried = 0;
    while (!queue.empty()) {
        tried++;
        pathPoint = queue.top();
        queue.pop();

        if (pathPoint.x == endX && pathPoint.y == endY) {
            break;
        }

        visited.insert(pathPoint);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (!dx && !dy) {
                    continue;
                }

                const int nx = pathPoint.x + dx;
                const int ny = pathPoint.y + dy;
                PathPoint neighbor(nx, ny);

                if (!isPassable(nx * coarseness, ny * coarseness)) {
                    visited.insert(neighbor);
                    continue;
                }

                if (visited.count(neighbor)) {
                    continue;
                }

                if (cameFrom.find(neighbor) != cameFrom.end()) {
                    if ((cameFrom[neighbor].pathLength < pathPoint.pathLength)) {
                        continue;
                    }
                }

//                neighbor.pathLength = pathPoint.pathLength + 1.; // chebychev
                neighbor.pathLength = pathPoint.pathLength + std::abs(dx) + std::abs(dy); // manhattan
//                neighbor.pathLength = pathPoint.pathLength + std::hypot(dx, dy); // euclidian
//                neighbor.distance = std::abs(nx - endX) + std::abs(ny - endY); // manhattan
                neighbor.distance = std::hypot(nx - endX, ny - endY) * PATHFINDING_HEURISTIC_WEIGHT;
                queue.push(neighbor);


                cameFrom[neighbor] = pathPoint;
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 50) {
            WARN << "Timeout while pathing (" << tried << "nodes in" << clock.getElapsedTime().asMilliseconds() << "ms)";
            return path;
        }
    }
    DBG << "walked" << tried << "nodes in" << clock.getElapsedTime().asMilliseconds() << "ms";

    if (cameFrom.find(pathPoint) == cameFrom.end()) {
        WARN << "Failed to find path from" << startX << "," << startY << "to" << endX << "," << endY;
        return path;
    }

    path.push_back(end);

    while (cameFrom[pathPoint].x != startX || cameFrom[pathPoint].y != startY) {
        pathPoint = cameFrom[pathPoint];
        path.push_back(MapPos(pathPoint.x * coarseness, pathPoint.y * coarseness));

        if (cameFrom.find(pathPoint) == cameFrom.end()) {
            WARN << "invalid path, failed to find previous step";
            return path;
        }
    }

    return path;
    std::vector<MapPos> cleanedPath;
    cleanedPath.push_back(path[0]);
    for (int i=1; i<path.size() - 1; i++) {
        double lastAngle = std::atan2((path[i].y - path[i-1].y), (path[i].x - path[i-1].x));
        double nextAngle = std::atan2((path[i+1].y - path[i].y), (path[i+1].x - path[i].x));
        if (lastAngle != nextAngle) {
            cleanedPath.push_back(path[i]);
        }
    }
    cleanedPath.push_back(path.back());

    DBG << cleanedPath.size() << "/" << path.size();

    return cleanedPath;

}

bool MoveOnMap::isPassable(const int x, const int y)
{
    const int tileX = x / Constants::TILE_SIZE;
    const int tileY = y / Constants::TILE_SIZE;
    if (IS_UNLIKELY(tileX < 0 || tileY < 0 || tileX >= m_map->getCols() || tileY >= m_map->getRows())) {
        return false;
    }

    if (m_terrainMoveMultiplier[m_map->getTileAt(tileX, tileY).terrainId()] == 0) {
        return false;
    }

    const MapPos mapPos(x, y);
    Unit::Ptr unit = m_unit.lock();
    for (const Unit::Ptr &otherUnit : m_unitManager->units()) {
        if (otherUnit.get() == unit.get()) {
            continue;
        }

        if (otherUnit->data.Size.z == 0) {
            continue;
        }

        const float xDistance = std::abs(otherUnit->position.x - mapPos.x);
        const float yDistance = std::abs(otherUnit->position.y - mapPos.y);
        const float xSize = (otherUnit->data.Size.x + unit->data.Size.x) * Constants::TILE_SIZE;
        const float ySize = (otherUnit->data.Size.y + unit->data.Size.y) * Constants::TILE_SIZE;

//        if ( <  && std::abs(other->position.y - mapPos.y) < (otherUnit->data.Size[1]  + unit->data.Size[1]) * Constants::TILE_SIZE) {
        if (xDistance < xSize && yDistance < ySize) {
//            DBG << unit->readableName << " " << other->readableName;
//            DBG << "x: " << xDistance << " " << xSize;
//            DBG << "y: " << yDistance << " " << ySize;
            return false;
        }
    }

    return true;
}

}
