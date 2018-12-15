#pragma once

#include "core/Types.h"

#include <memory>

#include <unordered_map>
#include <unordered_set>
#include <genie/dat/ResourceUsage.h>
#include <genie/dat/Civ.h>
#include "core/ResourceMap.h"

class Civilization;
struct Unit;

namespace genie {
class EffectCommand;
}

struct Player
{
    Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources = {});
    const int playerId;
    std::shared_ptr<Civilization> civ;

    ResourceMap resources;

    typedef std::shared_ptr<Player> Ptr;
    std::string name = "Player";

    void applyTechEffect(const genie::EffectCommand &effect);

    void addUnit(Unit *unit);
    void removeUnit(Unit *unit);

private:

    std::unordered_set<Unit*> m_units;
};

