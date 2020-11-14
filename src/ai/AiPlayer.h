#pragma once

#include "mechanics/Player.h"
#include "gen/enums.h"

struct AiPlayer : public Player
{
    AiPlayer(const int id, const int civId, const ResourceMap &startingResources = {}) :
        Player(id, civId, startingResources)
    {}

    ai::DifficultyLevel difficultyLevel = ai::DifficultyLevel::Moderate;

    // Held in escrow
    ResourceMap m_reserves;

    // How much to hold in escrow
    ResourceMap m_escrowPercentages;

    void addResource(const genie::ResourceType type, float amount) override;

    float resourcesAvailableWithEscrow(const genie::ResourceType type) const {
        float ret = Player::resourcesAvailable(type);

        ResourceMap::const_iterator it = m_reserves.find(type);
        if (it != m_reserves.end()) {
            ret += it->second;
        }

        return ret;
    }

    // meh, duplicating code ish
    bool canAffordUnitWithEscrow(const int unitId) const;
    bool canAffordResearchWithEscrow(const int researchId) const;

    void onChatMessage(const int sourcePlayer, const int targetPlayer, const std::string &message) override;
};

