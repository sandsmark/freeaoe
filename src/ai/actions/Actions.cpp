#include "Actions.h"

#include "ai/AiRule.h"
#include "ai/AiScript.h"
#include "ai/EnumLogDefs.h"
#include "ai/AiPlayer.h"
#include "ai/Ids.h"

#include "core/Logger.h"
#include "global/EventManager.h"
#include "mechanics/Unit.h"
#include "mechanics/Building.h"
#include "mechanics/UnitFactory.h"
#include "mechanics/UnitManager.h"


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

ai::Actions::ReleaseEscrow::ReleaseEscrow(const ai::Commodity commodity)
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
        WARN << "Unhandled commodity for release escrow" << commodity;
        break;
    }
}

void ai::Actions::ReleaseEscrow::execute(ai::AiRule *rule)
{
    AiPlayer *player = rule->m_owner->m_player;
    const float newAmount = player->resourcesAvailableWithEscrow(m_resourceType);
    player->m_reserves[m_resourceType] = 0;
    player->setAvailableResource(m_resourceType, newAmount);
}

void ai::Actions::ShowDebugMessage::execute(ai::AiRule *rule)
{
    rule->m_owner->showDebugMessage(m_message);
}

ai::Actions::TrainUnit::TrainUnit(const ai::Unit unit) :
    m_unitIds(ai::unitIds(unit))
{
}

void ai::Actions::TrainUnit::execute(ai::AiRule *rule)
{
    Player *player = rule->m_owner->m_player;
    for (const int id : m_unitIds) {
        if (tryTrain(player, id)) {
            return;
        }
    }
}

bool ai::Actions::TrainUnit::tryTrain(Player *player, int unitId)
{
    const genie::Unit &data = player->civilization.unitData(unitId);
    int16_t trainlocationId = data.Creatable.TrainLocationID;
    if (trainlocationId < 0) {
        WARN << "Failed to find unit where" << data.Name << "is created";
        return false;
    }

    // TODO: shared_ptr
    ::Unit *creator = player->findUnitByTypeID(trainlocationId);
    if (!creator) {
        WARN << "failed to find a training location for" << data.Name;
        return false;
    }

    if (!creator->isBuilding()) {
        WARN << "for now only buildings can create units..";
        DBG << "fixme in case there's some other units that can train units";
        return false;
    }

    ::Building *building = static_cast<::Building*>(creator);
    building->enqueueProduceUnit(&data); // yeah yeah pointers lol

    return true;
}

ai::Actions::BuildBuilding::BuildBuilding(const ai::Building building) :
    m_unitIds(unitIds(building))
{

}

void ai::Actions::BuildBuilding::execute(ai::AiRule *rule)
{
    Player *player = rule->m_owner->m_player;
    for (const int id : m_unitIds) {
        if (tryBuild(player, id)) {
            return;
        }
    }
}

bool ai::Actions::BuildBuilding::tryBuild(Player *player, int unitId)
{
    if (!player->canAffordUnit(unitId)) {
        return false;
    }

    const genie::Unit &data = player->civilization.unitData(unitId);
    int16_t builderId = data.Creatable.TrainLocationID;
    if (builderId < 0) {
        WARN << "Failed to find unit where" << data.Name << "is created";
        return false;
    }

    // TODO: shared_ptr
    std::vector<::Unit *> builders = player->findUnitsByTypeID(builderId);
    if (builders.empty()) {
        WARN << "failed to find a builder for" << data.Name;
        return false;
    }
    ::Unit *builder = nullptr;
    Task task;

    for (::Unit *unit : builders) {
        for (const Task &potential : unit->actions.availableActions()) {
            if (potential.data->ActionType == genie::ActionType::Build) {
                task = potential;
                break;
            }
        }
        if (!task.data) {
            continue;
        }

        builder = unit;
        break;
    }

    if (!builder) {
        WARN << "Failed to find builder for" << data.Name;
        return false;
    }

    ::Unit::Ptr unit = UnitFactory::Inst().createUnit(unitId, builder->player.lock(), builder->unitManager());
    ::Building::Ptr buildingToPlace = ::Unit::asBuilding(unit);

    // TODO: find proper placement, for now just place it by the builder
    MapPos pos = builder->position() + unit->clearanceSize() * 1.1; // meh, just some spacing
    builder->unitManager().add(unit, pos);

    buildingToPlace->setCreationProgress(0);

    task.target = buildingToPlace;
    IAction::assignTask(task, ::Unit::fromEntity(builder->shared_from_this())); // HACKKC fixme proper shared_ptr everywhere pls todo

    return true;
}
