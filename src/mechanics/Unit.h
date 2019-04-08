/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

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

#include "mechanics/Entity.h"
#include "core/ResourceMap.h"
#include "actions/IAction.h"

#include <deque>
#include <map>

#include <genie/dat/UnitCommand.h>
#include <genie/dat/unit/AttackOrArmor.h>

class Civilization;
struct Player;
struct Building;

struct Task {
    Task(const genie::Task &t, uint16_t id) : data(&t), unitId(id) {}
    Task() = default;

    const genie::Task *data = nullptr;
    uint16_t unitId = 0; // for task group swapping

    bool operator==(const Task &other) const {
        return unitId == other.unitId && (
                (data && other.data && data->ID == other.data->ID) ||
                (data == other.data)
        );
    }
};

namespace std {
template<> struct hash<Task>
{
    size_t operator()(const Task &b) const {
        return hash<int16_t>()(b.data->ID) ^ hash<uint16_t>()(b.unitId);
    }
};
}

struct Unit : public Entity
{
    enum HardcodedTypes {
        TownCenter = 109,

        FemaleVillager = 293,

        MaleVillager = 83,
        MaleLumberjack = 123,
        MaleStoneMiner = 124,
        MaleHunter = 122,
        MaleFarmer = 259,
        MaleForager = 120,
        MaleFisherman = 56,
        MaleGoldMiner = 579,
        MaleShepherd = 592,
        MaleBuilder = 118,
        MaleRepairer = 156,

        Docket = 45,
        Castle = 82,
        Market = 84,

        ArcheryRange = 87,
        Barracks = 12,
        Monastery = 104,
        SiegeWorkshop = 49,
        Stable = 101,

        Dock = 45,

        Mill = 68,
        LumberCamp = 562,
        MiningCamp = 584,

        PalisadeWall = 72,
        StoneWall = 117,
        FortifiedWall = 155,
        Gate = 487,

        Farm = 50,

        Cobra = 748,
        VMDL = 206,
        FuriousTheMonkeyBoy = 860,
    };

    typedef std::shared_ptr<Unit> Ptr;

    struct Annex {
        Unit::Ptr unit;
        MapPos offset;
    };

    enum class Stance {
        Aggressive,
        Defensive,
        StandGround,
        NoAttack
    } stance = Stance::Aggressive;

    // The blinking animation thing when it is selected as a target
    int targetBlinkTimeLeft = 0;

    Unit() = delete;
    Unit(const Unit &unit) = delete;

    Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager);

    ~Unit();

    float angle() const;
    void setAngle(const float angle);

    void prependAction(const ActionPtr &action);
    void queueAction(const ActionPtr &action);
    void setCurrentAction(const ActionPtr &action);
    void clearActionQueue();
    const ActionPtr &currentAction() const { return m_currentAction; }

    void snapPositionToGrid();

    bool update(Time time) override;

    const std::vector<const genie::Unit *> creatableUnits();

    static std::shared_ptr<Building> asBuilding(const Unit::Ptr &unit);

    bool selected = false;
    int playerId;
    std::weak_ptr<Player> player;
    std::vector<Annex> annexes;
    std::shared_ptr<Civilization> civilization;

    ResourceMap resources;

    virtual ScreenRect rect() const;
    virtual bool checkClick(const ScreenPos &pos) const;

    bool hasAutoTargets() const { return !m_autoTargetTasks.empty(); }
    void checkForAutoTargets();
    std::unordered_set<Task> availableActions();
    Task findMatchingTask(const genie::Task::ActionTypes &m_type, int targetUnit);
    Size selectionSize() const;

    virtual void setCreationProgress(float progress);
    void increaseCreationProgress(float progress);
    float creationProgress() const;
    float hitpointsLeft() const;
    float healthLeft() const;
    void takeDamage(const genie::unit::AttackOrArmor &attack, const float damageMultiplier);
    bool isDying() const;
    bool isDead() const;

    void setMap(const MapPtr &newMap) override;
    void setPosition(const MapPos &pos) override;

    void setUnitData(const genie::Unit &data_);
    const genie::Unit *data() const {return m_data; }

    int activeMissiles = 0;

    UnitManager &unitManager() const { return m_unitManager; }

    float distanceTo(const Unit::Ptr &otherUnit) const;

protected:
    Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager, const Type m_type);

    void removeAction(const ActionPtr &action);
    int taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state);
    void updateGraphic();

    const genie::Unit *m_data = nullptr;
    GraphicPtr movingGraphics;
    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;

    std::unordered_set<Task> m_autoTargetTasks;

    float m_creationProgress = 0.f;

    UnitManager &m_unitManager;

    float m_damageTaken = 0.f;
    Time m_prevTime = 0;
};


