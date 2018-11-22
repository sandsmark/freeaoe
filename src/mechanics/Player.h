#pragma once

#include "core/Types.h"

#include <memory>

#include <unordered_map>
#include <genie/dat/ResourceUsage.h>
#include "core/ResourceMap.h"

class Civilization;

struct Player
{
    Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources = {});
    const int playerId;
    std::shared_ptr<Civilization> civ;

    ResourceMap resources;

    typedef std::shared_ptr<Player> Ptr;
    std::string name = "Player";
};

