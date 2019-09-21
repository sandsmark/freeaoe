#include "ActionAttack.h"
#include "ActionMove.h"
#include "ActionGather.h"
#include "audio/AudioPlayer.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Missile.h"
#include "core/Constants.h"
#include "mechanics/Player.h"
#include "mechanics/Civilization.h"
#include <genie/dat/Unit.h>

ActionAttack::ActionAttack(const Unit::Ptr &attacker, const Unit::Ptr &target, const Task &task) :
    IAction(IAction::Type::Attack, attacker, task),
    m_targetPosition(target->position()),
    m_targetUnit(target)
{
    if (target->playerId == attacker->playerId) {
        m_targetUnit.reset();
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
        return IAction::UpdateResult::Completed;
    }

    Unit::Ptr targetUnit = m_targetUnit.lock();
    if (!targetUnit && !m_attackGround) {
        DBG << "Target unit gone";
        return IAction::UpdateResult::Completed;
    }

    if (targetUnit) {
        m_targetPosition = targetUnit->position();
    }

    ScreenPos screenPosition = unit->position().toScreen();
    ScreenPos targetScreenPosition = m_targetPosition.toScreen();
    unit->setAngle(screenPosition.angleTo(targetScreenPosition));

    if (unitFiresMissiles(unit) && missilesUnitCanFire(unit) <= 0) {
        return IAction::UpdateResult::NotUpdated;
    }

    float timeSinceLastAttack = (time - m_lastAttackTime) * 0.0015;

    if (timeSinceLastAttack < unit->data()->Combat.DisplayedReloadTime) {
        m_firing = true;
    } else {
        m_firing = false;
    }

    const float angleToTarget = unit->position().toScreen().angleTo(m_targetPosition.toScreen());
    unit->setAngle(angleToTarget);
    const float distance = unit->position().distance(m_targetPosition) / Constants::TILE_SIZE;

    bool inRange = true;
    if (targetUnit) {
        const float xSize = (targetUnit->data()->Size.x + unit->data()->Size.x) * Constants::TILE_SIZE + unit->data()->Combat.MaxRange + 10;
        const float ySize = (targetUnit->data()->Size.y + unit->data()->Size.y) * Constants::TILE_SIZE + unit->data()->Combat.MaxRange + 10;
        const float xDistance = std::abs(targetUnit->position().x - unit->position().x);
        const float yDistance = std::abs(targetUnit->position().y - unit->position().y);
        if (xDistance > xSize || yDistance > ySize) {
            inRange = false;
        }
    }

    if (!inRange && distance > unit->data()->Combat.MaxRange) {
        if (!unit->data()->Speed) {
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }

        const float angleToTarget = unit->position().angleTo(m_targetPosition);

        float targetX = m_targetPosition.x + cos(angleToTarget + M_PI) * unit->data()->Combat.MaxRange * Constants::TILE_SIZE / 1.1;
        float targetY = m_targetPosition.y + sin(angleToTarget + M_PI) * unit->data()->Combat.MaxRange * Constants::TILE_SIZE / 1.1;

        unit->prependAction(ActionMove::moveUnitTo(unit, MapPos(targetX, targetY), m_task));
        return IAction::UpdateResult::NotUpdated;
    }
    if (distance < unit->data()->Combat.MinRange) {
        if (!unit->data()->Speed) {
            DBG << "this unit can't move...";
            return IAction::UpdateResult::Failed;
        }

        if (unit->findMatchingTask(genie::Task::RetreatToShootingRage, -1).data) {
            const float angleToTarget = unit->position().angleTo(m_targetPosition);

            float targetX = m_targetPosition.x + cos(angleToTarget + M_PI) * unit->data()->Combat.MinRange * Constants::TILE_SIZE * 1.1;
            float targetY = m_targetPosition.y + sin(angleToTarget + M_PI) * unit->data()->Combat.MinRange * Constants::TILE_SIZE * 1.1;

            unit->prependAction(ActionMove::moveUnitTo(unit, MapPos(targetX, targetY), m_task));
            return IAction::UpdateResult::NotUpdated;
        }

        return IAction::UpdateResult::Failed;
    }

    if (timeSinceLastAttack < unit->data()->Combat.ReloadTime) {
        return IAction::UpdateResult::NotUpdated;
    }

    if (targetUnit && targetUnit->healthLeft() <= 0.f) {
        return IAction::UpdateResult::Completed;
    }
    m_lastAttackTime = time;

    // TODO: Create a flare here owned by the owner of the targeted unit, to show where the attack is coming from

    if (unit->data()->Creatable.SecondaryProjectileUnit != -1) { // I think we should prefer the secondary, for some reason, at least those are cooler
        spawnMissiles(unit, unit->data()->Creatable.SecondaryProjectileUnit, m_targetPosition, targetUnit);
        return IAction::UpdateResult::Updated;
    } else if (unit->data()->Combat.ProjectileUnitID != -1) {
        spawnMissiles(unit, unit->data()->Combat.ProjectileUnitID,  m_targetPosition, targetUnit);
        return IAction::UpdateResult::Updated;
    } else {
        for (const genie::unit::AttackOrArmor &attack : unit->data()->Combat.Attacks) {
            targetUnit->takeDamage(attack, 1.); // todo: damage multiplier
        }
    }

    return IAction::UpdateResult::Updated;
}

void ActionAttack::spawnMissiles(const Unit::Ptr &source, const int unitId, const MapPos &target, const Unit::Ptr &targetUnit)
{
    DBG << "Spawning missile" << unitId;

    const std::vector<float> &graphicDisplacement = source->data()->Combat.GraphicDisplacement;
    const std::vector<float> &spawnArea = source->data()->Creatable.ProjectileSpawningArea;
    DBG << source->data()->Combat.AccuracyPercent << source->data()->Creatable.SecondaryProjectileUnit;

    Player::Ptr owner = source->player.lock();
    if (!owner) {
        WARN << "no owning player";
        return;
    }
    const genie::Unit &gunit = owner->civilization.unitData(unitId);

    float widthDispersion = 0.;
    if (source->data()->Creatable.TotalProjectiles > 1) {
        widthDispersion = spawnArea[0] * Constants::TILE_SIZE / source->data()->Creatable.TotalProjectiles;
    }
    for (int i=0; i<missilesUnitCanFire(source); i++) {
        MapPos individualTarget = target;
        individualTarget.x +=  -cos(source->angle()) * i*widthDispersion - spawnArea[0]/2.;
        individualTarget.y +=  sin(source->angle()) * i*widthDispersion - spawnArea[1]/2.;
        Missile::Ptr missile = std::make_shared<Missile>(gunit, source, individualTarget, targetUnit);
        missile->setMap(source->map());

        missile->setBlastType(Missile::BlastType(source->data()->Combat.BlastAttackLevel), source->data()->Combat.BlastWidth);

        float offsetX = graphicDisplacement[0];
        float offsetY = graphicDisplacement[1];

        MapPos pos = source->position();
        pos.x += -sin(source->angle()) * offsetX + cos(source->angle()) * offsetX;
        pos.y +=  cos(source->angle()) * offsetY + sin(source->angle()) * offsetY;
        pos.z += graphicDisplacement[2];

        if (spawnArea[2] > 0) {
            pos.x += (rand() % int((100 - spawnArea[2]) * spawnArea[0] * Constants::TILE_SIZE)) / 100.;
            pos.y += (rand() % int((100 - spawnArea[2]) * spawnArea[1] * Constants::TILE_SIZE)) / 100.;
        }
        missile->setPosition(pos);
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
