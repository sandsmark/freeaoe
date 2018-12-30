#pragma once

#include "IAction.h"
#include "mechanics/Unit.h"

class ActionAttack : public IAction
{
public:
    ActionAttack(const Unit::Ptr &attacker, const Unit::Ptr &target, UnitManager *unitManager);
    ActionAttack(const Unit::Ptr &attacker, const MapPos &target, UnitManager *unitManager);

    UnitState unitState() const override;
    UpdateResult update(Time time) override;

private:
    MapPos m_targetPosition;
    std::weak_ptr<Unit> m_targetUnit;
    Time m_lastAttackTime = 0;
    bool m_firing = false;
};
