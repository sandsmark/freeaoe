#pragma once

#include "IAction.h"
#include "mechanics/Unit.h"

struct Player;
class UnitManager;

class ActionDropOff : public IAction
{
public:
    ActionDropOff(const Unit::Ptr &unit, const Unit::Ptr &target, const Task &task);

    UpdateResult update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }
    genie::Task::ActionTypes taskType() const override { return genie::Task::ActionTypes(m_task.data->ActionType); }

private:
    std::weak_ptr<Unit> m_target;
    genie::ResourceType m_resourceType;
};

class ActionGather : public IAction
{
public:
    ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const Task &task);

    UpdateResult update(Time time) override;
    UnitState unitState() const override;
    genie::Task::ActionTypes taskType() const override { return genie::Task::ActionTypes(m_task.data->ActionType); }

private:
    void maybeDropOff(const Unit::Ptr &unit);
    Unit::Ptr findDropSite(const Unit::Ptr &unit);

    std::weak_ptr<Unit> m_target;
    genie::ResourceType m_resourceType;
};

