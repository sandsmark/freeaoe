#pragma once

#include "IAction.h"
#include "mechanics/Unit.h"

class ActionAttack : public IAction
{
public:
    ActionAttack(const Unit::Ptr &attacker, const Unit::Ptr &target, const Task &task);
    ActionAttack(const Unit::Ptr &attacker, const MapPos &targetPos, const Task &task);

    genie::Task::ActionTypes taskType() const override { return genie::Task::Attack; }
    UnitState unitState() const override;
    UpdateResult update(Time time) override;

private:
    void spawnMissiles(const Unit::Ptr &source, const int unitId, const MapPos &target, const Unit::Ptr &targetUnit);
    bool unitFiresMissiles(const Unit::Ptr &unit);
    int missilesUnitCanFire(const Unit::Ptr &source);

    MapPos m_targetPosition;
    std::weak_ptr<Unit> m_targetUnit;
    Time m_lastAttackTime = 0;
    bool m_firing = false;
    bool m_attackGround = false;
};
