#include "Player.h"
#include "mechanics/Civilization.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c) :
    playerId(id),
    civ(c),
    resources(civ->startingResources())
{

}
