#pragma once

#include "core/IAction.h"
#include "core/Entity.h"

struct Player;
class UnitManager;

class ActionDropOff : public IAction
{
public:
    ActionDropOff(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task);

    bool update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }

private:
    std::weak_ptr<Unit> m_target;
    const genie::Task *m_task;
};

class ActionGather : public IAction
{
public:
    ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task, UnitManager *unitManager);

    bool update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }

private:
    MapPos findDropSite(const Unit::Ptr &unit);

    std::weak_ptr<Unit> m_target;
    const genie::Task *m_task;
    UnitManager *m_unitManager;
};

