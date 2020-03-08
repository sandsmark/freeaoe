#pragma once

#include "actions/IAction.h"

struct Building;
struct Unit;
using UnitPtr = std::shared_ptr<Unit>;

#include <memory>

struct Building;

class ActionBuild : public IAction
{
public:
    ActionBuild(const UnitPtr &builder, const Task &task);
    ~ActionBuild();

    UpdateResult update(Time time) override;

    UnitState unitState() const override;

    genie::ActionType taskType() const override { return genie::ActionType::Build; }

private:
    std::weak_ptr<Building> m_targetBuilding;
};

