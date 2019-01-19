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
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")", unitManager.map()),
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

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager, const Entity::Type type) :
    Entity(type, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")", unitManager.map()),
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

    for (Annex &annex : annexes) {
        updated = annex.unit->update(time) || updated;
    }

    if (m_currentAction) {
        IAction::UnitState prevState = m_currentAction->unitState();

        switch(m_currentAction->update(time)) {
        case IAction::UpdateResult::Completed:
            removeAction(m_currentAction);
            break;
        case IAction::UpdateResult::Updated:
            updated = true;
            break;
        case IAction::UpdateResult::NotUpdated:
            break;
        }

        if (!m_currentAction || prevState != m_currentAction->unitState()) {
            DBG << "action change";
            updateGraphic();
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
        ret += annex.unit->rect();
    }

    return ret;
}

void Unit::setCreationProgress(float progress)
{
    if (m_data->Type == genie::Unit::BuildingType) {
        if (m_creationProgress < m_data->Creatable.TrainTime && progress >= m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(defaultGraphics);
        } else if (m_creationProgress == m_data->Creatable.TrainTime && progress < m_data->Creatable.TrainTime) {
            m_renderer.setGraphic(AssetManager::Inst()->getGraphic(m_data->Building.ConstructionGraphicID));
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
        m_renderer.setGraphic(AssetManager::Inst()->getGraphic(m_data->DyingGraphic));
    }
}

bool Unit::isDying() const
{
    return m_damageTaken >= m_data->HitPoints && m_renderer.currentFrame() < m_renderer.frameCount() - 1;
}

bool Unit::isDead() const
{
    return m_damageTaken >= m_data->HitPoints && m_renderer.currentFrame() >= m_renderer.frameCount() - 1;
}

std::unordered_set<Task> Unit::availableActions()
{
    std::unordered_set<Task> tasks;
    for (const genie::Task &task : DataManager::datFile().UnitHeaders[m_data->ID].TaskList) {
        tasks.insert(Task(task, m_data->ID));
    }

    if (!m_data->Action.TaskSwapGroup) {
        return tasks;
    }

    for (const genie::Unit *swappable : civilization->swappableUnits(m_data->Action.TaskSwapGroup)) {
        for (const genie::Task &task : DataManager::datFile().UnitHeaders[swappable->ID].TaskList) {
            tasks.insert(Task(task, swappable->ID));
        }
    }

    return tasks;
}

Task Unit::findMatchingTask(const genie::Task::ActionTypes &type)
{
    for (const Task &task : availableActions()) {
        if (task.data->ActionType == type) {
            return task;
        }
    }

    return Task();
}

void Unit::setPosition(const MapPos &pos)
{
    for (Annex &annex : annexes) {
        annex.unit->setPosition(pos + annex.offset);
    }
    Entity::setPosition(pos);
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
}

DecayingEntity::Ptr Unit::createCorpse() const
{
    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "no owner for corpse";
        return nullptr;
    }

    const genie::Unit &corpseData = owner->civ->unitData(m_data->DeadUnitID);
    float decayTime = corpseData.ResourceDecay * corpseData.ResourceCapacity;

    // I don't think this is really correct, but it works better
    if (corpseData.ResourceDecay == -1 || (corpseData.ResourceDecay != 0 && corpseData.ResourceCapacity == 0)) {
        decayTime = std::numeric_limits<float>::infinity();
    }
    DecayingEntity::Ptr corpse = std::make_shared<DecayingEntity>(m_map.lock(), corpseData.StandingGraphic.first, decayTime);
    corpse->renderer().setPlayerId(playerId);
    corpse->setPosition(position());

    return corpse;
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
    for (const genie::Task &task : DataManager::datFile().UnitHeaders[m_data->ID].TaskList) {
        if (task.ActionType != taskType) {
            continue;
        }
        switch(state) {
        case IAction::Idle:
        case IAction::Proceeding:
            return task.ProceedingGraphicID;
            break;
        case IAction::Moving:
            return task.MovingGraphicID;
            break;
        case IAction::Working:
            return task.WorkingGraphicID;
            break;
        case IAction::Carrying:
            return task.CarryingGraphicID;
            break;
        default:
            break;
        }
    }

    return m_data->StandingGraphic.first;
}

void Unit::updateGraphic()
{
    GraphicPtr graphic;
    if (m_currentAction) {
        switch (m_currentAction->type) {
        case IAction::Type::Move:
            graphic = movingGraphics;
            break;
        case IAction::Type::Build:
            graphic = AssetManager::Inst()->getGraphic(taskGraphicId(genie::Task::Build, m_currentAction->unitState()));
            break;
        case IAction::Type::Gather:
            graphic = AssetManager::Inst()->getGraphic(taskGraphicId(genie::Task::GatherRebuild, m_currentAction->unitState()));
            break;
        case IAction::Type::Attack:
            if (m_currentAction->unitState() == IAction::UnitState::Attacking) {
                DBG << "Setting graphic";
                graphic = AssetManager::Inst()->getGraphic(data()->Combat.AttackGraphic);
                graphic->setRunOnce(true);
            }
            break;
        default:
            break;
        }
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
        m_currentAction.reset();
        m_renderer.setGraphic(defaultGraphics);

        if (!m_actionQueue.empty()) {
            DBG << "changing action to queued one";
            setCurrentAction(m_actionQueue.front());
            m_actionQueue.pop_front();
        } else {
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
