#include "AiPlayer.h"

#include "resource/DataManager.h"

void AiPlayer::addResource(const genie::ResourceType type, float amount)
{
    float toEscrow = amount * m_escrowPercentages[type] / 100.;
    m_reserves[type] += toEscrow;

    Player::addResource(type, amount - toEscrow);

    EventManager::registerListener(this, EventManager::ChatMessage);
}

bool AiPlayer::canAffordUnitWithEscrow(const int unitId) const
{
    const genie::Unit &unit = civilization.unitData(unitId);
    if (unit.ID == -1 || !unit.Enabled || unit.Creatable.TrainLocationID == -1) {
        return false;
    }

    for (const genie::Unit::ResourceStorage &res : unit.ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveResourceType:
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            break;
        default:
            continue;
        }

        const genie::ResourceType resourceType = genie::ResourceType(res.Type);

        int available = resourcesAvailableWithEscrow(genie::ResourceType(resourceType)) - resourcesUsed(genie::ResourceType(res.Type));
        if (available < res.Amount) {
            DBG << unit.Name << "Not affordable" << available << res.Amount;
            return false;
        }
    }

    for (const genie::Resource<short, short> &cost : unit.Creatable.ResourceCosts) {
        if (!cost.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(cost.Type);
        if (resourcesAvailableWithEscrow(type) < cost.Amount) {
            return false;
        }
    }

    return true;
}

bool AiPlayer::canAffordResearchWithEscrow(const int researchId) const
{
    const genie::Tech &research = DataManager::Inst().getTech(researchId);
    for (const genie::Tech::ResearchResourceCost &cost : research.ResourceCosts) {
        const genie::ResourceType resourceType = genie::ResourceType(cost.Type);
        if (resourcesAvailableWithEscrow(resourceType) < cost.Amount) {
            return false;
        }
    }

    return true;

}

void AiPlayer::onChatMessage(const int sourcePlayer, const int targetPlayer, const std::string &message)
{
    WARN << "todo, got chat message, handle that ai trigger" << sourcePlayer << message;

    if (targetPlayer != playerId) {
        return;
    }
}
