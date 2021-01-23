#include "ActionAttack.h"

#include "ActionMove.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "mechanics/Civilization.h"
#include "mechanics/Missile.h"
#include "mechanics/Player.h"
#include "mechanics/UnitManager.h"
#include "resource/DataManager.h"

#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/Combat.h>
#include <genie/dat/unit/Creatable.h>

#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

ActionAttack::ActionAttack(const Unit::Ptr &attacker, const Task &task) :
    IAction(IAction::Type::Attack, attacker, task),
    m_targetUnit(task.target)
{
    Unit::Ptr target = task.target.lock();
    if (!target) {
        WARN << "target gone even before we started attacking";
        return;
    }
    m_targetPosition = target->position();
    if (target->playerId() == attacker->playerId()) {
        m_targetUnit.reset();
    }
    const int attackGraphic = attacker->data()->Combat.AttackGraphic;
    if (attackGraphic != -1) {
        m_frameDelay = attacker->data()->Combat.FrameDelay * DataManager::Inst().getGraphic(attackGraphic).FrameDuration;
    }
}

ActionAttack::ActionAttack(const Unit::Ptr &attacker, const MapPos &targetPos, const Task &task) :
    IAction(IAction::Type::Attack, attacker, task),
    m_targetPosition(targetPos),
    m_attackGround(true)
{
}

IAction::UnitState ActionAttack::unitState() const
{
    if (m_firing) {
        return IAction::UnitState::Attacking;
    } else {
        return IAction::UnitState::Idle;
    }
}

IAction::UpdateResult ActionAttack::update(Time time)
{
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        // Our unit died
        return IAction::UpdateResult::Completed;
    }

    Unit::Ptr targetUnit = m_targetUnit.lock();
    if (!targetUnit && !m_attackGround) { // we lost our target unit, and we're not attacking the ground
        DBG << "Target unit gone";
        return IAction::UpdateResult::Completed;
    }

    // Update target position if we're attacking a unit
    if (targetUnit) {
        m_targetPosition = targetUnit->position();
    }


    // Need to use this more complex thing because when checking distance to a target
    // we need to find the distance to the closest part of it, not the center of the unit.
    const float distance = (targetUnit ?
                unit->distanceTo(targetUnit) :
                unit->distanceTo(m_targetPosition)
        ) / Constants::TILE_SIZE; // everything is defined by tile size in the dat files

    const bool overlaps = targetUnit ? targetUnit->mapRect().overlaps(unit->mapRect()) :
                                       unit->mapRect().contains(m_targetPosition);

    // Check if we are too far away
    if (!overlaps && distance > unit->data()->Combat.MaxRange) {
        if (!unit->data()->Speed) {
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }
        DBG << unit->debugName << "is too far away" << distance << unit->data()->Combat.MaxRange;

        std::shared_ptr<ActionMove> moveAction = ActionMove::moveUnitTo(unit, targetUnit);

        moveAction->maxDistance = unit->data()->Combat.MaxRange * Constants::TILE_SIZE;
        unit->actions.prependAction(moveAction);

        return IAction::UpdateResult::NotUpdated;
    }

    // Check if we are too close
    const float minDistance = unit->data()->Combat.MinRange * Constants::TILE_SIZE;
    if (minDistance > 0.f && m_targetPosition.distance(unit->position()) < minDistance) {
        if (!unit->data()->Speed) { // Too close, and the unit is stationary
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }

        if (!unit->actions.findAnyTask(genie::ActionType::RetreatToShootingRage, -1).data) {
            return IAction::UpdateResult::Failed;
        }

        const float angleToTarget = unit->position().angleTo(m_targetPosition);

        float targetX = m_targetPosition.x + cos(angleToTarget + M_PI) * minDistance;
        float targetY = m_targetPosition.y + sin(angleToTarget + M_PI) * minDistance;

        std::shared_ptr<ActionMove> moveAction = ActionMove::moveUnitTo(unit, MapPos(targetX, targetY), m_task);
        unit->actions.prependAction(moveAction);
        return IAction::UpdateResult::NotUpdated;
    }

    if (unitFiresMissiles(unit) && missilesUnitCanFire(unit) <= 0) {
        return IAction::UpdateResult::NotUpdated;
    }

    // Update the displayed angle
    const ScreenPos screenPosition = unit->position().toScreen();
    const ScreenPos targetScreenPosition = m_targetPosition.toScreen();
    unit->setAngle(screenPosition.angleTo(targetScreenPosition));

//    if (!m_lastAttackTime) {
//        m_lastAttackTime = time + unit->data()->Combat.ReloadTime; // skip the reloading
//        m_firing = false;
//        return IAction::UpdateResult::Updated;
//    }
    const float timeSinceLastAttack = (time - unit->lastAttackTime) * 0.0015;

    if (m_frameDelay > 0) {
        if (timeSinceLastAttack >= unit->data()->Combat.ReloadTime) {
            m_firing = false;
        }
    } else {
        if (timeSinceLastAttack < unit->data()->Combat.DisplayedReloadTime) {
            m_firing = true;
        } else {
            m_firing = false;
        }
    }

    // Check if we're still reloading
    if (timeSinceLastAttack < unit->data()->Combat.ReloadTime + m_frameDelay) {
        return IAction::UpdateResult::NotUpdated;
    }

    // Did we kill our target?
    if (targetUnit && targetUnit->healthLeft() <= 0.f) {
        return IAction::UpdateResult::Completed;
    }
    unit->lastAttackTime = time;

    if (m_frameDelay > 0) {
        m_firing = true;
    }

    // TODO: Create a flare here owned by the owner of the targeted unit, to show where the attack is coming from

    // Do the actual attack
    if (unit->data()->Creatable.SecondaryProjectileUnit != -1) { // I think we should prefer the secondary, for some reason, at least those are cooler
        spawnMissiles(unit, unit->data()->Creatable.SecondaryProjectileUnit, targetUnit);
    } else if (unit->data()->Combat.ProjectileUnitID != -1) {
        spawnMissiles(unit, unit->data()->Combat.ProjectileUnitID, targetUnit);
    } else if (targetUnit) {
        // Not firing missiles, deal damage directly
        for (const genie::unit::AttackOrArmor &attack : unit->data()->Combat.Attacks) {
            targetUnit->receiveAttack(attack, 1.); // todo: damage multiplier from elevation
        }
    } else {
        WARN << "No target unit, and not firing missiles";
        return IAction::UpdateResult::Completed;
    }

    return IAction::UpdateResult::Updated;
}

void ActionAttack::spawnMissiles(const Unit::Ptr &source, const int unitId, const Unit::Ptr &targetUnit)
{
    DBG << "Spawning missile" << unitId;

    const genie::XYZF &graphicDisplacement = source->data()->Combat.GraphicDisplacement;
//    const std::array<float, 3> &spawnArea = source->data()->Creatable.ProjectileSpawningArea; // TODO
    DBG << source->data()->Combat.AccuracyPercent << source->data()->Creatable.SecondaryProjectileUnit;

    Player::Ptr owner = source->player().lock();
    if (!owner) {
        WARN << "no owning player";
        return;
    }
    const genie::Unit &gunit = owner->civilization.unitData(unitId);

//    float widthDispersion = 0.;
//    if (source->data()->Creatable.TotalProjectiles > 1) {
//        widthDispersion = spawnArea[0] * Constants::TILE_SIZE / source->data()->Creatable.TotalProjectiles;
//    }
    for (int i=0; i<missilesUnitCanFire(source); i++) {
        MapPos individualTarget = m_targetPosition;
        if (targetUnit) {
            individualTarget.z += targetUnit->tallness()/2;
        }
        Missile::Ptr missile = std::make_shared<Missile>(gunit, source, individualTarget, targetUnit);
        missile->setMap(source->map());

        float offsetX = graphicDisplacement.x;
        float offsetY = graphicDisplacement.y;

        MapPos pos = source->position() - source->clearanceSize()/2;
        pos.x += -sin(source->angle()) * offsetX + cos(source->angle()) * offsetX;
        pos.y +=  cos(source->angle()) * offsetY + sin(source->angle()) * offsetY;
        pos.z += graphicDisplacement.z  * Constants::TILE_SIZE_HEIGHT;

        // TODO
//        if (spawnArea[2] > 0) {
//            pos.x += (rand() % int((100 - spawnArea[2]) * spawnArea[0] * Constants::TILE_SIZE)) / 100.;
//            pos.y += (rand() % int((100 - spawnArea[2]) * spawnArea[1] * Constants::TILE_SIZE)) / 100.;
//        }
        missile->setPosition(pos, true);
        DBG << "Missile spawned at" << pos;
        source->unitManager().addMissile(missile);
    }
}

bool ActionAttack::unitFiresMissiles(const Unit::Ptr &unit)
{
    return (unit->data()->Creatable.SecondaryProjectileUnit != -1) || (unit->data()->Combat.ProjectileUnitID != -1);
}

int ActionAttack::missilesUnitCanFire(const Unit::Ptr &source)
{
    return std::min(int(source->data()->Creatable.TotalProjectiles), source->data()->Creatable.MaxTotalProjectiles - source->activeMissiles);
}
