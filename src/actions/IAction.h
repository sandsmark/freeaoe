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
#include <genie/dat/UnitCommand.h>

#include <memory>
#include <unordered_set>

namespace genie {
class Task;
}

struct Unit;
struct Task;
class Map;
class UnitManager;



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
        Fly
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

    const Type type = Type::None;

    static Task findMatchingTask(const int ownPlayerId, const std::shared_ptr<Unit> &target, const std::unordered_set<Task> &potentials);

    virtual UnitState unitState() const { return UnitState::Idle; }
    virtual genie::Task::ActionTypes taskType() const = 0;

    virtual ~IAction();

    /// @return true if action is done
    virtual UpdateResult update(Time time) = 0;

protected:
    IAction(const Type type_, const std::shared_ptr<Unit> &unit, UnitManager *unitManager);
    std::weak_ptr<Unit> m_unit;
    Time m_prevTime = 0;
    UnitManager *m_unitManager;
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
    }

    os << separator;
    os.separator = separator;

    return os;
}

inline LogPrinter operator <<(LogPrinter os, const genie::Task::ActionTypes actionType)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "genie::Task::";

    //:%s,\(.*\) =.*,case genie::Task::\1: os << "\1"; break;,
    switch(actionType) {
    case genie::Task::None: os << "None"; break;

    /// In AoC
    case genie::Task::Garrison: os << "Garrison"; break;
    case genie::Task::GatherRebuild: os << "GatherRebuild"; break;
    case genie::Task::Graze: os << "Graze"; break;
    case genie::Task::Combat: os << "Combat"; break;
    case genie::Task::Fly: os << "Fly"; break;
    case genie::Task::ScareHunt: os << "ScareHunt"; break;
    case genie::Task::UnloadBoat: os << "UnloadBoat"; break;
    case genie::Task::Guard: os << "Guard"; break;
    case genie::Task::SetInitialResources: os << "SetInitialResources"; break;
    case genie::Task::Build: os << "Build"; break;
    case genie::Task::Convert: os << "Convert"; break;
    case genie::Task::Heal: os << "Heal"; break;
    case genie::Task::Repair: os << "Repair"; break;
    case genie::Task::GetAutoConverted: os << "GetAutoConverted"; break;
    case genie::Task::RetreatToShootingRage: os << "RetreatToShootingRage"; break;
    case genie::Task::Hunt: os << "Hunt"; break;
    case genie::Task::Trade: os << "Trade"; break;
    case genie::Task::GenerateWonderVictory: os << "GenerateWonderVictory"; break;
    case genie::Task::FarmDeselectWhenBuilt: os << "FarmDeselectWhenBuilt"; break;
    case genie::Task::Loot: os << "Loot"; break;
    case genie::Task::UnpackAndAttack: os << "UnpackAndAttack"; break;
    case genie::Task::OffMapTrade1: os << "OffMapTrade1"; break;
    case genie::Task::PickupRelic: os << "PickupRelic"; break;
    case genie::Task::KidnapUnit: os << "KidnapUnit"; break;
    case genie::Task::DepositRelic: os << "DepositRelic"; break;

    /// Not in AoC
    case genie::Task::MoveTo: os << "MoveTo"; break;
    case genie::Task::Follow: os << "Follow"; break;
    case genie::Task::Explore: os << "Explore"; break;
    case genie::Task::Shoot: os << "Shoot"; break;
    case genie::Task::Attack: os << "Attack"; break;
    case genie::Task::Escape: os << "Escape"; break;
    case genie::Task::Num: os << "Num"; break;
    case genie::Task::MakeUnit: os << "MakeUnit"; break;
    case genie::Task::MakeTech: os << "MakeTech"; break;
    case genie::Task::DiscoveryArtifact: os << "DiscoveryArtifact"; break;
    case genie::Task::Housing: os << "Housing"; break;
    case genie::Task::Pack: os << "Pack"; break;
    case genie::Task::OffMapTrade0: os << "OffMapTrade0"; break;
    case genie::Task::ChargeAttack: os << "ChargeAttack"; break;
    case genie::Task::TransformUnit: os << "TransformUnit"; break;
    case genie::Task::Shear: os << "Shear"; break;

    /// Only in HD, I guess
    case genie::Task::HDSiegeTowerAbility: os << "HDSiegeTowerAbility"; break;
    case genie::Task::HDRegeneration: os << "HDRegeneration"; break;
    case genie::Task::HDFeitoria: os << "HDFeitoria"; break;

    case genie::Task::Stop: os << "Stop"; break;
    case genie::Task::AboutFace: os << "AboutFace"; break;
    case genie::Task::Wheel: os << "Wheel"; break;
    }

    os << separator;
    os.separator = separator;

    return os;
}

typedef std::shared_ptr<IAction> ActionPtr;

