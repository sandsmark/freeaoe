#include "Actions.h"

#include "ai/AiRule.h"
#include "ai/AiScript.h"

#include <algorithm>

void ai::Actions::SetStrategicNumber::execute(AiRule *rule)
{
    rule->m_owner->strategicNumbers[m_strategicNumber] = m_targetValue;
}

ai::Action::~Action() { }

void ai::Actions::DisableSelf::execute(ai::AiRule *rule)
{
    // goddamn msvc and their slow standard support
    rule->m_owner->rules.erase(std::remove_if(
        rule->m_owner->rules.begin(),
        rule->m_owner->rules.end(),
        [=](const std::shared_ptr<AiRule> &containedRule) {
            return containedRule.get() == rule;
        }
    ));
}
