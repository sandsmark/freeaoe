#ifndef ACTIONGATHER_H
#define ACTIONGATHER_H

#include "core/IAction.h"
#include "core/Entity.h"

struct Player;

class ActionGather : public IAction
{
public:
    ActionGather(const Unit::Ptr &unit, const Unit::Ptr &target, const genie::Task *task);

    bool update(Time time) override;
    UnitState unitState() const override { return UnitState::Proceeding; }

private:
    std::weak_ptr<Unit> m_target;
    const genie::Task *m_task;
};

#endif // ACTIONGATHER_H
