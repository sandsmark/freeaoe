#include "Actions.h"

#include "ai/AiRule.h"
#include "ai/AiScript.h"
#include "ai/EnumLogDefs.h"

#include "core/Logger.h"
#include "global/EventManager.h"
#include "mechanics/Player.h"


#include <algorithm>

void ai::Actions::SetStrategicNumber::execute(AiRule *rule)
{
    rule->m_owner->strategicNumbers[m_strategicNumber] = m_targetValue;
}

ai::Action::~Action()
{
    DBG << this << "dying";
}

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

ai::Actions::BuyCommodity::BuyCommodity(const Commodity commodity, const int amount) :
    m_amount(amount)
{
    if (amount % 100 != 0) {
        WARN << "Invalid amount to buy:" << amount;
        m_amount -= amount % 100;
    }

    switch(commodity) {
    case Commodity::Food:
        m_resourceType = genie::ResourceType::FoodStorage;
        break;

    case Commodity::Wood:
        m_resourceType = genie::ResourceType::WoodStorage;
        break;

    case Commodity::Stone:
        m_resourceType = genie::ResourceType::StoneStorage;
        break;

    default:
        WARN << "Unhandled commodity for trade" << commodity;
        break;
    }

    EventManager::registerListener(this, EventManager::TradingPriceChanged);
}

void ai::Actions::BuyCommodity::execute(AiRule *rule)
{
    Player *player = rule->m_owner->m_player;
    const int goldAvailable = player->resourcesAvailable(genie::ResourceType::GoldStorage);
    const int cost = m_tradingPrice * m_amount * 1.3;
    const bool canTrade = goldAvailable >= cost;

    if (!canTrade) {
        WARN << "tried to trade without enough resources" << goldAvailable << cost;
        return;
    }
    player->removeResource(genie::ResourceType::GoldStorage, cost);
    player->addResource(m_resourceType, m_amount);
    EventManager::resourceBought(m_resourceType, m_amount);
}

void ai::Actions::BuyCommodity::onTradingPriceChanged(const genie::ResourceType type, const int newPrice)
{
    if (type != m_resourceType) {
        return;
    }

    m_tradingPrice = newPrice;
}
