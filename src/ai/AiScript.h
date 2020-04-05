#pragma once

#include "ai/gen/enums.h"
#include "core/SignalEmitter.h"

#include <genie/dat/ResourceType.h>

#include <memory>
#include <unordered_map>
#include <vector>

struct Player;

namespace ai {

struct AiRule;

struct AiScript : public SignalEmitter<AiScript>
{
    enum Signals {
        GoalChanged,
        EscrowChanged
    };

    AiScript(Player *player) : m_player(player) { }
    AiScript() = delete;

    std::unordered_map<StrategicNumberName, int> strategicNumbers;

    std::vector<std::shared_ptr<AiRule>> rules;


    Player *m_player = nullptr;

    void setGoal(int goalId, int value) {
        if (m_goals.count(goalId) && value == m_goals[goalId]) {
            return;
        }
        m_goals[goalId] = value;
        emit(GoalChanged);
    }

    int goal(int goalId) { return m_goals[goalId]; }

    void setEscrow(const genie::ResourceType resource, float amount);
    float escrowAmount(const genie::ResourceType resource) const;

    void showDebugMessage(const std::string &message);

private:
    std::unordered_map<int, int> m_goals;
};

} // namespace ai
