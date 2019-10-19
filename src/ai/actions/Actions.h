#pragma once

#include "ai/gen/enums.h"

namespace ai {

struct AiRule;

struct Action {
    virtual ~Action();

    virtual void execute(AiRule *owner) = 0;
};

namespace Actions {

struct SetStrategicNumber : public Action
{
    SetStrategicNumber(const StrategicNumberName name, const int targetValue) : m_strategicNumber(name), m_targetValue(targetValue) {}
    void execute(AiRule *rule) override;

    const StrategicNumberName m_strategicNumber;
    const int m_targetValue;
};

struct DisableSelf : public Action
{
    void execute(AiRule *rule) override;
};


} //namespace Actions

} //namespace ai
