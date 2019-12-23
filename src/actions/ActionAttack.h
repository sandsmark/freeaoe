#pragma once

#include "IAction.h"

struct Unit;
using UnitPtr = std::shared_ptr<Unit>;

#include <genie/dat/ActionType.h>

#include <memory>

class ActionAttack : public IAction
{
public:
    ActionAttack(const UnitPtr &attacker, const UnitPtr &target, const Task &task);
    ActionAttack(const UnitPtr &attacker, const MapPos &targetPos, const Task &task);

    genie::ActionType taskType() const override { return genie::ActionType::Attack; }
    UnitState unitState() const override;
    UpdateResult update(Time time) override;

private:
    void spawnMissiles(const UnitPtr &source, const int unitId, const MapPos &target, const UnitPtr &targetUnit);
    bool unitFiresMissiles(const UnitPtr &unit);
    int missilesUnitCanFire(const UnitPtr &source);

    MapPos m_targetPosition;
    std::weak_ptr<Unit> m_targetUnit;
    Time m_lastAttackTime = 0;
    bool m_firing = false;
    bool m_attackGround = false;
};
