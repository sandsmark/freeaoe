#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

class Civilization;

class Player
{
public:
    Player(const int id, const std::shared_ptr<Civilization> &c);
    const int playerId;
    std::shared_ptr<Civilization> civ;

    typedef std::shared_ptr<Player> Ptr;
};

#endif // PLAYER_H
