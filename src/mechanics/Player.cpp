#include "Player.h"

Player::Player(const int id, const std::shared_ptr<Civilization> &c) :
    playerId(id),
    civ(c)
{

}
