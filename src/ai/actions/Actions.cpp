#include "Actions.h"

#include "ai/AiRule.h"
#include "ai/AiScript.h"
#include "ai/EnumLogDefs.h"
#include "ai/Ids.h"

#include "core/Logger.h"
#include "global/EventManager.h"
#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/Building.h"


#include <algorithm>

void ai::Actions::SetStrategicNumber::execute(AiRule *rule)
{
    rule->m_owner->strategicNumbers[m_strategicNumber] = m_targetValue;
}

ai::Action::~Action()
{
//    DBG << this << "dying";
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

ai::Actions::SetEscrowPercent::SetEscrowPercent(const Commodity commodity, const int targetValue) :
    m_targetValue(targetValue)
{
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

    case Commodity::Gold:
        m_resourceType = genie::ResourceType::GoldStorage;
        break;

    default:
        WARN << "Unhandled commodity for set escrow percentage" << commodity;
        break;
    }
}

void ai::Actions::SetEscrowPercent::execute(ai::AiRule *rule)
{
    DBG << "Setting escrow for" << m_resourceType << "to" << m_targetValue;
    WARN << "escrow not implemented correctly";
    rule->m_owner->setEscrow(m_resourceType, m_targetValue / 100.);
}

void ai::Actions::ShowDebugMessage::execute(ai::AiRule *rule)
{
    rule->m_owner->showDebugMessage(m_message);
}

ai::Actions::TrainUnit::TrainUnit(const ai::Unit unit) :
    m_unitId(ai::unitId(unit))
{
}

void ai::Actions::TrainUnit::execute(ai::AiRule *rule)
{
    Player *player = rule->m_owner->m_player;
    const genie::Unit &data = player->civilization.unitData(m_unitId);
    int16_t trainlocationId = data.Creatable.TrainLocationID;
    if (trainlocationId < 0) {
        WARN << "Failed to find unit where" << data.Name << "is created";
        return;
    }

    // TODO: shared_ptr
    ::Unit *creator = player->findUnitByTypeID(trainlocationId);
    if (!creator) {
        WARN << "failed to find a training location for" << data.Name;
        return;
    }

    if (!creator->isBuilding()) {
        WARN << "for now only buildings can create units..";
        DBG << "fixme in case there's some other units that can train units";
        return;
    }

    ::Building *building = static_cast<::Building*>(creator);
    building->enqueueProduceUnit(&data); // yeah yeah pointers lol
}
