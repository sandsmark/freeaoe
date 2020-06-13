#pragma once

#include "ai/gen/enums.h"
#include "core/SignalEmitter.h"
#include "core/Types.h"

#include <genie/dat/ResourceType.h>

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct AiPlayer;

namespace ai {

struct AiRule;

struct AiScript : public SignalEmitter<AiScript>
{
    enum Signals {
        GoalChanged,
        EscrowChanged,
        TimerTriggered
    };

    AiScript(AiPlayer *player) : m_player(player) { }
    AiScript() = delete;

    bool update(const Time time);

    std::unordered_map<StrategicNumberName, int> strategicNumbers;

    std::vector<std::shared_ptr<AiRule>> rules;


    AiPlayer *m_player = nullptr;

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

    void addTimer(const int id, const Time targetTime);

    Time currentTime() const { return m_currentTime; }
    bool hasTimerExpired(const int id) { return m_expiredTimers.count(id) > 0; }

private:
    struct Timer {
        int id = -1;
        Time time = 0;
    };
    std::vector<Timer> m_timers;
    std::vector<Timer> m_activeTimers;
    std::unordered_set<int> m_expiredTimers;

    std::unordered_map<int, int> m_goals;
    Time m_currentTime = -1;
};

} // namespace ai
