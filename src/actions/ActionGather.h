#pragma once

#include "IAction.h"
#include "mechanics/Unit.h"

struct Player;
class UnitManager;

class ActionDropOff : public IAction
{
public:
    ActionDropOff(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task, UnitManager *unitManager);

    UpdateResult update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }

private:
    std::weak_ptr<Unit> m_target;
    const genie::Task *m_task;
};

class ActionGather : public IAction
{
public:
    ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task, UnitManager *unitManager);

    UpdateResult update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }

private:
    Unit::Ptr findDropSite(const Unit::Ptr &unit);

    std::weak_ptr<Unit> m_target;
    const genie::Task *m_task;
};

