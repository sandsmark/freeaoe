#include "Player.h"
#include "mechanics/Civilization.h"
#include "global/Logger.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c, const std::unordered_map<genie::ResourceType, float> &startingResources) :
    playerId(id),
    civ(c),
    resources(civ->startingResources())
{
    for (const std::pair<genie::ResourceType, float> &r : startingResources) {
        resources[r.first] = r.second;
    }

}
