#pragma once

#include <stddef.h>
#include <array>
#include <limits>
#include <memory>
#include <string>
#include <unordered_set>

#include "core/Constants.h"
#include "core/ResourceMap.h"
#include "core/Types.h"
#include "core/Utility.h"
#include "mechanics/Civilization.h"

struct Unit;

namespace genie {
class EffectCommand;
}

struct VisibilityMap
{
    bool isDirty = true; // needs re-render

    enum Visibility : int {
        Unexplored = std::numeric_limits<int>::min(),
        Explored = 0,
        Visible
    };

    VisibilityMap();

    inline Visibility visibilityAt(const MapPos &pos) const {
        return visibilityAt(pos.x / Constants::TILE_SIZE, pos.y / Constants::TILE_SIZE);
    }

    inline Visibility visibilityAt(const int tileX, const int tileY, const Visibility def = Unexplored) const {
        const size_t index = tileY * Constants::MAP_MAX_SIZE + tileX;
        if (IS_UNLIKELY(index >= m_visibility.size())) {
            return def;
        }

        if (m_visibility[index] > 0) {
            return Visible;
        } else if (m_visibility[index] == Unexplored) {
            return Unexplored;
        } else {
            return Explored;
        }
    }

    void setExplored(const int tileX, const int tileY) {
        const size_t index = tileY * Constants::MAP_MAX_SIZE + tileX;
        if (IS_UNLIKELY(index >= m_visibility.size())) {
            return;
        }
        m_visibility[index] = Explored;
        isDirty = true;
    }

    void addUnitLookingAt(const int tileX, const int tileY) {
        const size_t index = tileY * Constants::MAP_MAX_SIZE + tileX;
        if (IS_UNLIKELY(index >= m_visibility.size())) {
            return;
        }

        if (m_visibility[index] == Unexplored) {
            m_visibility[index] = Visible;
            isDirty = true;
        } else {
            m_visibility[index]++;

            if (m_visibility[index] == Visible) {
                isDirty = true;
            }
        }
    }

    void removeUnitLookingAt(const int tileX, const int tileY) {
        const size_t index = tileY * Constants::MAP_MAX_SIZE + tileX;
        if (IS_UNLIKELY(index >= m_visibility.size())) {
            return;
        }

        if (IS_UNLIKELY(m_visibility[index] == Unexplored)) {
            return;
        }

        if (m_visibility[index] == Visible) {
            isDirty = true;
        }

        m_visibility[index]--;
    }
    int edgeTileNum(const int tileX, const int tileY, const Visibility type) const;

private:
    std::array<int, Constants::MAP_MAX_SIZE * Constants::MAP_MAX_SIZE> m_visibility;
    std::array<int, 256> m_edgetileLut;
};

struct Player
{
    enum Age {
        DarkAge,
        FeudalAge,
        CastleAge,
        ImperialAge
    };

    bool alive = true;
    std::shared_ptr<VisibilityMap> visibility;

    Player(const int id, const int civId, const ResourceMap &startingResources = {});
    const int playerId;
    int playerColor = 0;

    Civilization civilization;

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

    void addAlliedPlayer(int playerId);
    void removeAlliedPlayer(int playerId);
    bool isAllied(int playerId);


private:
    std::unordered_set<Unit*> m_units;
    std::unordered_set<int> m_activeTechs;
    std::unordered_set<int> m_alliedPlayers;
};
