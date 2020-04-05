#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "mechanics/Player.h"

struct AiPlayer : public Player
{
    AiPlayer(const int id, const int civId, const ResourceMap &startingResources = {}) :
        Player(id, civId, startingResources)
    {}

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
};

#endif // AIPLAYER_H
