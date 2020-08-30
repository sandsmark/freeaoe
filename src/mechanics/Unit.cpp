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

#include <genie/dat/Unit.h>
#include <genie/dat/ResourceUsage.h>
#include <genie/dat/UnitCommand.h>
#include <genie/dat/unit/Action.h>
#include <genie/dat/unit/AttackOrArmor.h>
#include <genie/dat/unit/Building.h>
#include <genie/dat/unit/Combat.h>
#include <genie/dat/unit/Creatable.h>
#include <genie/dat/unit/DamageGraphic.h>
#include <genie/dat/unit/Moving.h>
#include <genie/dat/UnitCommand.h>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <map>
#include <string>
#include <utility>

#include "Civilization.h"
#include "Map.h"
#include "Building.h"
#include "UnitManager.h"
#include "audio/AudioPlayer.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/Utility.h"
#include "global/EventManager.h"
#include "mechanics/Player.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "resource/Sprite.h"
#include "render/GraphicRender.h"

std::shared_ptr<Unit> Unit::fromEntity(const EntityPtr &entity) noexcept
{
    if (!entity) {
        return nullptr;
    }
    if (!entity->isUnit()) {
        return nullptr;
    }
    return std::static_pointer_cast<Unit>(entity);
}

std::shared_ptr<Building> Unit::asBuilding(const Unit::Ptr &unit) noexcept
{
    if (!unit) {
        return nullptr;
    }

    if (!unit->isBuilding()) {
        return nullptr;
    }
    return std::static_pointer_cast<Building>(unit);
}

std::shared_ptr<Building> Unit::asBuilding(const std::weak_ptr<Unit> &unit) noexcept
{
    return asBuilding(unit.lock());
}

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    actions(this),
    m_playerId(player_->playerId),
    m_player(player_),
    m_unitManager(unitManager)
{
    m_renderer->setPlayerColor(player_->playerColor);
    m_renderer->setCivId(player_->civilization.id());

    setUnitData(data_);
    m_creationProgress = m_data->Creatable.TrainTime;

    player_->addUnit(this);
}

Unit::Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager, const Entity::Type type) :
    Entity(type, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    actions(this),
    m_playerId(player_->playerId),
    m_player(player_),
    m_unitManager(unitManager)
{
    m_renderer->setPlayerColor(player_->playerColor);

    setUnitData(data_);
    m_creationProgress = m_data->Creatable.TrainTime;

    player_->addUnit(this);
}

Unit::~Unit()
{
    Player::Ptr owner = m_player.lock();
    if (owner) {
        // TODO: don't do that here
        forEachVisibleTile([&](const int tileX, const int tileY) {
            owner->visibility->removeUnitLookingAt(tileX, tileY);
        });

        owner->removeUnit(this);
    }
}

void Unit::setAngle(const float angle) noexcept
{
    m_angle = angle;
    m_renderer->setAngle(angle);
}

bool Unit::update(Time time) noexcept
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

    if (actions.m_currentAction) {
        ActionPtr currentAction = actions.m_currentAction;

        IAction::UnitState prevState = currentAction->unitState();

        switch(currentAction->update(time)) {
        case IAction::UpdateResult::Completed:
            DBG << "Action completed" << currentAction->type;
            actions.removeAction(currentAction);
            break;
        case IAction::UpdateResult::Updated:
            updated = true;
            break;
        case IAction::UpdateResult::NotUpdated:
            break;
        case IAction::UpdateResult::Failed:
            WARN << currentAction->type << "action failed";
            actions.m_actionQueue.clear();
            actions.removeAction(currentAction);
            break;
        }

        if (!actions.m_currentAction || currentAction != actions.m_currentAction || prevState != actions.m_currentAction->unitState()) {
            updateGraphic();
        }
    }


    return Entity::update(time) || updated;
}

void Unit::setPlayer(const std::shared_ptr<Player> &player)
{
    m_player = player;
    m_playerId = player->playerId;
}

ScreenRect Unit::rect() const noexcept
{
    ScreenRect ret = m_renderer->rect();

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

bool Unit::checkClick(const ScreenPos &pos) const noexcept
{
    if (m_renderer->checkClick(pos)) {
        return true;
    }

    for (const Annex &annex : annexes) {
        if (annex.unit->checkClick(pos + annex.offset.toScreen())) {
            return true;
        }
    }
    return false;
}

void Unit::setCreationProgress(float progress) noexcept
{
    if (m_data->Type == genie::Unit::BuildingType) {
        if (m_creationProgress < m_data->Creatable.TrainTime && progress >= m_data->Creatable.TrainTime) {
            m_renderer->setSprite(defaultGraphics);
        } else if (m_creationProgress == m_data->Creatable.TrainTime && progress < m_data->Creatable.TrainTime) {
            m_renderer->setSprite(m_data->Building.ConstructionGraphicID);
        }
    }

    m_creationProgress = std::min(progress, float(m_data->Creatable.TrainTime));

    if (m_data->Type == genie::Unit::BuildingType && progress < m_data->Creatable.TrainTime) {
        m_renderer->setAngle(M_PI_2 + 2. * M_PI * (creationProgress()));
    } else {
        m_renderer->setAngle(m_angle); // blarf
    }
}

void Unit::increaseCreationProgress(float progress) noexcept
{
    setCreationProgress(m_creationProgress + progress);
}

float Unit::creationProgress() const noexcept
{
    if (IS_UNLIKELY(m_data->Creatable.TrainTime == 0)) {
        return 1;
    }

    return m_creationProgress / float(m_data->Creatable.TrainTime);
}

void Unit::takeDamage(const genie::unit::AttackOrArmor &attack, const float damageMultiplier) noexcept
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
        kill();
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
                m_renderer->setDamageOverlay(graphic->GraphicID);
                break;
            case genie::unit::DamageGraphic::OverlayRandomly:
                WARN << "Random overlay damage graphics not implemented yet";
                m_renderer->setDamageOverlay(graphic->GraphicID);
                break;
            case genie::unit::DamageGraphic::ReplaceGraphic:
                m_renderer->setSprite(graphic->GraphicID);
                break;
            }
        }
    }

}

void Unit::kill() noexcept
{
    m_damageTaken = data()->HitPoints;

    m_renderer->setPlaySounds(true);
    m_renderer->setSprite(m_data->DyingGraphic);

    if (data()->DyingSound != -1) {
        Player::Ptr owner = m_player.lock();
        if (owner) {
            AudioPlayer::instance().playSound(data()->DyingSound, owner->civilization.id());
        }
    }
}

bool Unit::isDying() const noexcept
{
    if (m_damageTaken < m_data->HitPoints) {
        return false;
    }

    // Check if the death animation has finished
    if (m_renderer->currentFrame() >= m_renderer->frameCount() - 1) {
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

bool Unit::isDead() const noexcept
{
    if (m_damageTaken < m_data->HitPoints) {
        return false;
    }

    // Check if the death animation has finished
    if (m_renderer->currentFrame() < m_renderer->frameCount() - 1) {
        return false;
    }

    if (m_data->CanBeGathered) {
        for (const ResourceEntry &resource : resources) {
            if (resource.second > 0) {
                return false;
            }
        }
    }

    return true;
}

Size Unit::selectionSize() const noexcept
{
    return Size(data()->OutlineSize.x * Constants::TILE_SIZE, data()->OutlineSize.y * Constants::TILE_SIZE);
}

void Unit::setMap(const MapPtr &newMap) noexcept
{
    for (Annex &annex : annexes) {
        annex.unit->setMap(newMap);
    }

    Entity::setMap(newMap);
}

void Unit::setPosition(const MapPos &pos, const bool initial)
{
    if (pos == position()) {
        return;
    }

    Player::Ptr owner = player().lock();

    // TODO merf, don't really want this to happen here, maybe use events?
    if (!initial && owner) {
        forEachVisibleTile([&](const int tileX, const int tileY) {
            owner->visibility->removeUnitLookingAt(tileX, tileY);
        });
    }

    MapPos oldTilePosition = position() / Constants::TILE_SIZE;
    MapPos newTilePosition = pos / Constants::TILE_SIZE;
    oldTilePosition.round();
    newTilePosition.round();
    if (oldTilePosition != newTilePosition) {
        EventManager::unitMoved(this, oldTilePosition, newTilePosition);
    }

    Entity::setPosition(pos, initial);

    if (owner) {
        forEachVisibleTile([&](const int tileX, const int tileY) {
            owner->visibility->addUnitLookingAt(tileX, tileY);
        });
    } else {
        WARN << "No player set!";
    }

    for (Annex &annex : annexes) {
        annex.unit->setPosition(pos + annex.offset, initial);
    }

    if (data()->Type >= genie::Unit::CombatantType) {
        m_unitManager.onCombatantUnitsMoved();
    }
}

void Unit::setUnitData(const genie::Unit &data_) noexcept
{
    m_data = &data_;

    defaultGraphics = AssetManager::Inst()->getGraphic(m_data->StandingGraphic.first);
    if (m_data->Moving.WalkingGraphic >= 0) {
        movingGraphics = AssetManager::Inst()->getGraphic(m_data->Moving.WalkingGraphic);
    }

    if (!defaultGraphics) {
        WARN << "Failed to load default graphics";
    }

    m_renderer->setSprite(defaultGraphics);

    actions.m_autoTargetTasks.clear();
    for (const Task &task : actions.availableActions()) {
        if (!task.data->EnableTargeting) {
            continue;
        }
        actions.m_autoTargetTasks.insert(task);
    }
}

Size Unit::clearanceSize() const noexcept
{
    return Size(data()->Size.x * Constants::TILE_SIZE, data()->Size.y * Constants::TILE_SIZE);
}

float Unit::tallness()
{
    return data()->Size.z * Constants::TILE_SIZE;
}

void Unit::forEachVisibleTile(const std::function<void (const int, const int)> &action)
{
    const int los = data()->LineOfSight;
    const int tileXOffset = position().x / Constants::TILE_SIZE;
    const int tileYOffset = position().y / Constants::TILE_SIZE;
    for (int y=-los; y<= los; y++) {
        for (int x=-los; x<= los; x++) {
            if (x*x + y*y < los*los) {
                action(x + tileXOffset, y + tileYOffset);
            }
        }
    }
}

float Unit::hitpointsLeft() const noexcept
{
    return std::max((data()->HitPoints * creationProgress() - m_damageTaken), 0.f);
}

float Unit::healthLeft() const noexcept
{
    const float healthpoints = hitpointsLeft();
    if (healthpoints <= 0) {
        return 0.f;
    }

    return healthpoints / data()->HitPoints;
}

void Unit::updateGraphic()
{
    if (hitpointsLeft() <= 0 && !isDying()) {
        m_renderer->setSprite(m_data->DyingGraphic);
        return;
    }

    if ((actions.m_currentAction && actions.m_currentAction->unitState() != IAction::Idle) || isDying()) {
        m_renderer->setPlaySounds(true);
    } else {
        m_renderer->setPlaySounds(false);
    }

    if (!actions.m_currentAction) {
        m_renderer->setSprite(defaultGraphics);
        return;
    }

    SpritePtr graphic;

    switch (actions.m_currentAction->type) {
    case IAction::Type::Move:
        graphic = movingGraphics;
        for (const genie::Task &task : DataManager::Inst().getTasks(m_data->ID)) {
            if (task.ActionType != genie::ActionType::GatherRebuild && task.ActionType != genie::ActionType::Hunt) {
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
        if (actions.m_currentAction->unitState() == IAction::UnitState::Attacking && data()->Combat.AttackGraphic != -1) {
            graphic = AssetManager::Inst()->getGraphic(data()->Combat.AttackGraphic);
            graphic->setRunOnce(true);
        } else {
            graphic = defaultGraphics;
        }
        break;
    default:
        graphic = AssetManager::Inst()->getGraphic(actions.taskGraphicId(actions.m_currentAction->taskType(), actions.m_currentAction->unitState()));
        break;
    }

    if (!graphic || !graphic->isValid()) {
        DBG << "No graphic" << actions.m_currentAction->type << debugName;
        graphic = defaultGraphics;
    }

    m_renderer->setSprite(graphic);
}


