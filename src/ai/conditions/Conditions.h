#pragma once

#include "ai/AiScript.h"

#include "core/SignalEmitter.h"
#include "core/Logger.h"
#include "global/EventListener.h"

namespace ai {

struct Condition : public EventListener, public SignalEmitter<Condition> {
    enum Signals {
        SatisfiedChanged
    };

    virtual ~Condition();
    virtual bool satisfied() = 0;
};

struct Action { // TODO: move to actions header when implementing actions
    virtual ~Action();
    virtual void trigger(UnitManager *unitManager) = 0;
};

namespace Conditions {

// Mostly things resolved at parse time, like difficulty
struct ConstantCondition : public Condition {
    ConstantCondition(const bool _value) : value(_value) {}
    bool satisfied() override { return value; }
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


    bool satisfied() override
    {
        return m_subcondition1->satisfied() || m_subcondition2->satisfied();
    }

    std::shared_ptr<Condition> m_subcondition1, m_subcondition2;
};

}//namespace Conditions
}//namespace ai
