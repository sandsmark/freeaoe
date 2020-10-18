#pragma once

#include <memory>
#include <vector>
#include "core/SignalEmitter.h"

namespace ai {

struct Condition;
struct Action;
struct AiScript;

struct AiRule : public SignalReceiver
{
    AiRule(AiScript *owner) : m_owner(owner) {}
    AiRule() = delete;
    ~AiRule();

    AiScript *m_owner = nullptr;

    void onConditionSatisfied();

    void addCondition(const std::shared_ptr<Condition> &condition);
    void addAction(const std::shared_ptr<Action> &action);

private:
    // should really have unique_ptr, but bison is a pile of shit
    std::vector<std::shared_ptr<Condition>> m_conditions;
    std::vector<std::shared_ptr<Action>> m_actions;
};

} // namespace ai
