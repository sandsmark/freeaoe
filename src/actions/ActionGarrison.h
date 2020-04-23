#ifndef ACTIONGARRISON_H
#define ACTIONGARRISON_H

#include "IAction.h"
struct Building;

class ActionGarrison : public IAction
{
public:
    ActionGarrison(const std::shared_ptr<Unit> &unit, const Task &task);

    genie::ActionType taskType() const override {
        return genie::ActionType::Garrison;
    }

    UpdateResult update(Time time) override;

private:
    std::weak_ptr<Building> m_target;
};


#endif // ACTIONGARRISON_H
