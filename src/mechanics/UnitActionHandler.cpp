#include "UnitActionHandler.h"

#include "Unit.h"

#include "Player.h"
#include "Map.h"
#include "UnitManager.h"

#include "resource/DataManager.h"

UnitActionHandler::UnitActionHandler(Unit *unit) :
    m_unit(unit)
{

}

TaskSet UnitActionHandler::availableActions() const noexcept
{
    const genie::Unit *data = m_unit->m_data;

    TaskSet tasks;
    for (const genie::Task &task : DataManager::Inst().getTasks(data->ID)) {

        // TODO: some units (archery range) have a combat task, but no attacks
        // Could be if it needs garrisoned units?
        if (task.ActionType == genie::ActionType::Combat && data->Combat.Attacks.empty()) {
            continue;
        }

        tasks.add(Task(&task, data->ID));
    }

    if (!data->Action.TaskSwapGroup) {
        return tasks;
    }

    Player::Ptr owner = m_unit->player().lock();
    if (!owner) {
        WARN << "Lost our player";
        return {};
    }

    for (const genie::Unit *swappable : owner->civilization.swappableUnits(data->Action.TaskSwapGroup)) {
        for (const genie::Task &task : DataManager::Inst().getTasks(swappable->ID)) {
            if (task.ActionType == genie::ActionType::Combat && data->Combat.Attacks.empty()) {
                continue;
            }
            tasks.add(Task(&task, swappable->ID));
        }
    }

    return tasks;

}

Task UnitActionHandler::findAnyTask(const genie::ActionType &type, int targetUnit) noexcept
{
    TaskSet available = availableActions();
    for (const Task &task : available) {
        if (task.data->ActionType == type && task.data->UnitID == targetUnit) {
            return task;
        }
    }

    for (const Task &task : available) {
        if (task.data->ActionType == type && task.data->UnitID == -1) { // less specific
            return task;
        }
    }

    return Task();

}

Task UnitActionHandler::findTaskWithTarget(const std::shared_ptr<Unit> &target)
{
    return findMatchingTask(m_unit->player().lock(), target, availableActions());
}

Task UnitActionHandler::findMatchingTask(const std::shared_ptr<Player> &ownPlayer, const std::shared_ptr<Unit> &target, const TaskSet &potentials)
{
    if (!ownPlayer){
        WARN << "no player passed for task finding";
        return Task();
    }
    for (const Task &task : potentials) {
        const genie::Task *action = task.data;

        switch (action->TargetDiplomacy) {
        case genie::Task::TargetSelf:
            if (target->playerId() != ownPlayer->playerId) {
                continue;
            }
            break;
        case genie::Task::TargetNeutralsEnemies: // TODO: neutrals
            if (target->playerId() == ownPlayer->playerId) {
                continue;
            }
            break;

        case genie::Task::TargetGaiaOnly:
            if (target->playerId() != UnitManager::GaiaID) {
                continue;
            }
            break;
        case genie::Task::TargetSelfAllyGaia:
            if (target->playerId() != ownPlayer->playerId && target->playerId() != UnitManager::GaiaID && !ownPlayer->isAllied(target->playerId())) {
                continue;
            }
            break;
        case genie::Task::TargetGaiaNeutralEnemies:
        case genie::Task::TargetOthers:
            if (target->playerId() == ownPlayer->playerId) {
                continue;
            }
            if (ownPlayer->isAllied(target->playerId())) {
                continue;
            }
            break;
        case genie::Task::TargetAnyDiplo:
        case genie::Task::TargetAnyDiplo2:
        default:
            break;
        }

        if (action->ActionType == genie::ActionType::Garrison) {
            continue;
        }

        if (target->creationProgress() < 1) {
            if (action->ActionType == genie::ActionType::Build) {
                return task;
            }

            continue;
        }

        if (action->UnitID == target->data()->ID) {
            return task;
        }

        if (action->ClassID == target->data()->Class) {
            return task;
        }
    }

    // Try more generic targeting
    for (const Task &task : potentials) {
        const genie::Task *action = task.data;
        if (action->ActionType != genie::ActionType::Combat) {
            continue;
        }
        if (action->TargetDiplomacy != genie::Task::TargetGaiaNeutralEnemies && action->TargetDiplomacy != genie::Task::TargetNeutralsEnemies) {
            continue;
        }
        if (ownPlayer->playerId == target->playerId()) {
            continue;
        }

        if (target->data()->Type < genie::Unit::CombatantType) {
            continue;
        }

        return task;
    }

    return Task();

}

Task UnitActionHandler::checkForAutoTargets() noexcept
{
    if (m_unit->stance != Unit::Stance::Aggressive || m_autoTargetTasks.size() == 0 || m_currentAction) {
        return {};
    }

    const MapPtr map = m_unit->m_map.lock();
    if (!map) {
        WARN << "no map";
        return {};
    }

    const genie::Unit *data = m_unit->m_data;

    const int los = data->LineOfSight;

    Task newTask;
    Unit::Ptr target;

    const MapPos position = m_unit->position();
    const int left = position.x / Constants::TILE_SIZE - los;
    const int top = position.y / Constants::TILE_SIZE - los;
    const int right = position.x / Constants::TILE_SIZE + los;
    const int bottom = position.y / Constants::TILE_SIZE + los;

    float closestDistance = los * Constants::TILE_SIZE;
    const std::vector<std::weak_ptr<Entity>> entities = map->entitiesBetween(left, top, right, bottom);
    for (const std::weak_ptr<Entity> &entity : entities) {
        const Unit::Ptr other = Unit::fromEntity(entity);
        if (!other) {
            continue;
        }

        if (other->id == m_unit->id) {
            continue;
        }
        if (other->playerId() == UnitManager::GaiaID) {
            // I don't think we should auto-target gaia units?
            continue;
        }

        const float distance = m_unit->distanceTo(other);

        if (distance > closestDistance) {
            continue;
        }

        const Task potentialTask = findMatchingTask(m_unit->player().lock(), other, m_autoTargetTasks);
        if (!potentialTask.data) {
            continue;
        }

        // TODO: should only prefer civilians (and I think only wolves? lions?)
        // should attack others as well
        // Maybe check combat level instead? but then suddenly we get wolves trying to find a path to ships
        if (potentialTask.data->ActionType == genie::ActionType::Combat && data->Class == genie::Unit::PredatorAnimal) {
            if (other->data()->Creatable.CreatableType != genie::unit::Creatable::VillagerType) {
                continue;
            }
        }

        if (potentialTask.data) {
            newTask = potentialTask;
            target = other;
            closestDistance = distance;
        }
    }

    if (!newTask.data || !target) {
        return {};
    }

    DBG << "found auto task" << newTask.data->actionTypeName() << "for" << m_unit->debugName;
    newTask.target = target;
    return newTask;
}

void UnitActionHandler::removeAction(const ActionPtr &action)
{
    if (action == m_currentAction) {
        if (!m_actionQueue.empty()) {
            DBG << "changing action to queued one" << m_actionQueue.front()->type;
            setCurrentAction(m_actionQueue.front());
            m_actionQueue.pop_front();
        } else {
            setCurrentAction(nullptr);
            DBG << "no actions queued";
        }
    } else {
        // fuck stl
        std::deque<ActionPtr>::iterator it = std::find(m_actionQueue.begin(), m_actionQueue.end(), action);

        if (it != std::end(m_actionQueue)) {
            m_actionQueue.erase(it);
        }
    }
}

void UnitActionHandler::clearActionQueue() noexcept
{
    m_actionQueue.clear();
    m_currentAction.reset();
    m_unit->updateGraphic();
}

int UnitActionHandler::taskGraphicId(const genie::ActionType taskType, const IAction::UnitState state)
{
    const genie::Unit *data = m_unit->m_data;

    for (const genie::Task &task : DataManager::Inst().getTasks(data->ID)) {
        if (task.ActionType != taskType/* &&
                !(taskType == genie::Actions::GatherRebuild && task.ActionType == genie::Actions::Hunt)*/) {
            continue;
        }

        switch(state) {
        case IAction::Idle:
        case IAction::Proceeding:
            if (task.ProceedingGraphicID != -1) {
                return task.ProceedingGraphicID;
            }
            break;
        case IAction::Moving:
            if (task.MovingGraphicID != -1) {
                return task.MovingGraphicID;
            }
            break;
        case IAction::Working:
            if (task.WorkingGraphicID != -1) {
                return task.WorkingGraphicID;
            }
            break;
        case IAction::Carrying:
            if (task.CarryingGraphicID != -1){
                return task.CarryingGraphicID;
            }
            break;
        default:
            break;
        }
    }
    WARN << "Failed to task graphic for task type" << taskType << "and unit state" << state;

    return data->StandingGraphic.first;
}

void UnitActionHandler::prependAction(const ActionPtr &action) noexcept
{
    m_actionQueue.push_front(std::move(m_currentAction));
    m_currentAction = action;
    m_unit->updateGraphic();
}

void UnitActionHandler::queueAction(const ActionPtr &action) noexcept
{
    if (!m_currentAction) {
        setCurrentAction(action);
    } else {
        m_actionQueue.push_back(action);
    }
}

void UnitActionHandler::setCurrentAction(const ActionPtr &action) noexcept
{
    m_currentAction = action;


    Player::Ptr owner = m_unit->player().lock();
    if (!owner) {
        WARN << "Lost our player";
        return;
    }

    if (action && action->requiredUnitID != -1 && action->requiredUnitID != m_unit->m_data->ID) {
        m_unit->setUnitData(owner->civilization.unitData(action->requiredUnitID));
    }

    m_unit->updateGraphic();
}
