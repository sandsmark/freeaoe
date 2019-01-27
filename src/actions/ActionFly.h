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
};
