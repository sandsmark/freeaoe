#pragma once

#include "core/IAction.h"
#include "Unit.h"

class ActionBuild : public IAction
{

public:
    ActionBuild(const Unit::Ptr &builder, const Unit::Ptr &building, UnitManager *unitManager);
    ~ActionBuild();

    UpdateResult update(Time time) override;

    UnitState unitState() const override;

private:
    std::weak_ptr<Unit> m_targetBuilding;
};

