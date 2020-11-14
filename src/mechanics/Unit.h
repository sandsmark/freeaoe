/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <algorithm>
#include <cstdint>
#include <deque>
#include <functional>
#include <iosfwd>
#include <memory>
#include <system_error>
#include <unordered_set>
#include <vector>

#include "Entity.h"
#include "UnitActionHandler.h"
#include "core/Constants.h"
#include "core/ResourceMap.h"
#include "core/Types.h"

class UnitManager;
namespace genie {
class Unit;

namespace unit {
struct AttackOrArmor;
}  // namespace unit
}  // namespace genie

struct Building;
struct Player;

class Sprite;
using SpritePtr = std::shared_ptr<Sprite>;

struct Unit : public Entity
{
    enum HardcodedTypes {
        // For creating normal games
        TownCenter = 109,

        FemaleVillager = 293,

        MaleVillager = 83,
        MaleLumberjack = 123,
        MaleStoneMiner = 124,
        MaleHunter = 122,
        MaleFarmer = 259,
        MaleForager = 120,
        MaleFisherman = 56,
        MaleGoldMiner = 579,
        MaleShepherd = 592,
        MaleBuilder = 118,
        MaleRepairer = 156,

        Docket = 45,
        Castle = 82,
        Market = 84,

        ArcheryRange = 87,
        Archer = 4,

        Barracks = 12,
        Monastery = 104,
        SiegeWorkshop = 49,
        Stable = 101,

        Dock = 45,

        // Special handling
        Mill = 68,
        LumberCamp = 562,
        MiningCamp = 584,

        // For convenience when creating
        PalisadeWall = 72,
        StoneWall = 117,
        FortifiedWall = 155,
        Gate = 487,

        // Farms are very special
        Farm = 50,

        // Nice to have because they are fun
        Cobra = 748,
        VMDL = 206,
        FuriousTheMonkeyBoy = 860,
        StormyDog = 862,

        // For replacements when loading scenarios, from danielpereira on aok.heavengames.com:
        //   IDs 768/770 should be kept disabled. They are used as a layer to
        //   enable the special Spanish Cannon Galleon bonuses
        //   If you check in the Technologies data in the .dat, you'll see
        //   that unit 768 is enabled for Spanish instead of the usual
        //   Cannon Galleon, and that the Elite Cannon Galleon technology
        //   upgrades this unit to ID 770.
        //   And, when I said that this unit is used as a layer,
        //   I mean that, when the game loads this unit,
        //   it replaces it with a Cannon Galleon and applies the Spanish bonuses
        // http://aok.heavengames.com/cgi-bin/forums/display.cgi?action=st&fn=4&tn=42049&st=96
        SpanishCannonGalleon = 768,
        EliteSpanishCannonGalleon = 770,
        CannonGalleon = 420,
        EliteCannonGalleon = 691,
    };

    typedef std::shared_ptr<Unit> Ptr;

    struct Annex {
        Unit::Ptr unit;
        MapPos offset;
    };

    enum class Stance {
        Invalid = -1,

        Aggressive,
        Defensive,
        StandGround,
        NoAttack
    } stance = Stance::Aggressive;

    UnitActionHandler actions;
    std::vector<Annex> annexes;
    std::weak_ptr<Building> garrisonedIn;
    ResourceMap resources;
    int activeMissiles = 0;
    Time lastAttackTime = 0;

    // No copy, no default constructor
    Unit() = delete;
    Unit(const Unit &unit) = delete;
    Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager);
    ~Unit();

    /// convenience casting functions
    static std::shared_ptr<Unit> fromEntity(const EntityPtr &entity) noexcept;
    static inline std::shared_ptr<Unit> fromEntity(const std::weak_ptr<Entity> &entity) noexcept {
        return fromEntity(entity.lock());
    }

    ////////////////////////////////
    // Geometry stuff
    inline float angle() const noexcept { return m_angle; }
    void setAngle(const float angle) noexcept;

    void setMap(const MapPtr &newMap) noexcept override;
    void setPosition(const MapPos &pos, const bool initial = false) override;
    int foundationTerrain() const override;

    //////////////////////////////////////////
    /// Geometry or whatever you call it stuff

    /// The visual rect of this unit on the screen
    virtual ScreenRect screenRect() const noexcept;

    /// Check if this click hit the unit (e. g. some units only count hits on opaque pixels)
    virtual bool containsCursorPos(const ScreenPos &pos) const noexcept;

    /// The size of the selection rect
    Size selectionSize() const noexcept;

    /// How close can it be to other units
    Size clearanceSize() const noexcept;

    /// The center of this unit
    MapPos center() const noexcept {
        return position() + clearanceSize() / 2.;
    }

    /// The rect this unit occupies in map coordinates
    MapRect mapRect() const noexcept;

    /// Number of tiles occupied by this unit
    Size tileSize() const noexcept override;

    float distanceTo(const MapPos &pos) const noexcept
    {
        const double centreDistance = position().distance(pos);
        const Size size = clearanceSize();
        const double clearance = std::max(size.width, size.height);//)//, std::max(otherSize.width, otherSize.height));
        return centreDistance - clearance;
    }

    /// Distance to other unit, taking into account the size of the other unit
    double distanceTo(const Unit::Ptr &otherUnit) const noexcept;

    /// in Z direction, if that makes sense
    float tallness();

    ////////////////////////////////
    // Called every tick
    bool update(Time time) noexcept override;

    // Owners and stuff
    int playerId() const { return m_playerId; }
    const std::weak_ptr<Player> &player() const { return m_player; }
    void setPlayer(const std::shared_ptr<Player> &player);

    UnitManager &unitManager() const noexcept { return m_unitManager; }

    ///////////////////////////////
    /// Hitpoints and similar stuff

    /// Set absolute creation progress
    virtual void setCreationProgress(float progress) noexcept;

    /// When creation is progressing
    void increaseCreationProgress(float progress) noexcept;

    /// The current creation progress
    float creationProgress() const noexcept;

    /// Number of hitpoints left, taking creation progress into account
    float hitpointsLeft() const noexcept;

    /// Percentage of health left
    float healthLeft() const noexcept;

    /// Increase received damage taking the kind of attack and damage multiplier into account
    void receiveAttack(const genie::unit::AttackOrArmor &attack, const float damageMultiplier) noexcept;

    /// Take damage, or heal if amount is negative, without any modifiers
    void takeDamage(const float amount); // negative == heal

    /// Instantly kill unit
    void kill() noexcept;

    /// If the unit is dying, i. e. showing the death animation
    bool isDying() const noexcept;

    /// Has been killed, and finished the death animation
    bool isDead() const noexcept;

    /// Is neither dead nor dying (showing the death animation)
    bool isAlive() const noexcept { return !isDying() && !isDead(); }


    ////////////////////////////////
    /// Unit data stuff

    /// Set the base genie unit data
    void setUnitData(const genie::Unit &data_) noexcept;

    /// Retrieve the current genie unit data
    const genie::Unit *data() const {
        return m_data;
    }

    // Checking task swap IDs
    bool canMatchGenieUnitID(const int id) const;
    // TODO: need basically the same for all attributes

protected:
    friend struct UnitActionHandler;

    void forEachVisibleTile(const std::function<void(const int, const int)> &action);

    Unit(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager, const Type m_type);
    void updateGraphic();

    const genie::Unit *m_data = nullptr;

    // Because we use it often
    SpritePtr m_movingGraphics;

    int m_playerId = -1;
    std::weak_ptr<Player> m_player;

    UnitManager &m_unitManager;

    float m_creationProgress = 0.f;
    float m_damageTaken = 0.f;
    Time m_prevTime = 0;
    float m_angle = 0.f;

    // Need to store it since it can change
    int m_lineOfSight = 0;

private:
    void onDamageTaken();
};

struct DopplegangerEntity : public StaticEntity
{
    const int ownerID;
    const genie::Unit *const originalUnitData = nullptr;

    typedef std::shared_ptr<DopplegangerEntity> Ptr;
    static Ptr fromEntity(const std::shared_ptr<Entity> &entity);

    DopplegangerEntity(const Unit::Ptr &originalUnit);

    bool update(Time time) noexcept override;
    bool shouldBeRemoved() const noexcept override;


private:
    void onOriginalGone();
    UnitManager &m_unitManager;

    bool m_wasVisible = true;
    bool m_isRubble = false;
    std::weak_ptr<Unit> m_originalUnit;
    int m_deadGraphic = -1;
    int m_dyingGraphic = -1; // TODO: haven't found a unit where this is used
};


inline LogPrinter operator <<(LogPrinter os, const Unit::Stance &stance)
{
    const char *separator = os.separator;
    os.separator = "";

    os << "Unit::Stance::";

    switch(stance) {
    case Unit::Stance::Invalid: os << "Invalid"; break;
    case Unit::Stance::Aggressive: os << "Aggressive"; break;
    case Unit::Stance::Defensive: os << "Defensive"; break;
    case Unit::Stance::StandGround: os << "StandGround"; break;
    case Unit::Stance::NoAttack: os << "NoAttack"; break;
    default: os << "Unknown" << std::to_string(int(stance)); break;
    }

    os << separator;
    os.separator = separator;

    return os;
}
