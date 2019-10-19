#include "AiRule.h"

#include "ai/conditions/Conditions.h"
#include "ai/actions/Actions.h"

namespace ai {

void ai::AiRule::onConditionSatisfied()
{
    for (const std::shared_ptr<Condition> &condition : m_conditions) {
        if (!condition->satisfied(this)) {
            return;
        }
    }

    DBG << "rule triggered";

    for (const std::shared_ptr<Action> &action : m_actions) {
        action->execute(this);
    }
}

void AiRule::addCondition(const std::shared_ptr<ai::Condition> &condition)
{
    m_conditions.push_back(condition);

    condition->connect(Condition::SatisfiedChanged, std::bind(&AiRule::onConditionSatisfied, this));
}

void AiRule::addAction(const std::shared_ptr<Action> &action)
{
    m_actions.push_back(action);

}

} //namespace ai
