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

namespace { // anonymous namespace, don't export this
struct PathPoint {
    PathPoint() = default;
    PathPoint(const PathPoint &other) :
    x(other.x),
    y(other.y),
    pathLength(other.pathLength),
    distance(other.distance){

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
        return point.x * 10 + point.y;
    }
};

namespace act {

Logger &MoveOnMap::log = Logger::getLogger("freeaoe.MoveOnMap");

static const float PATHFINDING_HEURISTIC_WEIGHT = 1.;

MoveOnMap::MoveOnMap(MapPos destination, MapPtr map) :
    m_map(map),
    target_reached(false)
{
    dest_ = destination;
    last_update_ = 0;

}

MoveOnMap::~MoveOnMap()
{
}

bool MoveOnMap::update(Time time)
{
    if (target_reached || m_path.empty()) {
        target_reached = true;
        m_mapObject->moving_ = false;
        return false;
    }

    if (!last_update_) {
        last_update_ = time;
        return true;
    }


    float elapsed = time - last_update_;
    last_update_ = time;
    float movement = elapsed * speed_ * 0.15;


    float distanceLeft = std::hypot(m_path.back().x - m_mapObject->getPos().x, m_path.back().y - m_mapObject->getPos().y);
    while (distanceLeft <= movement && !m_path.empty()) {

        m_path.pop_back();
        distanceLeft = std::hypot(m_path.back().x - m_mapObject->getPos().x, m_path.back().y - m_mapObject->getPos().y);
    }
    if (m_path.empty()) {
        target_reached = true;
        m_mapObject->moving_ = false;
        return false;
    }

    MapPos nextPos = m_path.back();

    const float direction = std::atan2(nextPos.y - m_mapObject->getPos().y, nextPos.x - m_mapObject->getPos().x);
    MapPos newPos = m_mapObject->getPos();
    newPos.x += cos(direction) * movement;
    newPos.y += sin(direction) * movement;

    ScreenPos sourceScreen = m_mapObject->getPos().toScreen();
    ScreenPos targetScreen = newPos.toScreen();
    m_mapObject->angle_ = std::atan2((targetScreen.y - sourceScreen.y), (targetScreen.x - sourceScreen.x));

    m_mapObject->setPos(newPos);

    if (std::hypot(newPos.x - dest_.x, newPos.y - dest_.y) < movement) {
        target_reached = true;
        m_mapObject->moving_ = false;
    }

    return true;
}

bool MoveOnMap::moveUnitTo(EntityPtr entity, MapPos destination, MapPtr map)
{
    comp::UnitDataPtr gunit = entity->getComponent<comp::UnitData>(comp::UNIT_DATA);
    if (!gunit->getData().Speed) {
        log.info("Handled unit that can't move %s", gunit->readableName().c_str());
        return false;
    }
    std::shared_ptr<MoveOnMap> action(new act::MoveOnMap(destination, map));

    action->m_terrainMoveMultiplier = DataManager::Inst().getTerrainRestriction(gunit->getData().TerrainRestriction).PassableBuildableDmgMultiplier;
    action->speed_ = gunit->getData().Speed;
    action->m_mapObject = entity->getComponent<comp::MapObject>(comp::MAP_OBJECT);

    action->m_path = action->findPath(action->m_mapObject->getPos(), destination, 1);

    // Try coarser
    // Uglier, but hopefully faster
    if (action->m_path.empty()) {
        action->m_path = action->findPath(action->m_mapObject->getPos(), destination, 20);
    }

    if (action->m_path.empty()) {
        log.info("Failed to find path for %s", gunit->readableName().c_str());
        return false;
    }

    action->m_mapObject->moving_ = true;

    entity->current_action_ = action;

    return true;
}


std::vector<MapPos> MoveOnMap::findPath(const MapPos &start, const MapPos &end, int coarseness)
{
    sf::Clock clock;

    std::vector<MapPos> path;

    int startX = std::round(start.x / coarseness);
    int startY = std::round(start.y / coarseness);
    if (!isPassable(startX * coarseness, startY * coarseness)) {
        log.warn("handed unpassable start");
        return path;
    }

    int endX = std::round(end.x / coarseness);
    int endY = std::round(end.y / coarseness);
    if (!isPassable(endX * coarseness, endY * coarseness)) {
        log.warn("handed unpassable target");
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

                neighbor.pathLength = pathPoint.pathLength + 1.; // chebychev
//                neighbor.pathLength = current.pathLength + std::abs(dx) + std::abs(dy); // manhattan
//                neighbor.pathLength = pathPoint.pathLength + std::hypot(dx, dy); // euclidian
//                neighbor.distance = std::abs(nx - endX) + std::abs(ny - endY); // manhattan
                neighbor.distance = std::hypot(nx - endX, ny - endY) * PATHFINDING_HEURISTIC_WEIGHT;
                queue.push(neighbor);


                cameFrom[neighbor] = pathPoint;
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 50) {
            log.error("Timeout while pathing (%d nodes in %d ms)", tried, clock.getElapsedTime().asMilliseconds());
            return path;
        }
    }
    log.debug("walked %d nodes in %d ms", tried, clock.getElapsedTime().asMilliseconds());

    if (cameFrom.find(pathPoint) == cameFrom.end()) {
        log.error("Failed to find path from %d,%d to %d,%d", startX, startY, endX, endY);
        return path;
    }

    path.push_back(end);

    while (cameFrom[pathPoint].x != startX || cameFrom[pathPoint].y != startY) {
        pathPoint = cameFrom[pathPoint];
        path.push_back(MapPos(pathPoint.x * coarseness, pathPoint.y * coarseness));

        if (cameFrom.find(pathPoint) == cameFrom.end()) {
            log.error("invalid path, failed to find previous step");
            return path;
        }
    }

    return path;

}

bool MoveOnMap::isPassable(int x, int y)
{
    x /= Map::TILE_SIZE;
    y /= Map::TILE_SIZE;
    if (IS_UNLIKELY(x < 0 || y < 0 || x >= m_map->getCols() || y >= m_map->getRows())) {
        return false;
    }

    return (m_terrainMoveMultiplier[m_map->getTileAt(x, y).terrainId()] > 0);
}

}
