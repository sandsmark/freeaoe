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
#include <unordered_set>
#include "Unit.h"

#include "Map.h"
class SfmlRenderTarget;

struct Camera;
typedef std::shared_ptr<Camera> CameraPtr;

struct Player;

struct MapPositionSorter
{
    bool operator()(const Unit::Ptr &lhs, const Unit::Ptr &rhs) const {
        const ScreenPos pos1 = lhs->position().toScreen();
        const ScreenPos pos2 = rhs->position().toScreen();

        if (pos1.y != pos2.y) {
            return pos1.y > pos2.y;
        }

        if (pos1.x != pos2.x) {
            return pos1.x > pos2.x;
        }

        // std sucks
        return lhs > rhs;
    }
};

//class CameraPtr;
// IDEA: Class containing all entities, (adds, removes, updates them).
// Base class (EntitySpace?)
typedef std::unordered_set<Unit::Ptr> UnitSet;

class UnitManager
{
public:
    UnitManager();
    virtual ~UnitManager();

    void add(const Unit::Ptr &unit);

    bool init();

    bool update(Time time);
    void render(const std::shared_ptr<SfmlRenderTarget> &renderTarget);

    bool onLeftClick(const MapPos &mapPos);
    void onRightClick(const ScreenPos &screenPos, const CameraPtr &camera);
    void onMouseMove(const MapPos &mapPos);

    void selectUnits(const ScreenRect &selectionRect, const CameraPtr &camera);
    void setMap(const MapPtr &map);
    const MapPtr &map() { return m_map; }

    void setSelectedUnits(const UnitSet &units);
    const UnitSet &selected() const { return m_selectedUnits; }

    const std::set<Unit::Ptr, MapPositionSorter> &units() const { return m_units; }

    void placeBuilding(const int unitId, const std::shared_ptr<Player> &player);

    Unit::Ptr unitAt(const ScreenPos &pos, const CameraPtr &camera) const;

    const std::unordered_set<Task> availableActions() const { return m_currentActions; }

    const Task defaultActionAt(const ScreenPos &pos, const CameraPtr &camera);
    void moveUnitTo(const Unit::Ptr &unit, const MapPos &targetPos);

private:
    void updateVisibility(const CameraPtr &camera);
    void assignTask(const Task &task, const Unit::Ptr &unit, const Unit::Ptr &target);
    void playSound(const Unit::Ptr &unit);

    std::set<Unit::Ptr, MapPositionSorter> m_units;
    std::unordered_set<Task> m_currentActions;

    UnitSet m_selectedUnits;
    MapPtr m_map;
    sf::RenderTexture m_outlineOverlay;
    MoveTargetMarker::Ptr m_moveTargetMarker;

    Unit::Ptr m_buildingToPlace;
    MapPos m_previousCameraPos;
};

