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

struct Unit;
struct Entity;

namespace comp {
class GraphicRender;
}

typedef std::shared_ptr<Entity> EntityPtr;
class Civilization;

struct Entity
{
public:
    enum class Type {
        None,
        Unit,
        MoveTargetMarker
    };
    const Type type = Type::None;

    Entity() = delete;

    virtual ~Entity();

    virtual bool update(Time time);

    MapPos position;

    virtual comp::GraphicRender &renderer() { return m_graphics; }

    static std::shared_ptr<Unit> asUnit(EntityPtr entity);

    const std::string readableName;

    bool isVisible = false;

protected:
    Entity(const Type type_, const std::string &name);

    comp::GraphicRender m_graphics;
    res::GraphicPtr defaultGraphics;
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

    const genie::Unit &data;

    Unit() = delete;

    Unit(const genie::Unit &data_, int playerId, std::shared_ptr<Civilization> civilization);

    bool selected = false;

    void setAngle(const float angle);

    void queueAction(ActionPtr action);
    void setCurrentAction(ActionPtr action);
    void removeAction(IAction *action);
    void clearActionQueue();
    const ActionPtr &currentAction() const { return m_currentAction; }


    bool update(Time time) override;

    const std::vector<const genie::Unit *> creatableUnits();

    int playerId;

    int constructors = 0;

    std::vector<Annex> annexes;

    virtual ScreenRect rect() const;

    virtual void setCreationProgress(float progress);
    void increaseCreationProgress(float progress);
    float creationProgress() const;

    std::unordered_set<const genie::Task*> availableActions();

    std::shared_ptr<Civilization> m_civilization;

protected:
    int taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state);

    res::GraphicPtr movingGraphics;
    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;
    float m_creationProgress = 0.f;
};

#endif // ENTITY_H
