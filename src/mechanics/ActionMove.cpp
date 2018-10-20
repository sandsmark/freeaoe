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
#include "resource/DataManager.h"
#include "core/Utility.h"

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

    float x = 0;
    float y = 0;
    float pathLength = 0;
    float distance = 0;

    bool operator==(const PathPoint &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const PathPoint &other) const {
        return x != other.x || y != other.y;
    }
    bool operator<(const PathPoint &other) const {
        return (other.distance + other.pathLength) < (distance + pathLength);
    }
};
} //namespace

template<> struct std::hash<PathPoint>
{
    std::size_t operator()(const PathPoint& point) const
    {
        return point.y * 255 * 96 + point.x;
    }
};

static const float PATHFINDING_HEURISTIC_WEIGHT = 1.;

ActionMove::ActionMove(MapPos destination, const MapPtr &map, const Unit::Ptr &unit) :
    IAction(Type::Move, unit),
    m_map(map),
    target_reached(false)
{
    dest_ = destination;

    m_terrainMoveMultiplier = DataManager::Inst().getTerrainRestriction(unit->data()->TerrainRestriction).PassableBuildableDmgMultiplier;
    speed_ = unit->data()->Speed;
}

MapPos ActionMove::findClosestWalkableBorder(const MapPos &target, int coarseness)
{
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "Lost our unit";
        return target;
    }

    // follow a straight line from the target to our location, to find the closest position we can get to
    // standard bresenham, not the prettiest implementation
    const int x0 = target.x;
    const int y0 = target.y;
    const int x1 = unit->position().x;
    const int y1 = unit->position().y;

    int dx = x1 - x0;
    int dy = y1 - y0;

    int u, v;
    int distanceU, distanceV;
    int uincrX, uincrY, vincrX, vincrY;

    if (std::abs(dx) > std::abs(dy)) {
        distanceU = std::abs(dx);
        distanceV = std::abs(dy);
        u = x1;
        v = y1;
        uincrX = 1;
        uincrY = 0;
        vincrX = 0;
        vincrY = 1;
        if (dx < 0) { uincrX = -uincrX; }
        if (dy < 0) { vincrY = -vincrY; }
    } else {
        distanceU = std::abs(dy);
        distanceV = std::abs(dx);
        u = y1;
        v = x1;
        uincrX = 0;
        uincrY = 1;
        vincrX = 1;
        vincrY = 0;
        if (dx < 0) { vincrX = -vincrX; }
        if (dy < 0) { uincrY = -uincrY; }
    }

    const int uend = u + distanceU;
    int d = (2 * distanceV) - distanceU;	    /* Initial value as in Bresenham's */
    const int incrS = 2 * distanceV;	/* Δd for straight increments */
    const int incrD = 2 *(distanceV - distanceU);	/* Δd for diagonal increments */

    int x = x0, y = y0;

    do {
        if (d < 0) {
            /* choose straight (u direction) */
            d = d + incrS;
        } else {
            /* choose diagonal (u+v direction) */
            d = d + incrD;
            v = v+1;
            x += vincrX;
            y += vincrY;
        }

        u = u+1;
        x += uincrX;
        y += uincrY;

        if (isPassable(x, y, coarseness)) {
            break;
        }
    } while (u <= uend);


    return MapPos(x, y);
}

ActionMove::~ActionMove()
{
}

IAction::UpdateResult ActionMove::update(Time time)
{
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "My unit got deleted";
        return UpdateResult::Completed;
    }

    if (m_passableDirty) {
        m_passable.reset();
        m_passableCached.reset();
    }

    if (!m_prevTime) {
        m_prevTime = time;
        updatePath();
        return UpdateResult::NotUpdated;
    }

    if (target_reached || m_path.empty()) {
        target_reached = true;
        return UpdateResult::Completed;
    }

    float elapsed = time - m_prevTime;
    float movement = elapsed * speed_ * 0.15;


    float distanceLeft = std::hypot(m_path.back().x - unit->position().x, m_path.back().y - unit->position().y);
    while (distanceLeft < movement && !m_path.empty()) {
        m_path.pop_back();
        if (m_path.empty()) {
            break;
        }
        distanceLeft = std::hypot(m_path.back().x - unit->position().x, m_path.back().y - unit->position().y);
    }

    if (m_path.empty()) {
        target_reached = true;
        return UpdateResult::Completed;
    }

    MapPos nextPos = m_path.back();
    if (!isPassable(nextPos.x, nextPos.y)) {
        WARN << "next waypoint inaccessible, repathing";
        updatePath();

        if (m_path.empty()) {
            target_reached = true;
            return UpdateResult::Completed;
        }

        return UpdateResult::NotUpdated;
    }

    const float direction = std::atan2(nextPos.y - unit->position().y, nextPos.x - unit->position().x);
    MapPos newPos = unit->position();
    movement = std::min(movement, std::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y));
    newPos.x += std::cos(direction) * movement;
    newPos.y += std::sin(direction) * movement;

    // Try to wiggle past
    if (!isPassable(newPos.x, newPos.y)) {
        newPos = unit->position();
        movement = std::min(movement, std::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y));
        newPos.x += std::cos(direction + M_PI_2/2) * movement;
        newPos.y += std::sin(direction + M_PI_2/2) * movement;
    }
    // Try to wiggle past, other direction
    if (!isPassable(newPos.x, newPos.y)) {
        newPos = unit->position();
        movement = std::min(movement, std::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y));
        newPos.x += std::cos(direction - M_PI_2/2) * movement;
        newPos.y += std::sin(direction - M_PI_2/2) * movement;
    }

    if (!isPassable(newPos.x, newPos.y)) {
        WARN << "can't move forward, repathing";

        std::vector<MapPos> partial = findPath(unit->position(), nextPos, 1);
        if (partial.size() < 2) {
            WARN << "failed to find intermediary path";
            target_reached = true;
            return UpdateResult::Completed;
        } else {
            m_path.insert(m_path.begin(), ++partial.begin(), partial.end());
            return UpdateResult::Updated;
        }
    }


    ScreenPos sourceScreen = unit->position().toScreen();
    ScreenPos targetScreen = newPos.toScreen();
    unit->setAngle(std::atan2((targetScreen.y - sourceScreen.y), (targetScreen.x - sourceScreen.x)));
    newPos.z = m_map->elevationAt(newPos);

    unit->setPosition(newPos);

    m_prevTime = time;

    if (std::hypot(newPos.x - dest_.x, newPos.y - dest_.y) < movement) {
        target_reached = true;
        return UpdateResult::Completed;
    }

    return UpdateResult::Updated;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, MapPos destination, const MapPtr &map)
{
    if (!unit->data()->Speed) {
        DBG << "Handed unit that can't move" << unit->debugName;
        return nullptr;
    }

    std::shared_ptr<ActionMove> action (new ActionMove(destination, map, unit));

    return action;
}

std::vector<MapPos> ActionMove::findPath(MapPos start, MapPos end, int coarseness)
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

                if (!isPassable(nx * coarseness, ny * coarseness, coarseness)) {
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

    while (cameFrom[pathPoint] != currentPosition) {
        pathPoint = cameFrom[pathPoint];
        path.emplace_back(pathPoint.x * coarseness, pathPoint.y * coarseness);

        if (cameFrom.find(pathPoint) == cameFrom.end()) {
            WARN << "invalid path, failed to find previous step";
            return path;
        }
    }
    DBG << "final path length" << path.size();

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

bool ActionMove::isPassable(const int x, const int y, int coarseness)
{
    if (IS_UNLIKELY(x < 0 || y < 0)) {
        return false;
    }
    const int tileX = x / Constants::TILE_SIZE;
    const int tileY = y / Constants::TILE_SIZE;
    if (IS_UNLIKELY(tileX >= m_map->getCols() || tileY >= m_map->getRows())) {
        return false;
    }

    const unsigned cacheIndex = x  + y * 255u;
    if (m_passableCached[cacheIndex]) {
        return m_passable[cacheIndex];
    }

    m_passableDirty = true;
    m_passableCached[cacheIndex] = true;

    const MapTile &tile = m_map->getTileAt(tileX, tileY);
    if (m_terrainMoveMultiplier[tile.terrainId] == 0) {
        m_passable[cacheIndex] = false;
        return false;
    }

    const MapPos mapPos(x, y);
    Unit::Ptr unit = m_unit.lock();

    for (int dx = tileX-1; dx<=tileX+1; dx++) {
        for (int dy = tileY-1; dy<=tileY+1; dy++) {
            if (IS_UNLIKELY(dx < 0 || dy < 0 || dx >= m_map->getCols() || dy >= m_map->getRows())) {
                continue;
            }
            const std::vector<std::weak_ptr<Entity>> &entities = m_map->entitiesAt(dx, dy);

            if (entities.empty()) {
                continue;
            }

            for (const std::weak_ptr<Entity> &entity : entities) {
                Unit::Ptr otherUnit = Entity::asUnit(entity);
                if (IS_UNLIKELY(!otherUnit)) {
                    continue;
                }

                if (IS_UNLIKELY(otherUnit->id == unit->id)) {
                    continue;
                }

                if (otherUnit->data()->Size.z == 0) {
                    continue;
                }

                const float xSize = (otherUnit->data()->Size.x + unit->data()->Size.x) * Constants::TILE_SIZE + coarseness;
                const float ySize = (otherUnit->data()->Size.y + unit->data()->Size.y) * Constants::TILE_SIZE + coarseness;
                const float xDistance = std::abs(otherUnit->position().x - mapPos.x);
                const float yDistance = std::abs(otherUnit->position().y - mapPos.y);

                if (IS_UNLIKELY(xDistance < xSize && yDistance < ySize)) {
                    m_passable[cacheIndex] = false;
                    return false;
                }
            }
        }
    }

    m_passable[cacheIndex] = true;
    return true;
}

void ActionMove::updatePath()
{
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "Lost our unit";
        return;
    }

    DBG << "moving to" << dest_;

    MapPos newDest = dest_;
    if (!isPassable(dest_.x, dest_.y)) {
        newDest = findClosestWalkableBorder(dest_, 2);
        dest_ = newDest;
    }

    m_path = findPath(unit->position(), newDest, 2);

    // Try coarser
    // Uglier, but hopefully faster
    if (m_path.empty()) {
        if (newDest != dest_) {
            newDest = findClosestWalkableBorder(dest_, 5);
            dest_ = newDest;
        }
        m_path = findPath(unit->position(), newDest, 5);
    }

    if (m_path.empty()) {
        if (newDest != dest_) {
            newDest = findClosestWalkableBorder(dest_, 10);
            dest_ = newDest;
        }
        m_path = findPath(unit->position(), newDest, 10);
    }

    if (m_path.empty()) {
        DBG << "Failed to find path for" << unit->debugName;
    }
}
