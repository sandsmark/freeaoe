#pragma once

#include "actions/IAction.h"
#include "core/Types.h"
#include "mechanics/Unit.h"

#include <genie/dat/ResourceUsage.h>

#include <memory>

class ActionDropOff : public IAction
{
public:
    ActionDropOff(const Unit::Ptr &unit, const Unit::Ptr &target, const Task &task);

    UpdateResult update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }
    genie::ActionType taskType() const override;

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
    genie::ActionType taskType() const override;

private:
    void maybeDropOff(const Unit::Ptr &unit);
    Unit::Ptr findDropSite(const Unit::Ptr &unit);

    std::weak_ptr<Unit> m_target;
    genie::ResourceType m_resourceType;
};

