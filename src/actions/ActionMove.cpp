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

//    if (minDistance > 0.f && target.distance(start) < minDistance) {
//        const float angleToTarget = start.angleTo(target);
//        DBG << "too close" << minDistance << target.distance(start) << angleToTarget;

//        target.x = start.x + cos(angleToTarget) * minDistance + 0.1;
//        target.y = start.y + sin(angleToTarget) * minDistance + 0.1;

//        if (isPassable(target.x, target.y)) {
//            m_destination = target;
//            DBG << "position away is okay";
//            return target;
//        }
//    }

    const float xSize = unit->data()->Size.x * Constants::TILE_SIZE;
    const float ySize = unit->data()->Size.y * Constants::TILE_SIZE;
    const float radius = std::max(xSize, ySize);
    float clearanceLength = 0.f;

    const int tileX = target.x / Constants::TILE_SIZE;
    const int tileY = target.y / Constants::TILE_SIZE;
    for (int dx = tileX-1; dx<=tileX+1; dx++) {
        for (int dy = tileY-1; dy<=tileY+1; dy++) {
            if (IS_UNLIKELY(dx < 0 || dy < 0 || dx >= m_map->columnCount() || dy >= m_map->rowCount())) {
                continue;
            }
            const std::vector<std::weak_ptr<Entity>> &entities = m_map->entitiesAt(dx, dy);

            if (entities.empty()) {
                continue;
            }

            for (const std::weak_ptr<Entity> &entity : entities) {
                Unit::Ptr otherUnit = Unit::fromEntity(entity);
                if (IS_UNLIKELY(!otherUnit)) {
                    continue;
                }

                if (IS_UNLIKELY(otherUnit->id == unit->id)) {
                    continue;
                }

                if (otherUnit->data()->Size.z == 0) {
                    continue;
                }

                if (otherUnit->distanceTo(otherUnit) < 0.1f) {// radius + otherUnit->clearanceSize().width) {
                    const Size targetSize = otherUnit->clearanceSize();
                    const float targetRadius = std::max(targetSize.width, targetSize.height);
                    clearanceLength = std::max(targetRadius + std::max(targetRadius, radius), clearanceLength);
                }
            }
        }
    }

    MapPos newPos = target;
    if (clearanceLength > 0.f) {
//        DBG << "Found target unit";
#ifdef DEBUG
        testedPoints.push_back(target);
#endif
        const float angleToTarget = start.angleTo(target);

        const float stepSize = M_PI / radius;

        float lowestDistance = std::numeric_limits<float>::max();

        bool left = false;
        for (float angleOffset = 0; angleOffset < M_PI*2.; angleOffset += stepSize) {
            MapPos potential(cos(angleToTarget), sin(angleToTarget));
            if (left) {
                potential.x += cos(angleOffset);
                potential.y += sin(angleOffset);
                left = false;
            } else {
                potential.x -= cos(angleOffset);
                potential.y -= sin(angleOffset);
                left = true;
            }
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
//        DBG << "Found way around target";
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

#ifdef DEBUG
        testedPoints.push_back(MapPos(x, y));
#endif

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

    // TODO differentiate between max manhattan distance (square obstruction type) and euclidian distance (round obstruction type)
    MapRect targetRect(m_destination, Size(maxDistance + 1, maxDistance + 1));
    MapPos unitPosition = unit->position();

    Unit::Ptr targetUnit = m_targetUnit.lock();

    // First update
    if (!m_prevTime) {
        if (unitPosition.distance(m_destination) < 1 || targetRect.contains(unitPosition)) { // just in case
            return UpdateResult::Completed;
        }
        if (targetUnit) {
            m_lastTargetUnitPosition = targetUnit->position();
            m_destination = m_lastTargetUnitPosition;
        }

        m_prevTime = time;
        updatePath();
        if (m_path.empty()) {
            return UpdateResult::Failed;
        }

        return UpdateResult::NotUpdated;
    }

    if (targetUnit) {
        if (unit->distanceTo(targetUnit) < 0.f) {
            return UpdateResult::Completed;
        }

        const Size size = targetUnit->clearanceSize();
        targetRect.width = size.width;
        targetRect.height = size.height;
        targetRect.x -= targetRect.width/2;
        targetRect.y -= targetRect.height/2;

        if ((targetUnit->position()/50).rounded() != (m_lastTargetUnitPosition/50).rounded()) {
            m_lastTargetUnitPosition = targetUnit->position();
            m_destination = m_lastTargetUnitPosition;

            if (std::floor(unitPosition.distance(m_destination)) < 0.1) {// std::max(unit->clearanceSize().width, unit->clearanceSize().height) + 1) {
                return UpdateResult::Completed;
            }

            updatePath();

            return UpdateResult::NotUpdated;
        }
    }

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

//    if (targetUnit) { // check if it moved
//        const double targetMovedDistance = m_lastTargetPosition.distance(targetUnit->position());
//        m_lastTargetUnitPosition = targetUnit->position();
//        m_destination = m_lastTargetUnitPosition;
//        if (targetMovedDistance > 1) {  // chosen by dice roll
//            DBG << "Unit moved, repathing";
//            updatePath();
//        }
//    }

    if (m_targetReached) {
        return UpdateResult::Completed;
    }

    if (m_path.empty()) {
        m_targetReached = true;

        if (unitPosition.distance(m_destination) < 1 || targetRect.contains(unitPosition)) {
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
        m_prevPathPoint = unitPosition;
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

        if (m_destination.rounded() == unit->position().rounded() || targetRect.contains(unit->position())) {
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


    MapPos newPos = unitPosition;

    const float direction = std::atan2(nextPos.y - unitPosition.y, nextPos.x - unitPosition.x);
    if (util::hypot(nextPos.x - newPos.x, nextPos.y - newPos.y) < movement) {
        newPos = nextPos;
    } else {
        newPos.x += std::cos(direction) * movement;
        newPos.y += std::sin(direction) * movement;
    }

    if (!isPassable(newPos.x, newPos.y)) {
        DBG << "Wiggle left";
        newPos = unitPosition;

        newPos.x += std::cos(direction + M_PI_2) * movement;
        newPos.y += std::sin(direction + M_PI_2) * movement;
    }

    if (!isPassable(newPos.x, newPos.y)) {
        DBG << "Wiggle right";
        newPos = unitPosition;

        newPos.x += std::cos(direction - M_PI_2) * movement;
        newPos.y += std::sin(direction - M_PI_2) * movement;
    }

    if (!isPassable(newPos.x, newPos.y)) {
        if (!isPassable(m_destination.x, m_destination.y)) {
            DBG << "destination isn't passable, trying again next round";
            return UpdateResult::NotUpdated;
        }
        if (unitPosition.distance(m_destination) < 1) {
            DBG << "can't move forward, but close enough to destination" << distanceLeft;
            m_destination.z = m_map->elevationAt(m_destination);
            unit->setPosition(m_destination);
            return UpdateResult::Completed;
        }
        DBG << "can't move forward and too far from the destination" << distanceLeft << "finding intermediat path for" << unit->debugName;
        DBG << unitPosition << newPos << movement;

        DBG << "can't move forward, finding intermediat path for" << unit->debugName;

        std::vector<MapPos> partial = findPath(unitPosition, nextPos, 1);
        if (partial.size() < 1) {
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
            DBG << "found intermediary from" << unitPosition << "to" << nextPos;
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


    const ScreenPos sourceScreen = unitPosition.toScreen();
    const ScreenPos targetScreen = newPos.toScreen();
    const float newAngle = sourceScreen.angleTo(targetScreen);
    if (m_path.size() < 2) {
        unit->setAngle(newAngle);
    } else {
        // Avoid changing the angle quickly back and forth in some corner cases, it looks dumb
        nextPos = *(m_path.end() - 2);
        nextPos.z = m_map->elevationAt(nextPos);
        if (std::abs(m_prevPathPoint.toScreen().angleTo(nextPos.toScreen())) > 0.1) {
            unit->setAngle(m_prevPathPoint.toScreen().angleTo(nextPos.toScreen()));
        }
    }
    newPos.z = m_map->elevationAt(newPos);

    if (!isPassable(newPos.x, newPos.y)) {
        WARN << "ended up in unpassable land";
        return UpdateResult::Failed;
    }
    unit->setPosition(newPos);

    m_prevTime = time;

    return UpdateResult::Updated;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const UnitPtr &unit, const Task &task) noexcept
{
    if (!unit->data()->Speed) {
        DBG << "Handed unit that can't move" << unit->debugName;
        return nullptr;
    }


    Unit::Ptr targetUnit = task.target.lock();
    if (!targetUnit) {
        WARN << "Asked to move to unit, but no unit passed";
        return nullptr;
    }

    std::shared_ptr<ActionMove> action (new ActionMove(targetUnit->position(), unit, task));
    action->m_targetUnit = targetUnit;

    return action;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, MapPos destination, const Task &task) noexcept
{
    if (!unit->data()->Speed) {
        DBG << "Handed unit that can't move" << unit->debugName;
        return nullptr;
    }


    std::shared_ptr<ActionMove> action (new ActionMove(destination, unit, task));
    action->m_targetUnit = task.target;

    return action;
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, MapPos destination) noexcept
{
    static genie::Task defaultGenieMoveTask;
    defaultGenieMoveTask.ActionType = genie::ActionType::MoveTo;

    return moveUnitTo(unit, destination, Task(defaultGenieMoveTask, -1));
}

std::shared_ptr<ActionMove> ActionMove::moveUnitTo(const Unit::Ptr &unit, const Unit::Ptr &targetUnit) noexcept
{
    static genie::Task defaultGenieMoveTask;
    defaultGenieMoveTask.ActionType = genie::ActionType::MoveTo;

    Task moveTask(defaultGenieMoveTask, -1);
    moveTask.target = targetUnit;

    return moveUnitTo(unit, moveTask);
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

#if 0
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
#endif

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
    if (startX == endX && startY == endY) {
        DBG << "Already at right position" << start << end;
        return {start};
    }
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


    MapRect targetRect(MapPos(endX-coarseness/2, endY-coarseness/2), Size(maxDistance / coarseness + coarseness, maxDistance / coarseness + coarseness));
    const Unit::Ptr targetUnit = m_targetUnit.lock();
    if (targetUnit) {
        const Size size = targetUnit->clearanceSize() / coarseness;
        targetRect.width += size.width;
        targetRect.height += size.height;
        targetRect.x -= targetRect.width/2;
        targetRect.y -= targetRect.height/2;
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

        if (targetRect.contains(parent.x, parent.y)) {// && (minDistance <= 0.f || parent.distance > minDistance/coarseness)) {
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
    if (IS_UNLIKELY(tileX >= m_map->columnCount() || tileY >= m_map->rowCount())) {
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
            if (IS_UNLIKELY(dx < 0 || dy < 0 || dx >= m_map->columnCount() || dy >= m_map->rowCount())) {
                continue;
            }
            const std::vector<std::weak_ptr<Entity>> &entities = m_map->entitiesAt(dx, dy);

            for (size_t i=0; i<entities.size(); i++) {
                const Unit::Ptr otherUnit = Unit::fromEntity(entities[i]);
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
//        WARN << "target not passable, finding closest possible position";
        newDest = findClosestWalkableBorder(unit->position(), m_destination, 2);
        m_destination = newDest;
    }

    TIME_TICK;
    m_path = findPath(unit->position(), newDest, 2);

    // Try coarser
    // Uglier, but hopefully faster
    if (m_path.empty()) {
        WARN << "failed to find path, trying 0.2 resolution";
        if (newDest != m_destination) {
            newDest = findClosestWalkableBorder(unit->position(), m_destination, 5);
            m_destination = newDest;
        }
        m_path = findPath(unit->position(), newDest, 5);
    }

    TIME_TICK;

    if (m_path.empty()) {
        WARN << "failed to find path, trying 0.1 resolution";
        if (newDest != m_destination) {
            newDest = findClosestWalkableBorder(unit->position(), m_destination, 10);
            m_destination = newDest;
        }
        m_path = findPath(unit->position(), newDest, 10);
    }

    if (m_path.empty()) {
        DBG << "Failed to find path for" << unit->debugName;
    }

    TIME_TICK;
}
