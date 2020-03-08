#pragma once

#include "actions/IAction.h"
#include "core/Types.h"

#include <genie/dat/ResourceUsage.h>

#include <memory>

class ActionDropOff : public IAction
{
public:
    ActionDropOff(const std::shared_ptr<Unit> &unit, const Task &task);

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
    ActionGather(const std::shared_ptr<Unit> &unit, const Task &task);

    UpdateResult update(Time time) override;
    UnitState unitState() const override;
    genie::ActionType taskType() const override;

private:
    UpdateResult maybeDropOff(const std::shared_ptr<Unit> &unit);
    std::shared_ptr<Unit> findDropSite(const std::shared_ptr<Unit> &unit);

    std::weak_ptr<Unit> m_target;
    genie::ResourceType m_resourceType;
};

