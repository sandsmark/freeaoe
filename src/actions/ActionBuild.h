#pragma once

#include "actions/IAction.h"
#include "mechanics/Unit.h"

class ActionBuild : public IAction
{

public:
    ActionBuild(const Unit::Ptr &builder, const Unit::Ptr &building, UnitManager *unitManager);
    ~ActionBuild();

    UpdateResult update(Time time) override;

    UnitState unitState() const override;

private:
    std::weak_ptr<Building> m_targetBuilding;
};

