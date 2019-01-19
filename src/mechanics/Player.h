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
    enum Age {
        DarkAge,
        FeudalAge,
        CastleAge,
        ImperialAge
    };

    Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources = {});
    const int playerId;
    std::shared_ptr<Civilization> civ;

    ResourceMap resourcesAvailable;
    ResourceMap resourcesUsed;

    typedef std::shared_ptr<Player> Ptr;
    std::string name = "Player";

    void applyResearch(const int researchId);
    void applyTechEffect(const int effectId);
    void applyTechEffectCommand(const genie::EffectCommand &effect);
    void setAge(const Age age);

    void addUnit(Unit *unit);
    void removeUnit(Unit *unit);

private:
    std::unordered_set<Unit*> m_units;
    std::unordered_set<int> m_activeTechs;
};

