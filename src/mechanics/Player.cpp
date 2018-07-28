#include "Player.h"
#include "mechanics/Civilization.h"
#include "global/Logger.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c) :
    playerId(id),
    civ(c),
    resources(civ->startingResources())
{
    for (const std::pair<genie::ResourceType, int> &r : resources) {
        if (!r.second) {
            continue;
        }
        DBG << int(r.first) << r.second;
    }

}
