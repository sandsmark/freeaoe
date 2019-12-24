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

struct ResourceValue : public Condition
{
    ResourceValue(const genie::ResourceType m_type, const RelOp comparison, const int targetValue, int playerId);

    void onPlayerResourceChanged(Player *player, const genie::ResourceType type, float newValue) override
    {
        if (type != m_type) {
            return;
        }
        if (player->playerId != m_playerId) {
            return;
        }

        bool isSatisfied = CompareCondition::actualCompare(int(m_targetValue), m_relOp, newValue);
        if (isSatisfied == m_isSatisfied) {
            return;
        }
        m_isSatisfied = isSatisfied;

        emit(SatisfiedChanged);
    }

    bool satisfied(AiRule *owner) override
    {
        m_isSatisfied = CompareCondition::actualCompare(int(m_targetValue), m_relOp, owner->m_owner->m_player->currentAge());
        return m_isSatisfied;
    }

    genie::ResourceType m_type = genie::ResourceType::InvalidResource;
    int m_targetValue;
    const RelOp m_relOp;
    bool m_isSatisfied = false;
    const int m_playerId;
};

struct UnitTypeCount : public Condition
{
    UnitTypeCount(const Unit type, const RelOp comparison, const int targetValue, int playerId);
    UnitTypeCount(const Building type, const RelOp comparison, const int targetValue, int playerId);
    UnitTypeCount(const WallType type, const RelOp comparison, const int targetValue, int playerId);

    bool satisfied(AiRule *owner) override
    {
        m_isSatisfied = CompareCondition::actualCompare(int(m_targetValue), m_relOp, m_unitCount);
        return m_isSatisfied;
    }
    void onValueChanged();

    std::unordered_set<int> m_typeIds;
    int m_targetValue;
    const RelOp m_relOp;
    bool m_isSatisfied = false;
    int m_unitCount = 0;

    const int m_playerId; // -1 == any player

    void onUnitCreated(::Unit *unit) override;
    void onUnitDying(::Unit *unit) override;
    void onUnitOwnerChanged(::Unit *unit, int oldPlayerId, int newPlayerId) override;
    void onUnitCaptured(::Unit *unit, int oldPlayerId, int newPlayerId) override;
};

}//namespace Conditions
}//namespace ai
