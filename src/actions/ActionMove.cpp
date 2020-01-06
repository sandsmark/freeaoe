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

#include "core/Logger.h"
#include "core/Utility.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "mechanics/MapTile.h"
#include "mechanics/Map.h"
#include "resource/DataManager.h"

#include <genie/Types.h>
#include <genie/dat/TerrainRestriction.h>
#include <genie/dat/Unit.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <algorithm>
#include <iosfwd>
#include <limits>
#include <queue>
#include <stack>

#include <system_error>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG
std::vector<MapPos> ActionMove::testedPoints;
#endif

struct SimplePathPoint {
    SimplePathPoint(const int x_, const int y_) : x(x_), y(y_) {}
    int x = 0;
    int y = 0;

    bool operator==(const SimplePathPoint &other) const noexcept {
        return x == other.x || y == other.y;
    }
};

namespace { // anonymous namespace, don't export this
struct PathPoint {
    PathPoint() = default;

    int8_t dx = 0;
    int8_t dy = 0;

    PathPoint(int64_t _x, int64_t _y) : x(_x), y(_y) {}

    int32_t x = 0;
    int32_t y = 0;
    float pathLength = 0;
    float distance = 0;

    bool operator==(const PathPoint &other) const noexcept DUMB_CLANG_IT_IS_USED {
        return x == other.x && y == other.y;
    }
    bool operator!=(const PathPoint &other) const noexcept {
        return x != other.x || y != other.y;
    }
    bool operator<(const PathPoint &other) const noexcept DUMB_CLANG_IT_IS_USED {
        return other.distance < distance;
    }

    inline operator SimplePathPoint () const {
        return {x, y};
    }
};
} //namespace
template<> struct std::hash<PathPoint>
{
    std::size_t operator()(const PathPoint& point) const noexcept DUMB_CLANG_IT_IS_USED
    {
        return point.y * 255 * 48 + point.x;
    }
};

template<> struct std::hash<SimplePathPoint>
{
    std::size_t operator()(const SimplePathPoint& point) const noexcept
    {
        return point.y * 255 * 48 + point.x;
    }
};

static const float PATHFINDING_HEURISTIC_WEIGHT = 10;

ActionMove::ActionMove(MapPos destination, const Unit::Ptr &unit, const Task &task) :
    IAction(Type::Move, unit, task),
    m_map(unit->map()),
    m_targetReached(false)
{
    m_destination = destination;

    m_terrainMoveMultipliers = DataManager::Inst().getTerrainRestriction(unit->data()->TerrainRestriction).PassableBuildableDmgMultiplier;
    m_speed = unit->data()->Speed;
}

MapPos ActionMove::findClosestWalkableBorder(const MapPos &start, const MapPos &target, int coarseness) noexcept
{
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "Lost our unit";
        return start;
    }

    std::shared_ptr<Unit> targetUnit;
    const float xSize = unit->data()->Size.x * Constants::TILE_SIZE;
    const float ySize = unit->data()->Size.y * Constants::TILE_SIZE;
    const float radius = std::max(xSize, ySize);

    const int tileX = target.x / Constants::TILE_SIZE;
    const int tileY = target.y / Constants::TILE_SIZE;
    for (int dx = tileX-1; dx<=tileX+1 && !targetUnit; dx++) {
        for (int dy = tileY-1; dy<=tileY+1 && !targetUnit; dy++) {
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

                if (otherUnit->distanceTo(target) < radius) {
//                    DBG << "unit in our spot, trying to find a place close to it" << otherUnit->debugName;
                    targetUnit = std::move(otherUnit);
                    break;
                }
            }
        }
    }

    MapPos newPos = start;
    if (targetUnit) {
#ifdef DEBUG
        testedPoints.push_back(target);
#endif
        const Size targetSize = targetUnit->clearanceSize();
        const float targetRadius = std::max(targetSize.width, targetSize.height);
        const float clearanceLength = std::max(targetRadius, radius);


        const float stepSize = M_PI / radius;

        float lowestDistance = std::numeric_limits<float>::max();

        for (float angleOffset = 0; angleOffset < M_PI*2.; angleOffset += stepSize) {
            MapPos potential(cos(angleOffset), sin(angleOffset));
            potential = potential * clearanceLength + target;
            if (!isPassable(potential.x, potential.y)) {
                continue;
            }

#ifdef DEBUG
            testedPoints.push_back(potential);
#endif

            const float distance = start.distance(potential);
            if (distance < lowestDistance) {
                newPos = potential;
                lowestDistance = distance;
            }
        }
    }
    if (isPassable(newPos.x, newPos.y)) {
        return newPos;
    }
    // follow a straight line from the target to our location, to find the closest position we can get to
    // standard bresenham, not the prettiest implementation

    const int x0 = std::round(target.x / coarseness) * coarseness;
    const int y0 = std::round(target.y / coarseness) * coarseness;
    const int x1 = std::round(start.x / coarseness) * coarseness;
    const int y1 = std::round(start.y / coarseness) * coarseness;

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
    const int incrS = coarseness * 2 * distanceV;	/* Δd for straight increments */
    const int incrD = coarseness * 2 *(distanceV - distanceU);	/* Δd for diagonal increments */

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

        if (isPassable(x, y)) {
            x += uincrX;
            y += uincrY;
            break;
        }
    } while (u <= uend);



    return MapPos(x, y);
}

ActionMove::~ActionMove()
{
}

IAction::UpdateResult ActionMove::update(Time time) noexcept
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "My unit got deleted";
        return UpdateResult::Failed;
    }

    if (m_passableDirty) {
        m_passable.reset();
        m_passableCached.reset();
    }

    MapPos unitPosition = unit->position();
    if (!isPassable(unitPosition.x, unitPosition.y)) {
        WARN << "we got stuck!" << unit->debugName;
        unitPosition = findClosestWalkableBorder(m_destination, unitPosition, 1);
        if (isPassable(unitPosition.x, unitPosition.y)) {
            unitPosition.z = m_map->elevationAt(unitPosition);
            unit->setPosition(unitPosition);
            updatePath();
            return UpdateResult::Updated;
        }

        return UpdateResult::Failed;
    }

    if (!m_prevTime) {
        if (unitPosition.distance(m_destination) < 1) { // just in case
            return UpdateResult::Completed;
        }

        m_prevTime = time;
        updatePath();
        if (m_path.empty()) {
            return UpdateResult::Failed;
        }
//        if (m_path.back() != unitPosition) {
//            unit->setPosition(m_path.back()); // Just in case we had to do a coarse check
//            return UpdateResult::Updated;
//        }
        return UpdateResult::NotUpdated;
    }

    if (m_targetReached) {
        return UpdateResult::Completed;
    }

    if (m_path.empty()) {
        m_targetReached = true;

        if (unitPosition.distance(m_destination) < 1) {
            if (isPassable(m_destination.x, m_destination.y)) {
                m_destination.z = m_map->elevationAt(m_destination);


                unit->setPosition(m_destination);
                return UpdateResult::Completed;
            }
        }

        WARN << "failed to reach target" << unit->debugName;
        return UpdateResult::Failed;
    }

    float elapsed = time - m_prevTime;
    float movement = elapsed * m_speed * 0.15;


    float distanceLeft = util::hypot(m_path.back().x - unitPosition.x, m_path.back().y - unitPosition.y);
    while (movement > distanceLeft && !m_path.empty() && isPassable(m_path.back().x, m_path.back().y)) {
        movement -= distanceLeft;
        unitPosition = m_path.back();
        unitPosition.z = m_map->elevationAt(unitPosition);
        m_path.pop_back();
        if (m_path.empty()) {
            break;
        }
        distanceLeft = util::hypot(m_path.back().x - unitPosition.x, m_path.back().y - unitPosition.y);
    }

    if (m_path.empty()) {
        m_targetReached = true;
        if (!isPassable(unitPosition.x, unitPosition.y)) {
            WARN << "path empty after loop, complete, distance left:" << unitPosition.distance(m_destination) << unit->debugName;
            return UpdateResult::Failed;
        }

        m_prevTime = time;
        unitPosition.z = m_map->elevationAt(unitPosition);
        unit->setPosition(unitPosition);
        return UpdateResult::Completed;
    }

    MapPos nextPos = m_path.back();
    if (!isPassable(nextPos.x, nextPos.y)) {
//        DBG << "next waypoint inaccessible, repathing" << unit->debugName;

        updatePath();

        if (m_destination.rounded() == unit->position().rounded()) {
            DBG << "already in place";
            unitPosition.z = m_map->elevationAt(unitPosition);
            unit->setPosition(m_destination);
            return UpdateResult::Completed;
        }

        if (m_path.empty()) {
            WARN << "failed to find new target path";
            m_targetReached = true;
            return UpdateResult::Failed;
        }

        if (!isPassable(unitPosition.x, unitPosition.y)) {
            WARN << "ended up in unpassable land";
            return UpdateResult::Failed;
        }

        m_prevTime = time;
        unitPosition.z = m_map->elevationAt(unitPosition);
        unit->setPosition(unitPosition);
        return UpdateResult::NotUpdated;
    }

    const float direction = std::atan2(nextPos.y - unitPosition.y, nextPos.x - unitPosition.x);
    MapPos newPos = unitPosition;
    if (util::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y) < movement) {
        newPos = nextPos;
    } else {
        newPos.x += std::cos(direction) * movement;
        newPos.y += std::sin(direction) * movement;
    }

    // Try to wiggle past
    if (!isPassable(newPos.x, newPos.y)) {
        newPos = unitPosition;
        movement = std::min(movement, util::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y));
        newPos.x += std::cos(direction + M_PI_2/2) * movement;
        newPos.y += std::sin(direction + M_PI_2/2) * movement;
    }
    // Try to wiggle past, other direction
    if (!isPassable(newPos.x, newPos.y)) {
        newPos = unitPosition;
        movement = std::min(movement, util::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y));
        newPos.x += std::cos(direction - M_PI_2/2) * movement;
        newPos.y += std::sin(direction - M_PI_2/2) * movement;
    }

    if (!isPassable(newPos.x, newPos.y)) {
        if (!isPassable(m_destination.x, m_destination.y)) {
            DBG << "destination isn't passable, trying again next round";
            return UpdateResult::NotUpdated;
        }
        DBG << "can't move forward, finding intermediat path for" << unit->debugName;

        std::vector<MapPos> partial = findPath(unitPosition, nextPos, 1);
        if (partial.size() < 2) {
            WARN << "failed to find intermediary path";
            m_targetReached = true;
            m_prevTime = time;

            if (!isPassable(unitPosition.x, unitPosition.y)) {
                WARN << "ended up in unpassable land";
                return UpdateResult::Failed;
            }
            unitPosition.z = m_map->elevationAt(unitPosition);
            unit->setPosition(unitPosition);
            return UpdateResult::Failed;
        } else {
            DBG << "found intermediary";
            m_path.insert(m_path.begin(), ++partial.begin(), partial.end());
            m_prevTime = time;

            if (!isPassable(unitPosition.x, unitPosition.y)) {
                WARN << "ended up in unpassable land";
                return UpdateResult::Failed;
            }
            unitPosition.z = m_map->elevationAt(unitPosition);
            unit->setPosition(unitPosition);
            return UpdateResult::Updated;
        }
    }


    ScreenPos sourceScreen = unitPosition.toScreen();
    ScreenPos targetScreen = newPos.toScreen();
    unit->setAngle(sourceScreen.angleTo(targetScreen));
    newPos.z = m_map->elevationAt(newPos);

    if (!isPassable(newPos.x, newPos.y)) {
        WARN << "ended up in unpassable land";
        return UpdateResult::Failed;
    }
    unit->setPosition(newPos);

    m_prevTime = time;

    return UpdateResult::Updated;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, MapPos destination, const Task &task) noexcept
{
    if (!unit->data()->Speed) {
        DBG << "Handed unit that can't move" << unit->debugName;
        return nullptr;
    }


    std::shared_ptr<ActionMove> action (new ActionMove(destination, unit, task));

    return action;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, MapPos destination) noexcept
{
    static genie::Task defaultGenieMoveTask;
    defaultGenieMoveTask.ActionType = genie::ActionType::MoveTo;

    return moveUnitTo(unit, destination, Task(defaultGenieMoveTask, -1));
}

#if 0
static std::vector<MapPos> simplifyAngles(const std::vector<MapPos> &path)
{
    std::vector<MapPos> cleanedPath;
    cleanedPath.push_back(path[0]);
    for (size_t i=1; i<path.size() - 1; i++) {
        double lastAngle = std::atan2((path[i].y - path[i-1].y), (path[i].x - path[i-1].x));
        double nextAngle = std::atan2((path[i+1].y - path[i].y), (path[i+1].x - path[i].x));
        if (lastAngle != nextAngle) {
            cleanedPath.push_back(path[i]);
        }
    }
    cleanedPath.push_back(path.back());

    return cleanedPath;
}
#endif

static std::vector<MapPos> simplifyRdp(const std::vector<MapPos> &path, const float epsilon) noexcept
{
    if (path.empty()) {
        return path;
    }

    std::vector<MapPos> cleanedPath;


    std::stack<std::pair<int, int>> ranges;
    ranges.push({0, path.size() - 1});
    std::vector<bool> selected(path.size(), true);

    while (!ranges.empty()) {
        const int start = ranges.top().first;
        const int end = ranges.top().second;
        ranges.pop();

        float dmax = -1;
        int index = 0;
        for (int i = start + 1; i < end - 1; i++) {
            float d = path[i].distanceToLine(path[start], path[end]);
            if (d > dmax) {
                index = i;
                dmax = d;
            }
        }

        if (dmax > epsilon) {
            ranges.push({start, index});
            ranges.push({index, end});
        } else {
            for (int i=start + 1; i<end; i++) {
                selected[i] = false;
            }
        }
    }

    for (size_t i=0; i<path.size(); i++) {
        if (selected[i]) {
            cleanedPath.push_back(path[i]);
        }
    }

//    DBG << "after cleaning" << cleanedPath.size() << "/" << path.size();

    return cleanedPath;
}

std::vector<MapPos> ActionMove::findPath(MapPos start, MapPos end, int coarseness) noexcept
{
#ifdef DEBUG
    testedPoints.clear();
#endif
    if (start == end) {
        return {};
    }

    sf::Clock clock;

    std::vector<MapPos> path;

    int startX = std::round(start.x / coarseness);
    int startY = std::round(start.y / coarseness);
    int endX = std::round(end.x / coarseness);
    int endY = std::round(end.y / coarseness);
    if (!isPassable(startX * coarseness, startY * coarseness)) {
        WARN << "handed unpassable start, attempting to get out";
        start = findClosestWalkableBorder(MapPos(endX * coarseness, endY * coarseness), MapPos(startX * coarseness, startY * coarseness), coarseness);
        startX = std::round(start.x / coarseness);
        startY = std::round(start.y / coarseness);
    }

    if (!isPassable(startX * coarseness, startY * coarseness)) {
        WARN << "handed unpassable start, failed to find new";
        return path;
    }

    if (!isPassable(endX * coarseness, endY * coarseness)) {
//        WARN << "handed unpassable target, attempting to get out";
        start = findClosestWalkableBorder(start, end, coarseness);
        startX = std::round(start.x / coarseness);
        startY = std::round(start.y / coarseness);
    }

    if (!isPassable(endX * coarseness, endY * coarseness)) {
        WARN << "handed unpassable target";
        return path;
    }

    PathPoint currentPosition(startX, startY);

    std::unordered_map<PathPoint, PathPoint> cameFrom;

    // STL is a steaming pile of shit
    std::priority_queue<PathPoint> queue;
    currentPosition.distance = util::hypot(startX - endX, startY - endY);
    currentPosition.pathLength = 0;
    queue.push(currentPosition);

    std::unordered_set<SimplePathPoint> visited;
    visited.insert(currentPosition);

    PathPoint parent;
    size_t tried = 0;
    while (!queue.empty()) {
        tried++;
        parent = queue.top();
        queue.pop();

        if (parent.x == endX && parent.y == endY) {
            break;
        }

        visited.insert(parent);

#ifdef DEBUG
        testedPoints.push_back(MapPos(parent.x * coarseness, parent.y * coarseness));
#endif

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (!dx && !dy) {
                    continue;
                }

                // Check if we're checking backwards
                if (parent.dy == 0 && dy != 0 && parent.dx * dx < 0)  {
                    continue;
                }
                if (parent.dx == 0 && dx != 0 && parent.dy * dy < 0) {
                    continue;
                }

                const int nx = parent.x + dx;
                const int ny = parent.y + dy;

                // looking up in visited is expensive, try to avoid that
                if (nx == parent.x && ny == parent.y) {
                    continue;
                }

                // We already came from there
                if (nx == parent.x + parent.dx && ny == parent.y + parent.dy) {
                    continue;
                }


                SimplePathPoint position(nx, ny);
                if (visited.find(position) != visited.end()) {
                    continue;
                }

                if (!isPassable(nx * coarseness, ny * coarseness)) {
                    visited.insert(position);
                    continue;
                }
                PathPoint pathPoint(nx, ny);


                if (cameFrom.find(pathPoint) != cameFrom.end()) {
                    if ((cameFrom[pathPoint].pathLength < parent.pathLength)) {
                        continue;
                    }
                }

                pathPoint.dx = dx;
                pathPoint.dy = dx;

                const int diagCost = 3;
                const int straightCost = 2;
                if (!dx || !dy) {
                    pathPoint.pathLength = parent.pathLength + straightCost;
                } else {
                    pathPoint.pathLength = parent.pathLength + diagCost;
                }
//                pathPoint.pathLength = parent.pathLength + 1.; // chebychev
//                pathPoint.pathLength = parent.pathLength + std::abs(dx) + std::abs(dy); // manhattan
//                pathPoint.pathLength = parent.pathLength + util::hypot(dx, dy); // euclidian

//                pathPoint.distance = pathPoint.pathLength + (std::abs(nx - endX) + std::abs(ny - endY)) * PATHFINDING_HEURISTIC_WEIGHT; // manhattan
                pathPoint.distance = pathPoint.pathLength + util::hypot(nx - endX, ny - endY) * PATHFINDING_HEURISTIC_WEIGHT * straightCost;
                queue.push(pathPoint);

                cameFrom[pathPoint] = parent;
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 50) {
            WARN << "Timeout while pathing (" << tried << "nodes in" << clock.getElapsedTime().asMilliseconds() << "ms)";
            DBG << "visited" << visited.size();
            DBG << "queue size" << queue.size();
            return path;
        }
    }
    const int32_t elapsed = clock.getElapsedTime().asMilliseconds();
    if (elapsed > 10) {
        DBG << "walked" << tried << "nodes in" << elapsed << "ms";
        DBG << "visited" << visited.size();
    }

    if (cameFrom.find(parent) == cameFrom.end()) {
        WARN << "Failed to find path from" << startX << "," << startY << "to" << endX << "," << endY;
        DBG << parent.x << parent.y;
        return path;
    }

    path.push_back(end);

    while (cameFrom[parent] != currentPosition) {
        parent = cameFrom[parent];
        path.emplace_back(parent.x * coarseness, parent.y * coarseness);

        if (cameFrom.find(parent) == cameFrom.end()) {
            WARN << "invalid path, failed to find previous step";
            return path;
        }
    }
//    DBG << "final path length" << path.size();

    return path;

//    return simplifyRdp(simplifyAngles(path), coarseness);
//    return simplifyAngles(path);
//    return simplifyRdp(path, coarseness*1.5);
}

bool ActionMove::isPassable(const float x, const float y) noexcept
{
    if (IS_UNLIKELY(x < 0 || y < 0)) {
        return false;
    }
    const int tileX = x / Constants::TILE_SIZE + 0.5;
    const int tileY = y / Constants::TILE_SIZE + 0.5;
    if (IS_UNLIKELY(tileX >= m_map->getCols() || tileY >= m_map->getRows())) {
        return false;
    }

    const unsigned cacheIndex = x  + y * Constants::TILE_SIZE * Constants::MAP_MAX_SIZE;
    if (m_passableCached[cacheIndex]) {
        return m_passable[cacheIndex];
    }

    m_passableDirty = true;
    m_passableCached[cacheIndex] = true;

    const MapTile &tile = m_map->getTileAt(tileX, tileY);
    if (m_terrainMoveMultipliers[tile.terrainId] == 0) {
        m_passable[cacheIndex] = false;
        return false;
    }

    const double z = m_map->elevationAt(MapPos(x, y));
    const Unit::Ptr unit = m_unit.lock();
    genie::XYZF size = unit->data()->Size;
    size.x *= Constants::TILE_SIZE;
    size.y *= Constants::TILE_SIZE;

    for (int dx = tileX-1; dx<=tileX+1; dx++) {
        for (int dy = tileY-1; dy<=tileY+1; dy++) {
            if (IS_UNLIKELY(dx < 0 || dy < 0 || dx >= m_map->getCols() || dy >= m_map->getRows())) {
                continue;
            }
            const std::vector<std::weak_ptr<Entity>> &entities = m_map->entitiesAt(dx, dy);

            for (size_t i=0; i<entities.size(); i++) {
                const Unit::Ptr otherUnit = Entity::asUnit(entities[i]);
                if (IS_UNLIKELY(!otherUnit)) {
                    continue;
                }

                if (IS_UNLIKELY(otherUnit->id == unit->id)) {
                    continue;
                }

                if (otherUnit->data()->Size.z == 0) {
                    continue;
                }

                switch (otherUnit->data()->ObstructionType) {
                case genie::Unit::PassableObstruction:
                case genie::Unit::PassableObstruction2:
                case genie::Unit::PassableNoOutlineObstruction:
                    continue;
                case genie::Unit::BuildingObstruction:
                case genie::Unit::MountainObstruction: // TOOD:  apparently uses the selection mask?
                    if (dx == tileX && dy == tileY) { // TODO: need to check the distance from the tile
                        m_passable[cacheIndex] = false;
                        return false;
                    }
                    break;
                case genie::Unit::UnitObstruction:
                default: {
                    const MapPos &otherPos = otherUnit->position();

                    const double centreDistance = util::hypot(x - otherPos.x, y - otherPos.y, z - otherPos.z);
                    const Size otherSize = otherUnit->clearanceSize();
                    const double clearance = std::max(std::max(size.x, size.y), std::max(otherSize.width, otherSize.height));
                    if (centreDistance < clearance) {
                        m_passable[cacheIndex] = false;
                        return false;
                    }
                    break;
                }
                }
            }
        }
    }

    m_passable[cacheIndex] = true;
    return true;
}

void ActionMove::updatePath() noexcept
{
#ifdef DEBUG
    testedPoints.clear();
#endif
    TIME_THIS;

    m_path.clear();
    std::shared_ptr<Unit> unit = m_unit.lock();
    if (!unit) {
        WARN << "Lost our unit";
        return;
    }

    if (false) { // TODO use this and run the pathfinding in a background thread
        TIME_THIS;
        std::vector<MapUnit> mapUnits;
        MapUnit mapUnit;
        for (const Unit::Ptr &unit : unit->unitManager().units()) {
            mapUnit.pos = unit->position();
            mapUnit.size = unit->data()->ClearanceSize;

            switch (unit->data()->ObstructionType) {
            case genie::Unit::PassableObstruction:
            case genie::Unit::PassableObstruction2:
            case genie::Unit::PassableNoOutlineObstruction:
                continue;
            case genie::Unit::BuildingObstruction:
            case genie::Unit::MountainObstruction: // TOOD:  apparently uses the selection mask?
                mapUnit.rectangular = true;
                break;
            case genie::Unit::UnitObstruction:
            default:
                mapUnit.rectangular = false;
                break;
            }

            mapUnits.push_back(std::move(mapUnit));
        }
        DBG << mapUnits.size();
    }

    TIME_TICK;

    MapPos newDest = m_destination;
    if (!isPassable(m_destination.x, m_destination.y)) {
        WARN << "target not passable, finding closest possible position";
        newDest = findClosestWalkableBorder(unit->position(), m_destination, 2);
        m_destination = newDest;
    }

    TIME_TICK;
    m_path = simplifyRdp(findPath(unit->position(), newDest, 2), 2 * 1.3);

    // Try coarser
    // Uglier, but hopefully faster
    if (m_path.empty()) {
        WARN << "failed to find path, trying 0.2 resolution";
        if (newDest != m_destination) {
            newDest = findClosestWalkableBorder(unit->position(), m_destination, 5);
            m_destination = newDest;
        }
        m_path = simplifyRdp(findPath(unit->position(), newDest, 5), 5 * 1.3);
    }

    TIME_TICK;

    if (m_path.empty()) {
        WARN << "failed to find path, trying 0.1 resolution";
        if (newDest != m_destination) {
            newDest = findClosestWalkableBorder(unit->position(), m_destination, 10);
            m_destination = newDest;
        }
        m_path = simplifyRdp(findPath(unit->position(), newDest, 10), 10 * 1.3);
    }

    if (m_path.empty()) {
        DBG << "Failed to find path for" << unit->debugName;
    }

    TIME_TICK;
}
