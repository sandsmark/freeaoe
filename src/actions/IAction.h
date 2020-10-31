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

#include "core/Types.h"

#include <genie/dat/ActionType.h>

#include <unordered_set>

struct Unit;
struct Task;

namespace genie {
class Task;
}

struct Task {
    Task(const genie::Task *t, int id);
    Task() = default;

    bool isValid() const { return taskId != -1; }

    int taskId = -1;
    int unitId = -1; // for task group swapping
    std::weak_ptr<Unit> target;

    // Raw pointer because we can assume that the dat file stays around for as long as we stay around
    const genie::Task *data = nullptr;


    bool operator==(const Task &other) const;
};

namespace std {
template<> struct hash<Task>
{
    size_t operator()(const Task &b) const {
        return hash<int16_t>()(b.taskId) ^ hash<uint16_t>()(b.unitId);
    }
};
}

class IAction
{
public:
    enum class Type {
        None,
        Move,
        PlaceOnMap,
        Build,
        Gather,
        DropOff,
        Attack,
        Fly,
        Garrison
    };

    enum UnitState {
        Idle,
        Moving,
        Working,
        Carrying,
        Proceeding,
        Attacking
    };

    enum class UpdateResult {
        Updated,
        NotUpdated,
        Completed,
        Failed
    };

    enum class AssignType {
        Replace,
        Queue
    };

    const Type type = Type::None;

    virtual UnitState unitState() const { return UnitState::Idle; }
    virtual genie::ActionType taskType() const = 0;

    static void assignTask(const Task &task, const std::shared_ptr<Unit> &unit, const AssignType assignType);

    virtual ~IAction();

    /// @return true if action is done
    virtual UpdateResult update(Time time) = 0;

    int requiredUnitID = -1;

protected:
    IAction(const Type type_, const std::shared_ptr<Unit> &unit, const Task &task);
//    IAction(const Type type_, const std::shared_ptr<Unit> &unit);
    std::weak_ptr<Unit> m_unit;
    Time m_prevTime = 0;
    Task m_task;
};

inline LogPrinter operator <<(LogPrinter os, const IAction::UnitState unitState)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "IAction::UnitState::";
    switch (unitState){
    case IAction::Idle: os << "Idle"; break;
    case IAction::Moving: os << "Moving"; break;
    case IAction::Working: os << "Working"; break;
    case IAction::Carrying: os << "Carrying"; break;
    case IAction::Proceeding: os << "Proceeding"; break;
    case IAction::Attacking: os << "Attacking"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const IAction::Type actionType)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "IAction::Type::";

    switch(actionType) {
    case IAction::Type::None: os << "None"; break;
    case IAction::Type::Move: os << "Move"; break;
    case IAction::Type::PlaceOnMap: os << "PlaceOnMap"; break;
    case IAction::Type::Build: os << "Build"; break;
    case IAction::Type::Gather: os << "Gather"; break;
    case IAction::Type::DropOff: os << "DropOff"; break;
    case IAction::Type::Attack: os << "Attack"; break;
    case IAction::Type::Fly: os << "Fly"; break;
    case IAction::Type::Garrison: os << "Garrison"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::ActionType actionType)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::Actions::";

    //:%s,\(.*\) =.*,case genie::Actions::\1: os << "\1"; break;,
    switch(actionType) {
    case genie::ActionType::None: os << "None"; break;

    /// In AoC
    case genie::ActionType::Garrison: os << "Garrison"; break;
    case genie::ActionType::GatherRebuild: os << "GatherRebuild"; break;
    case genie::ActionType::Graze: os << "Graze"; break;
    case genie::ActionType::Combat: os << "Combat"; break;
    case genie::ActionType::Fly: os << "Fly"; break;
    case genie::ActionType::ScareHunt: os << "ScareHunt"; break;
    case genie::ActionType::UnloadBoat: os << "UnloadBoat"; break;
    case genie::ActionType::Guard: os << "Guard"; break;
    case genie::ActionType::SetInitialResources: os << "SetInitialResources"; break;
    case genie::ActionType::Build: os << "Build"; break;
    case genie::ActionType::Convert: os << "Convert"; break;
    case genie::ActionType::Heal: os << "Heal"; break;
    case genie::ActionType::Repair: os << "Repair"; break;
    case genie::ActionType::GetAutoConverted: os << "GetAutoConverted"; break;
    case genie::ActionType::RetreatToShootingRage: os << "RetreatToShootingRage"; break;
    case genie::ActionType::Hunt: os << "Hunt"; break;
    case genie::ActionType::Trade: os << "Trade"; break;
    case genie::ActionType::GenerateWonderVictory: os << "GenerateWonderVictory"; break;
    case genie::ActionType::FarmDeselectWhenBuilt: os << "FarmDeselectWhenBuilt"; break;
    case genie::ActionType::Loot: os << "Loot"; break;
    case genie::ActionType::UnpackAndAttack: os << "UnpackAndAttack"; break;
    case genie::ActionType::OffMapTrade1: os << "OffMapTrade1"; break;
    case genie::ActionType::PickupRelic: os << "PickupRelic"; break;
    case genie::ActionType::KidnapUnit: os << "KidnapUnit"; break;
    case genie::ActionType::DepositRelic: os << "DepositRelic"; break;

    /// Not in AoC
    case genie::ActionType::MoveTo: os << "MoveTo"; break;
    case genie::ActionType::Follow: os << "Follow"; break;
    case genie::ActionType::Explore: os << "Explore"; break;
    case genie::ActionType::Shoot: os << "Shoot"; break;
    case genie::ActionType::Attack: os << "Attack"; break;
    case genie::ActionType::Escape: os << "Escape"; break;
    case genie::ActionType::Num: os << "Num"; break;
    case genie::ActionType::MakeUnit: os << "MakeUnit"; break;
    case genie::ActionType::MakeTech: os << "MakeTech"; break;
    case genie::ActionType::DiscoveryArtifact: os << "DiscoveryArtifact"; break;
    case genie::ActionType::Housing: os << "Housing"; break;
    case genie::ActionType::Pack: os << "Pack"; break;
    case genie::ActionType::OffMapTrade0: os << "OffMapTrade0"; break;
    case genie::ActionType::ChargeAttack: os << "ChargeAttack"; break;
    case genie::ActionType::TransformUnit: os << "TransformUnit"; break;
    case genie::ActionType::Shear: os << "Shear"; break;

    /// Only in HD, I guess
    case genie::ActionType::HDSiegeTowerAbility: os << "HDSiegeTowerAbility"; break;
    case genie::ActionType::HDRegeneration: os << "HDRegeneration"; break;
    case genie::ActionType::HDFeitoria: os << "HDFeitoria"; break;

    case genie::ActionType::Stop: os << "Stop"; break;
    case genie::ActionType::AboutFace: os << "AboutFace"; break;
    case genie::ActionType::Wheel: os << "Wheel"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

typedef std::shared_ptr<IAction> ActionPtr;

