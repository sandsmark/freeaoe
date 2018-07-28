#pragma once

#include <memory>
#include <unordered_map>
#include <genie/dat/ResourceUsage.h>

class Civilization;

struct Player
{
    Player(const int id, const std::shared_ptr<Civilization> &c, const std::unordered_map<genie::ResourceType, float> &startingResources = {});
    const int playerId;
    std::shared_ptr<Civilization> civ;

    std::unordered_map<genie::ResourceType, float> resources;

    typedef std::shared_ptr<Player> Ptr;
};

