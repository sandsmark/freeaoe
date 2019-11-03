#pragma once

#include "ai/AiScript.h"
#include "ai/AiRule.h"

#include "core/SignalEmitter.h"
#include "core/Logger.h"
#include "global/EventListener.h"
#include "mechanics/Player.h"

#include <genie/dat/ResourceUsage.h>

namespace ai {

struct Condition : public EventListener, public SignalEmitter<Condition> {
    enum Signals {
        SatisfiedChanged
    };

    virtual ~Condition();
    virtual bool satisfied(AiRule *owner) = 0;
};

namespace Conditions {

// Mostly things resolved at parse time, like difficulty
struct ConstantCondition : public Condition
{
    ConstantCondition(const bool _value) : value(_value) {}
    bool satisfied(AiRule * /*owner*/) override { return value; }
    const bool value;
};

struct OrCondition : public Condition
{
    OrCondition(const std::shared_ptr<Condition> &subcondition1, const std::shared_ptr<Condition> &subcondition2) :
        m_subcondition1(subcondition1),
        m_subcondition2(subcondition2)
    {
        if (!m_subcondition1) {
            WARN << "missing first condition!";
            m_subcondition1 = std::make_shared<ConstantCondition>(true);
        }

        if (!m_subcondition2) {
            WARN << "missing second condition!";
            m_subcondition2 = std::make_shared<ConstantCondition>(true);
        }
    }


    bool satisfied(AiRule *owner) override
    {
        return m_subcondition1->satisfied(owner) || m_subcondition2->satisfied(owner);
    }

    std::shared_ptr<Condition> m_subcondition1, m_subcondition2;
};

struct CompareCondition : public Condition
{
    CompareCondition(const int value1, const RelOp comparison, const int value2) :
        m_value1(value1),
        m_value2(value2),
        m_comparison(comparison)
    {
    }

    static inline bool actualCompare(const int value1, const RelOp comparison, const int value2)
    {
        switch (comparison) {
        case RelOp::Equal:
            return value1 == value2;
        case RelOp::LessThan:
            return value1 < value2;
        case RelOp::NotEqual:
            return value1 != value2;
        case RelOp::GreaterThan:
            return value1 > value2;
        case RelOp::LessOrEqual:
            return value1 <= value2;
        case RelOp::GreaterOrEqual:
            return value1 >= value2;
        }

        return false;
    }

    bool satisfied(AiRule * /*owner*/) override
    {
        return actualCompare(m_value1, m_comparison, m_value2);
    }

    const int m_value1, m_value2;
    const RelOp m_comparison;
};

struct CurrentAge : public Condition
{
    CurrentAge(const Age targetAge);

    bool checkAge(const Player::Age age)
    {
        switch(age) {
        case Player::Age::DarkAge:
            return m_targetAge == Age::DarkAge;
        case Player::Age::FeudalAge:
            return m_targetAge == Age::FeudalAge;
        case Player::Age::CastleAge:
            return m_targetAge == Age::CastleAge;
        case Player::Age::ImperialAge:
            return m_targetAge == Age::ImperialAge;
        default:
            WARN << "invalid age" << age;
            return false;
        }
    }

    void onPlayerResourceChanged(Player *player, const genie::ResourceType type, float newValue) override
    {
        if (type != genie::ResourceType::CurrentAge) {
            return;
        }

        if (!checkAge(player->currentAge())) {
            return;
        }

        // TODO: check player first.. but then we need to store our player or something, so figure out a way to do that cleanly

        emit(SatisfiedChanged);
    }

    bool satisfied(AiRule *owner) override
    {
        return checkAge(owner->m_owner->m_player->currentAge());
    }

    const Age m_targetAge;
};

}//namespace Conditions
}//namespace ai
