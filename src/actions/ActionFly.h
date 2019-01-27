#pragma once

#include "IAction.h"

class ActionFly : public IAction
{
public:
    ActionFly(const std::shared_ptr<Unit> &unit, UnitManager *unitManager);

    UpdateResult update(Time time) override;
    UnitState unitState() const override;

private:
    Time m_lastUpdateTime = 0;
    Time m_lastTurnTime = 0;
    Time m_lastStateChangeTime = 0;
    UnitState m_currentState = UnitState::Proceeding;
};
