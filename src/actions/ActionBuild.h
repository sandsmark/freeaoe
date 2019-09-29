#pragma once

#include "actions/IAction.h"

struct Building;
struct Unit;
using UnitPtr = std::shared_ptr<Unit>;

#include <genie/dat/UnitCommand.h>

#include <memory>

struct Building;

class ActionBuild : public IAction
{
public:
    ActionBuild(const UnitPtr &builder, const UnitPtr &building, const Task &task);
    ~ActionBuild();

    UpdateResult update(Time time) override;

    UnitState unitState() const override;

    genie::Task::ActionTypes taskType() const override { return genie::Task::Build; }

private:
    std::weak_ptr<Building> m_targetBuilding;
};

