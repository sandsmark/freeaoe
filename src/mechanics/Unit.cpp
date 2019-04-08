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

#include "Unit.h"
#include "audio/AudioPlayer.h"
#include "resource/LanguageManager.h"
#include "mechanics/Civilization.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include "mechanics/Building.h"
#include "core/Constants.h"
#include "resource/DataManager.h"
#include "UnitManager.h"
#include <genie/dat/Unit.h>
#include "core/Utility.h"

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    playerId(player_->playerId),
    player(player_),
    civilization(player_->civ),
    m_unitManager(unitManager)
{
    m_renderer.setPlayerId(playerId);
    m_renderer.setCivId(civilization->id());

    setUnitData(data_);
    m_creationProgress = m_data->Creatable.TrainTime;

    player_->addUnit(this);
}

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager, const Entity::Type type) :
    Entity(type, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    playerId(player_->playerId),
    player(player_),
    civilization(player_->civ),
    m_unitManager(unitManager)
{
    m_renderer.setPlayerId(playerId);

    setUnitData(data_);
    m_creationProgress = m_data->Creatable.TrainTime;

    player_->addUnit(this);
}

Unit::~Unit()
{
    Player::Ptr owner = player.lock();
    if (owner) {
        owner->removeUnit(this);
    }
}

bool Unit::update(Time time)
{
    if (isDying()) {
        return Entity::update(time);
    }

    if (isDead()) {
        return false;
    }

    bool updated = false;

    if (m_prevTime) {
        int timeDelta = time - m_prevTime;

        if (targetBlinkTimeLeft) {
            targetBlinkTimeLeft -= timeDelta;
        }

        if (targetBlinkTimeLeft < 0) {
            targetBlinkTimeLeft = 0;
        }
    }

    m_prevTime = time;

    for (Annex &annex : annexes) {
        updated = annex.unit->update(time) || updated;
    }

    if (m_currentAction) {
        ActionPtr currentAction = m_currentAction;

        IAction::UnitState prevState = currentAction->unitState();

        switch(currentAction->update(time)) {
        case IAction::UpdateResult::Completed:
            DBG << "Action completed" << currentAction->type;
            removeAction(currentAction);
            break;
        case IAction::UpdateResult::Updated:
            updated = true;
            break;
        case IAction::UpdateResult::NotUpdated:
            break;
        case IAction::UpdateResult::Failed:
            WARN << currentAction->type << "action failed";
            m_actionQueue.clear();
            removeAction(currentAction);
            break;
        }

        if (!m_currentAction || currentAction != m_currentAction || prevState != m_currentAction->unitState()) {
            updateGraphic();
        }
        if (!m_currentAction) {
            checkForAutoTargets();
        }
    }


    return Entity::update(time) || updated;
}

void Unit::snapPositionToGrid()
{
    MapPos newPos = position();
    newPos /= Constants::TILE_SIZE;
    newPos += Size(m_data->Size);
    newPos.round();
    newPos -= Size(m_data->Size);
    newPos *= Constants::TILE_SIZE;

    setPosition(newPos);
}

const std::vector<const genie::Unit *> Unit::creatableUnits()
{
    if (creationProgress() < 1.) {
        return {};
    }

    return civilization->creatableUnits(m_data->ID);
}

std::shared_ptr<Building> Unit::asBuilding(const Unit::Ptr &unit)
{
    if (!unit) {
        return nullptr;
    }

    if (!unit->isBuilding()) {
        return nullptr;
    }
    return std::static_pointer_cast<Building>(unit);
}

ScreenRect Unit::rect() const
{
    ScreenRect ret = m_renderer.rect();

    for (const Annex &annex : annexes) {
        ScreenRect annexRect = annex.unit->rect();
        if (annexRect.isEmpty()) {
            continue;
        }
        annexRect = annexRect + annex.offset.toScreen();
        if (ret.isEmpty()) {
            ret = annex.unit->rect();
        } else {
            ret += annex.unit->rect();
        }
    }

    return ret;
}

bool Unit::checkClick(const ScreenPos &pos) const
{
    if (m_renderer.checkClick(pos)) {
        return true;
    }

    for (const Annex &annex : annexes) {
        if (annex.unit->checkClick(pos + annex.offset.toScreen())) {
            return true;
        }
    }
    return false;
}

void Unit::setCreationProgress(float progress)
{
    if (m_data->Type == genie::Unit::BuildingType) {
        if (m_creationProgress < m_data->Creatable.TrainTime && progress >= m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(defaultGraphics);
        } else if (m_creationProgress == m_data->Creatable.TrainTime && progress < m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(m_data->Building.ConstructionGraphicID);
        }
    }

    m_creationProgress = std::min(progress, float(m_data->Creatable.TrainTime));

    if (m_data->Type == genie::Unit::BuildingType && progress < m_data->Creatable.TrainTime) {
        m_renderer.setAngle(M_PI_2 + 2. * M_PI * (creationProgress()));
    }
}

void Unit::increaseCreationProgress(float progress)
{
    setCreationProgress(m_creationProgress + progress);
}

float Unit::creationProgress() const
{
    if (IS_UNLIKELY(m_data->Creatable.TrainTime == 0)) {
        return 1;
    }

    return m_creationProgress / float(m_data->Creatable.TrainTime);
}

void Unit::takeDamage(const genie::unit::AttackOrArmor &attack, const float damageMultiplier)
{
    if (hitpointsLeft() <= 0) {
        return;
    }

    float newDamage = 0;
    for (const genie::unit::AttackOrArmor &armor : m_data->Combat.Armours) {
        if (attack.Class != armor.Class) {
            continue;
        }

        newDamage += std::max(attack.Amount - armor.Amount, 0);
    }
    newDamage *= damageMultiplier;
    newDamage = std::max(newDamage, 1.f);

    m_damageTaken += newDamage;

    if (hitpointsLeft() <= 0) {
        m_renderer.setGraphic(m_data->DyingGraphic);

        DBG  << data()->DyingSound;
        if (data()->DyingSound != -1) {
            AudioPlayer::instance().playSound(data()->DyingSound, civilization->id());
        }
    } else {
        const int damagedPercent = 100 * m_damageTaken / data()->HitPoints;
        const genie::unit::DamageGraphic *graphic = nullptr;
        for (const genie::unit::DamageGraphic &damageGraphic : data()->DamageGraphics) {
            if (damagedPercent < damageGraphic.DamagePercent) {
                continue;
            }
            if (!graphic || damageGraphic.DamagePercent > graphic->DamagePercent) {
                graphic = &damageGraphic;
            }
        }
        if (graphic) {
            switch (graphic->ApplyMode) {
            case genie::unit::DamageGraphic::OverlayGraphic:
                m_renderer.setDamageOverlay(graphic->GraphicID);
                break;
            case genie::unit::DamageGraphic::OverlayRandomly:
                WARN << "Random overlay damage graphics not implemented yet";
                m_renderer.setDamageOverlay(graphic->GraphicID);
                break;
            case genie::unit::DamageGraphic::ReplaceGraphic:
                m_renderer.setGraphic(graphic->GraphicID);
                break;
            }
        }
    }

}

bool Unit::isDying() const
{
    if (m_damageTaken < m_data->HitPoints) {
        return false;
    }

    // Check if the death animation has finished
    if (m_renderer.currentFrame() >= m_renderer.frameCount() - 1) {
        return false;
    }

    // If it is a gatherable resource, check if there is any left
    if (m_data->CanBeGathered) {
        for (const ResourceEntry resource : resources) {
            if (resource.second > 0) {
                return false;
            }
        }
    }

    // Otherwise we are dying indeed;
    return true;
}

bool Unit::isDead() const
{
    if (m_damageTaken < m_data->HitPoints) {
        return false;
    }

    // Check if the death animation has finished
    if (m_renderer.currentFrame() < m_renderer.frameCount() - 1) {
        return false;
    }

    if (m_data->CanBeGathered) {
        for (const ResourceEntry resource : resources) {
            if (resource.second > 0) {
                return false;
            }
        }
    }

    return true;
}

void Unit::checkForAutoTargets()
{
    if (stance != Stance::Aggressive || m_autoTargetTasks.empty() || m_currentAction) {
        return;
    }

    const float maxRange = m_data->LineOfSight * Constants::TILE_SIZE;
    Task newTask;
    Unit::Ptr target;

    for (const Unit::Ptr &other : m_unitManager.units()) {
        if (other->id == this->id) {
            continue;
        }
        if (other->playerId == UnitManager::GaiaID) {
            // I don't think we should auto-target gaia units?
            continue;
        }
        if (other->position().distance(position()) > maxRange) {
            continue;
        }
        newTask = IAction::findMatchingTask(playerId, other, m_autoTargetTasks);
        if (!newTask.data) {
            continue;
        }

        // TODO: should only prefer civilians (and I think only wolves? lions?)
        // should attack others as well
        // Maybe check combat level instead? but then suddenly we get wolves trying to find a path to ships
        if (newTask.data->ActionType == genie::Task::Combat && data()->Type == genie::Unit::PredatorAnimal && other->data()->Type != genie::Unit::Civilian) {
            continue;
        }

        if (newTask.data) {
            target = other;
            break;
        }
    }

    if (!newTask.data || !target) {
        return;
    }

    m_unitManager.assignTask(newTask, Entity::asUnit(shared_from_this()), target);
}

std::unordered_set<Task> Unit::availableActions()
{
    std::unordered_set<Task> tasks;
    for (const genie::Task &task : DataManager::Inst().getTasks(m_data->ID)) {
        tasks.insert(Task(task, m_data->ID));
    }

    if (!m_data->Action.TaskSwapGroup) {
        return tasks;
    }

    for (const genie::Unit *swappable : civilization->swappableUnits(m_data->Action.TaskSwapGroup)) {
        for (const genie::Task &task : DataManager::Inst().getTasks(swappable->ID)) {
            tasks.insert(Task(task, swappable->ID));
        }
    }

    return tasks;
}

Task Unit::findMatchingTask(const genie::Task::ActionTypes &type, int targetUnit)
{
    for (const Task &task : availableActions()) {
        if (task.data->ActionType == type && task.data->UnitID == targetUnit) {
            return task;
        }
    }

    return Task();
}

Size Unit::selectionSize() const
{
    return Size(data()->OutlineSize.x * Constants::TILE_SIZE, data()->OutlineSize.y * Constants::TILE_SIZE);
}

void Unit::setMap(const MapPtr &newMap)
{
    for (Annex &annex : annexes) {
        annex.unit->setMap(newMap);
    }

    Entity::setMap(newMap);
}

void Unit::setPosition(const MapPos &pos)
{
    for (Annex &annex : annexes) {
        annex.unit->setPosition(pos + annex.offset);
    }
    Entity::setPosition(pos);

    if (data()->Type >= genie::Unit::CombatantType) {
        m_unitManager.onCombatantUnitsMoved();
    }
}

void Unit::setUnitData(const genie::Unit &data_)
{
    m_data = &data_;

    defaultGraphics = AssetManager::Inst()->getGraphic(m_data->StandingGraphic.first);
    if (m_data->Moving.WalkingGraphic >= 0) {
        movingGraphics = AssetManager::Inst()->getGraphic(m_data->Moving.WalkingGraphic);
    }

    if (!defaultGraphics) {
        WARN << "Failed to load default graphics";
    }

    m_renderer.setGraphic(defaultGraphics);

    m_autoTargetTasks.clear();
    for (const Task &task : availableActions()) {
        if (!task.data->EnableTargeting) {
            continue;
        }
        m_autoTargetTasks.insert(task);
    }
}

DecayingEntity::Ptr Unit::createCorpse() const
{
    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "no owner for corpse";
        return nullptr;
    }

    if (m_data->DeadUnitID == -1) {
        return nullptr;
    }

    const genie::Unit &corpseData = owner->civ->unitData(m_data->DeadUnitID);
    float decayTime = corpseData.ResourceDecay * corpseData.ResourceCapacity;

    for (const genie::Unit::ResourceStorage &r : corpseData.ResourceStorages) {
        if (r.Type == int(genie::ResourceType::CorpseDecayTime)) {
            decayTime = r.Amount;
            break;
        }
    }

    // I don't think this is really correct, but it works better
    if (corpseData.ResourceDecay == -1 || (corpseData.ResourceDecay != 0 && corpseData.ResourceCapacity == 0)) {
        DBG << "decaying forever";
        decayTime = std::numeric_limits<float>::infinity();
    }
    DecayingEntity::Ptr corpse = std::make_shared<DecayingEntity>(corpseData.StandingGraphic.first, decayTime);
    corpse->renderer().setPlayerId(playerId);
    corpse->setPosition(position());
    corpse->renderer().setAngle(angle());
    corpse->setMap(map());

    return corpse;
}

float Unit::distanceTo(const Unit::Ptr &otherUnit) const
{
    const float xSize = (otherUnit->data()->Size.x + data()->Size.x) * Constants::TILE_SIZE;
    const float ySize = (otherUnit->data()->Size.y + data()->Size.y) * Constants::TILE_SIZE;
    const float xDistance = std::abs(otherUnit->position().x - position().x);
    const float yDistance = std::abs(otherUnit->position().y - position().y);

    return std::hypot(std::max(xDistance - xSize, 0.f), std::max(yDistance - ySize, 0.f));
}

float Unit::hitpointsLeft() const
{
    return std::max((data()->HitPoints * creationProgress() - m_damageTaken), 0.f);
}

float Unit::healthLeft() const
{
    const float healthpoints = hitpointsLeft();
    if (healthpoints <= 0) {
        return 0.f;
    }

    return healthpoints / data()->HitPoints;
}

int Unit::taskGraphicId(const genie::Task::ActionTypes taskType, const IAction::UnitState state)
{
    for (const genie::Task &task : DataManager::Inst().getTasks(m_data->ID)) {
        if (task.ActionType != taskType/* &&
                !(taskType == genie::Task::GatherRebuild && task.ActionType == genie::Task::Hunt)*/) {
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

    return m_data->StandingGraphic.first;
}

void Unit::updateGraphic()
{
    if (hitpointsLeft() <= 0) {
        m_renderer.setGraphic(m_data->DyingGraphic);
        return;
    }

    if (m_currentAction && m_currentAction->unitState() != IAction::Idle) {
        m_renderer.setPlaySounds(true);
    } else {
        m_renderer.setPlaySounds(false);
    }

    if (!m_currentAction) {
        m_renderer.setGraphic(defaultGraphics);
        return;
    }

    GraphicPtr graphic;

    switch (m_currentAction->type) {
    case IAction::Type::Move:
        graphic = movingGraphics;
        for (const genie::Task &task : DataManager::Inst().getTasks(m_data->ID)) {
            if (task.ActionType != genie::Task::GatherRebuild && task.ActionType != genie::Task::Hunt) {
                continue;
            }

            if (task.ResourceIn == -1) {
                continue;
            }

            if (resources[genie::ResourceType(task.ResourceIn)] > 0) {
                if (task.CarryingGraphicID != -1) {
                    graphic = AssetManager::Inst()->getGraphic(task.CarryingGraphicID);
                    break;
                }
            }
        }

        break;
    case IAction::Type::Attack:
        if (m_currentAction->unitState() == IAction::UnitState::Attacking) {
            DBG << "Setting graphic";
            graphic = AssetManager::Inst()->getGraphic(data()->Combat.AttackGraphic);
            graphic->setRunOnce(true);
        }
        break;
    default:
        graphic = AssetManager::Inst()->getGraphic(taskGraphicId(m_currentAction->taskType(), m_currentAction->unitState()));
        break;
    }

    if (!graphic) {
        DBG << "No graphic";
        graphic = defaultGraphics;
    }

    m_renderer.setGraphic(graphic);
}

float Unit::angle() const
{
    return m_renderer.angle();
}

void Unit::setAngle(const float angle)
{
    m_renderer.setAngle(angle);
}

void Unit::prependAction(const ActionPtr &action)
{
    m_actionQueue.push_front(std::move(m_currentAction));
    m_currentAction = action;
    updateGraphic();
}

void Unit::queueAction(const ActionPtr &action)
{
    if (!m_currentAction) {
        setCurrentAction(action);
    } else {
        m_actionQueue.push_back(action);
    }
}

void Unit::setCurrentAction(const ActionPtr &action)
{
    m_currentAction = action;

    updateGraphic();
}

void Unit::removeAction(const ActionPtr &action)
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

void Unit::clearActionQueue()
{
    m_actionQueue.clear();
    m_currentAction.reset();
    updateGraphic();
}
