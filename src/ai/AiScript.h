#pragma once

#include "ai/gen/enums.h"
#include "core/SignalEmitter.h"

#include <memory>
#include <unordered_map>
#include <vector>

class UnitManager;
struct Player;

namespace ai {

struct AiRule;

struct AiScript : public SignalEmitter<AiScript>
{
    enum Signals {
        GoalChanged
    };

    AiScript(Player *player);
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

private:
    std::unordered_map<int, int> m_goals;
};

} // namespace ai
