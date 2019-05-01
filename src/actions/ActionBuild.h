#pragma once

#include "actions/IAction.h"
#include "mechanics/Unit.h"

class ActionBuild : public IAction
{

public:
    ActionBuild(const Unit::Ptr &builder, const Unit::Ptr &building);
    ~ActionBuild();

    UpdateResult update(Time time) override;

    UnitState unitState() const override;

    genie::Task::ActionTypes taskType() const override { return genie::Task::Build; }

private:
    std::weak_ptr<Building> m_targetBuilding;
};

