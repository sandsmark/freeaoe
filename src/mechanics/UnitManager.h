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
#include <memory>
#include <unordered_set>

#include "Unit.h"

#include "global/EventListener.h"
#include "render/IRenderTarget.h"

struct Player;
struct Building;
struct Missile;
struct Camera;


typedef std::shared_ptr<Camera> CameraPtr;

class GraphicRender;
using GraphicRenderPtr = std::shared_ptr<GraphicRender>;

class Map;
using MapPtr = std::shared_ptr<Map>;

namespace genie {
class Tech;
}

namespace sf {
class RenderTexture;
}

struct UnplacedBuilding {
    GraphicRenderPtr graphic;
    MapPos position;
    int unitID = 0;
    const genie::Unit *data = nullptr;
    int orientation = 0; // "fake" orientation..
    bool isWall = false;
    bool canPlace = true;
};


struct MapPositionSorter
{
    bool operator()(const Unit::Ptr &lhs, const Unit::Ptr &rhs) const {
        const MapPos &mpos1 = lhs->position();
        const MapPos &mpos2 = rhs->position();
        if (mpos1.z != mpos2.z) {
            return mpos1.z > mpos2.z;
        }

        const ScreenPos pos1 = mpos1.toScreen();
        const ScreenPos pos2 = mpos2.toScreen();


        if (pos1.y != pos2.y) {
            return pos1.y < pos2.y;
        }

        if (pos1.x != pos2.x) {
            return pos1.x < pos2.x;
        }

        // std sucks
        return lhs < rhs;
    }
};

//class CameraPtr;
// IDEA: Class containing all entities, (adds, removes, updates them).
// Base class (EntitySpace?)
typedef std::vector<std::shared_ptr<Unit>> UnitVector;
//typedef std::unordered_set<std::shared_ptr<Unit>> UnitSet;

/// STL's API design is a flying, then crashing, shitshow.
/// should probably make it templated idk idc
struct UnitSet {
    using iterator = std::vector<std::shared_ptr<Unit>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<Unit>>::const_iterator;

    inline iterator begin() { return units.begin(); }
    inline iterator end() { return units.end(); }

    inline const_iterator begin() const { return units.begin(); }
    inline const_iterator end() const { return units.end(); }

    inline bool isEmpty() const { return units.empty(); }
    size_t size() const { return units.size(); }

    const std::shared_ptr<Unit> &first() const { return units[0]; }

    bool contains(const std::shared_ptr<Unit> &unit) const {
        return std::find(units.begin(), units.end(), unit) != units.end();
    }

    // STL sucks, so let's wrap it
    inline void add(const std::shared_ptr<Unit> &unit) {
        const std::vector<std::shared_ptr<Unit>>::const_iterator it = std::find(units.begin(), units.end(), unit);
        if (it != units.end()) {
            return;
        }
        units.push_back(unit);
    }

    inline bool remove(const std::shared_ptr<Unit> &unit) {
        const std::vector<std::shared_ptr<Unit>>::const_iterator it = std::find(units.begin(), units.end(), unit);
        if (it == units.end()) {
            return false;
        }
        units.erase(it);
        return true;
    }

    std::vector<std::shared_ptr<Unit>> units;
};

class UnitManager : public EventListener, public SignalEmitter<UnitManager>
{
public:
    enum Signals {
        ActionsChanged,
        SignalCount
    };
    static constexpr int GaiaID = 0;

    enum class State {
        PlacingBuilding,
        PlacingWall,
        SelectingAttackTarget,
        SelectingGarrisonTarget,
        Default
    };

    UnitManager(const UnitManager&) = delete;
    const UnitManager &operator=(const UnitManager&) = delete;

    UnitManager();
    virtual ~UnitManager();

    void add(const Unit::Ptr &unit, const MapPos &position);
    void remove(const Unit::Ptr &unit);
    void remove(const DopplegangerEntity::Ptr &unit);

    bool init();

    void setPlayers(const std::vector<std::shared_ptr<Player>> &players);
    void setHumanPlayer(const std::shared_ptr<Player> &player);
    int humanPlayerID() const { return m_humanPlayerID; }
    std::shared_ptr<Player> humanPlayer() const { return m_humanPlayer.lock(); }

    bool update(Time time);

    bool onLeftClick(const ScreenPos &screenPos, const CameraPtr &camera);
    void onRightClick(const ScreenPos &screenPos, const CameraPtr &camera);
    void onMouseMove(const MapPos &mapPos);
    bool onMouseRelease();

    void selectUnits(const ScreenRect &selectionRect, const CameraPtr &camera);
    void setMap(const MapPtr &map);
    const MapPtr &map() { return m_map; }

    void setSelectedUnits(const UnitVector &units);
    const UnitSet &selected() const { return m_selectedUnits; }

    const UnitVector &units() const { return m_units; }
    const std::unordered_set<std::shared_ptr<Missile>> &missiles() const { return m_missiles; }
    const std::unordered_set<StaticEntity::Ptr> &staticEntities() const { return m_staticEntities; }
    const std::vector<UnplacedBuilding> &buildingsToPlace() const { return m_buildingsToPlace; }
    const MoveTargetMarker::Ptr &moveTargetMarker() const { return m_moveTargetMarker; }

    void startPlaceBuilding(const int unitId, const std::shared_ptr<Player> &player);
    void enqueueProduceUnit(const genie::Unit *unitData, const UnitVector &producers);
    void enqueueResearch(const genie::Tech *techData, const UnitVector &producers);

    Unit::Ptr unitAt(const ScreenPos &pos, const CameraPtr &camera) const;
    Unit::Ptr clickedUnitAt(const ScreenPos &pos, const CameraPtr &camera);

    const TaskSet availableActions() const { return m_currentActions; }

    const Task defaultActionAt(const ScreenPos &pos, const CameraPtr &camera) const noexcept;
    void moveUnitTo(const Unit::Ptr &unit, const MapPos &targetPos);
    void selectAttackTarget();
    void selectGarrisonTarget();

    State state() const { return m_state; }

    void addMissile(const std::shared_ptr<Missile> &missile) { m_missiles.insert(missile); }
    void addStaticEntity(const StaticEntity::Ptr &entity) { if (entity) m_staticEntities.insert(entity); }

    void onCombatantUnitsMoved() { m_unitsMoved = true; }

    int targetBlinkTimeLeft(int unitID) const noexcept;

private:
    void onResearchCompleted(Player * /*player*/, int /*researchId*/) override { m_availableActionsChanged = true; }
    void onUnitMoved(Unit *unit, const MapPos &oldTile, const MapPos &newTile) override;
    void onTileHidden(const int playerID, const int tileX, const int tileY) override;
    void onTileDiscovered(const int playerID, const int tileX, const int tileY) override;

    void updateBuildingToPlace();
    void placeBuilding(const UnplacedBuilding &building);
    void updateAvailableActions();

    State m_state = State::Default;

    void playSound(const Unit::Ptr &unit);
    const Task taskForPosition(const Unit::Ptr &unit, const ScreenPos &pos, const CameraPtr &camera) const noexcept;

    std::unordered_set<std::shared_ptr<Missile>> m_missiles;
    std::unordered_set<StaticEntity::Ptr> m_staticEntities;
    UnitVector m_units;
    MoveTargetMarker::Ptr m_moveTargetMarker;
    UnitSet m_unitsWithActions;
    TaskSet m_currentActions;

    /// The blinking animation thing when it is selected as a target
    std::unordered_map<int, int> m_targetBlinkTimeLeft; // TODO: find a better way to do this

    UnitSet m_selectedUnits;
    MapPtr m_map;

    std::vector<UnplacedBuilding> m_buildingsToPlace;
    MapPos m_wallPlacingStart;

    bool m_unitsMoved = true;

    bool m_availableActionsChanged = true; // Because we might get a bunch of events in a single update, do it only once

    std::vector<std::weak_ptr<Player>> m_players;
    std::weak_ptr<Player> m_humanPlayer;
    int m_humanPlayerID = -1;

    Time m_lastUpdateTime = 0;
};

inline LogPrinter operator <<(LogPrinter os, const UnitManager::State state)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "UnitManager::State::";
    switch(state) {
    case UnitManager::State::Default: os << "Default"; break;
    case UnitManager::State::PlacingWall: os << "PlacingWall"; break;
    case UnitManager::State::PlacingBuilding: os << "PlacingBuilding"; break;
    case UnitManager::State::SelectingAttackTarget: os << "SelectingAttackTarget"; break;
    case UnitManager::State::SelectingGarrisonTarget: os << "SelectingGarrisonTarget"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}
