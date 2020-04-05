#pragma once

#include "ai/gen/enums.h"
#include "global/EventListener.h"
#include <genie/dat/ResourceType.h>

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

struct BuyCommodity : public Action, EventListener
{
    BuyCommodity(const Commodity commodity, const int amount);

    void execute(AiRule *rule) override;
    void onTradingPriceChanged(const genie::ResourceType type, const int newPrice);

private:
    genie::ResourceType m_resourceType = genie::ResourceType::InvalidResource;
    int m_tradingPrice = 100;
    int m_amount;
};


} //namespace Actions

} //namespace ai
