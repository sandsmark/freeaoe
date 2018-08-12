#include "Player.h"
#include "mechanics/Civilization.h"
#include "global/Logger.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources) :
    playerId(id),
    civ(c),
    resources(civ->startingResources())
{
    for (const std::pair<const genie::ResourceType, float> &r : startingResources) {
        resources[r.first] = r.second;
    }

}
