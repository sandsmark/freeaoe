#pragma once

#include "IAction.h"

#include "core/Constants.h"

class ActionFly : public IAction
{
public:
    static constexpr float wantedHeight = 3 * Constants::TILE_SIZE_HEIGHT;

    ActionFly(const std::shared_ptr<Unit> &unit, const Task &task);

    UpdateResult update(Time time) override;
    UnitState unitState() const override;

    genie::Task::ActionTypes taskType() const override { return genie::Task::Fly; }

private:
    Time m_lastUpdateTime = 0;
    Time m_lastTurnTime = 0;
    Time m_lastStateChangeTime = 0;
    UnitState m_currentState = UnitState::Proceeding;
};
