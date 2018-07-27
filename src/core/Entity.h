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

#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <deque>
#include "Utility.h"
#include "render/GraphicRender.h"

#include "IComponent.h"
#include "IAction.h"
#include <genie/dat/UnitCommand.h>

namespace genie {
class Unit;
}

class Map;
typedef std::shared_ptr<Map> MapPtr;

struct Unit;
struct Entity;

namespace comp {
class GraphicRender;
}

typedef std::shared_ptr<Entity> EntityPtr;
class Civilization;

struct MoveTargetMarker;

struct Entity: std::enable_shared_from_this<Entity>
{
    const size_t id;

    enum class Type {
        None,
        Unit,
        MoveTargetMarker
    };
    const Type type = Type::None;

    Entity() = delete;

    virtual ~Entity();

    virtual bool update(Time time);


    virtual comp::GraphicRender &renderer() { return m_graphics; }

    static std::shared_ptr<Unit> asUnit(EntityPtr entity);

    const std::string debugName;

    bool isVisible = false;

    const MapPos &position() const { return m_position; }
    void setPosition(const MapPos &pos, const MapPtr &map);

protected:
    Entity(const Type type_, const std::string &name);

    comp::GraphicRender m_graphics;
    res::GraphicPtr defaultGraphics;

private:
    friend struct MoveTargetMarker;
    MapPos m_position;
};

struct MoveTargetMarker : public Entity
{
    typedef std::shared_ptr<MoveTargetMarker> Ptr;

    MoveTargetMarker();

    void moveTo(const MapPos &pos);

    bool update(Time time) override;

private:
    bool m_isRunning = false;
};

struct Task {
    Task(const genie::Task &t, uint16_t id) : data(&t), unitId(id) {}
    Task() = default;

    const genie::Task *data = nullptr;
    const uint16_t unitId = 0; // for task group swapping

    bool operator==(const Task &other) const {
        return unitId == other.unitId && (
                (data && other.data && data->ID == other.data->ID) ||
                (data == other.data)
        );
    }
};

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

    Unit() = delete;
    Unit(const Unit &unit) = delete;

    Unit(const genie::Unit &data_, int playerId, std::shared_ptr<Civilization> civilization);

    bool selected = false;

    void setAngle(const float angle);

    void queueAction(ActionPtr action);
    void setCurrentAction(ActionPtr action);
    void removeAction(IAction *action);
    void clearActionQueue();
    const ActionPtr &currentAction() const { return m_currentAction; }

    void snapPositionToGrid(const MapPtr &map);

    bool update(Time time) override;

    const std::vector<const genie::Unit *> creatableUnits();

    int playerId;

    int constructors = 0;

    std::vector<Annex> annexes;

    virtual ScreenRect rect() const;

    virtual void setCreationProgress(float progress);
    void increaseCreationProgress(float progress);
    float creationProgress() const;

    std::unordered_set<Task> availableActions();

    std::shared_ptr<Civilization> m_civilization;

    void setUnitData(const genie::Unit &data_);

    const genie::Unit *data() const {return m_data; }

protected:
    int taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state);

    const genie::Unit *m_data = nullptr;
    res::GraphicPtr movingGraphics;
    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;
    float m_creationProgress = 0.f;
};

namespace std {

template<> struct hash<Task>
{
    size_t operator()(const Task &b) const {
        return hash<int16_t>()(b.data->ID) ^ hash<uint16_t>()(b.unitId);
    }
};
}

#endif // ENTITY_H
