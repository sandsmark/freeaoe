#include "Player.h"

#include <genie/dat/Research.h>
#include <genie/dat/Techage.h>
#include <genie/dat/TechageEffect.h>
#include <genie/dat/Unit.h>
#include <genie/dat/ResourceUsage.h>
#include <stdint.h>
#include <utility>
#include <vector>

#include "core/Logger.h"
#include "mechanics/Civilization.h"
#include "mechanics/Unit.h"
#include "global/EventManager.h"
#include "resource/DataManager.h"

//#define CHEAT_VISIBILITY 1

Player::Player(const int id, const int civId, const ResourceMap &startingResources) :
    visibility(std::make_shared<VisibilityMap>()),
    playerId(id),
    civilization(civId),
    name("Player " + std::to_string(id)),
    m_resourcesAvailable(civilization.startingResources())
{
    // Override
    for (const std::pair<const genie::ResourceType, float> &r : startingResources) {
        m_resourcesAvailable[r.first] = r.second;
    }

    updateAvailableTechs();
}

void Player::applyResearch(const int researchId)
{
    if (researchId == -1) {
        return;
    }

    applyTechEffect(DataManager::Inst().getTech(researchId).EffectID);

    // Apply all implicit research
    for (const genie::Tech &research : DataManager::Inst().allTechs()) {
        if (research.ResearchLocation != -1) {
            continue;
        }
        if (research.EffectID == -1) {
            continue;
        }
        if (research.Civ != -1 && research.Civ != civilization.id()) {
            continue;
        }
        if (m_activeTechs.count(research.EffectID)) {
            continue;
        }

        bool requirementsSatisfied = false;
        for (const int reqId : research.RequiredTechs) {
            if (reqId == -1) {
                continue;
            }
            if (m_activeTechs.count(reqId)) {
                requirementsSatisfied = true;
            } else {
                requirementsSatisfied = false;
                break;
            }
        }

        if (!requirementsSatisfied) {
            continue;
        }

        applyTechEffect(research.EffectID);
    }
    updateAvailableTechs();
}

void Player::applyTechEffect(const int effectId)
{
    if (effectId == -1) {
        return;
    }

    if (m_activeTechs.count(effectId)) {
        DBG << effectId << "already active";
        return;
    }

    m_activeTechs.insert(effectId);

    const genie::Effect &effect = DataManager::Inst().getEffect(effectId);

    for (const genie::EffectCommand &command : effect.EffectCommands) {
        applyTechEffectCommand(command);
    }
}

void Player::applyTechEffectCommand(const genie::EffectCommand &effect)
{
    switch(effect.Type) {
    case genie::EffectCommand::ResourceModifier: {
        const genie::ResourceType resourceType = genie::ResourceType(effect.TargetUnit);
        if (effect.UnitClassID) {
            m_resourcesAvailable[resourceType] += effect.Amount;
        } else {
            m_resourcesAvailable[resourceType] = effect.Amount;
        }
        break;
    }
    case genie::EffectCommand::EnableUnit:
        civilization.enableUnit(effect.TargetUnit);
        break;
    case genie::EffectCommand::UpgradeUnit: {
        uint16_t fromUnitID = effect.TargetUnit;
        const genie::Unit &toUnitData = civilization.unitData(effect.UnitClassID);
        if (toUnitData.Class == genie::Unit::InvalidClass) {
            return;
        }

        for (Unit *unit : m_units) {
            if (unit->data()->ID != fromUnitID) {
                continue;
            }
            unit->setUnitData(toUnitData);
        }
        break;
    }

    case genie::EffectCommand::AttributeMultiplier:
    case genie::EffectCommand::AbsoluteAttributeModifier:
    case genie::EffectCommand::RelativeAttributeModifier:
        civilization.applyUnitAttributeModifier(effect);
        break;
    case genie::EffectCommand::ResourceMultiplier:
        m_resourcesAvailable[genie::ResourceType(effect.TargetUnit)] *= effect.Amount;
        break;
    case genie::EffectCommand::TechCostModifier:
        WARN << "Disable tech cost modifier not implemented";
        break;
    case genie::EffectCommand::DisableTech:
        WARN << "Disable tech effect not implemented";
        return;
    case genie::EffectCommand::TechTimeModifier:
        WARN << "Disable tech time modifier not implemented";
        break;
    default:
        WARN << "Unhandled tech effect type" << effect.Type;
        return;
    }

}

void Player::setAge(const Age age)
{
    m_resourcesAvailable[genie::ResourceType::CurrentAge] = age;

    genie::ResourceType effectResourceType;
    switch (age) {
    case DarkAge:
        effectResourceType = genie::ResourceType::DarkAgeTechID;
        break;
    case FeudalAge:
        effectResourceType = genie::ResourceType::FeudalAgeTechID;
        break;
    case CastleAge:
        effectResourceType = genie::ResourceType::CastleAgeTechID;
        break;
    case ImperialAge:
        effectResourceType = genie::ResourceType::ImperialAgeTechID;
        break;
    default:
        WARN << "Invalid age";
        return;
    }

    // TODO: need to recurse and research all dependencies
    applyTechEffect(civilization.startingResource(effectResourceType));
}

void Player::addUnit(Unit *unit)
{
    for (const genie::Unit::ResourceStorage &res : unit->data()->ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveResourceType:
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            if (res.Amount < 0) {
                m_resourcesUsed[genie::ResourceType(res.Type)] -= res.Amount;
            } else {
                m_resourcesAvailable[genie::ResourceType(res.Type)] += res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.insert(unit);
    if (m_unitGroups.empty()) {
        m_unitGroups.resize(1);
    }
    m_unitGroups[0].insert(unit);
}

void Player::removeUnit(Unit *unit)
{
    for (const genie::Unit::ResourceStorage &res : unit->data()->ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            if (res.Amount < 0) {
                m_resourcesUsed[genie::ResourceType(res.Type)] += res.Amount;
            } else {
                m_resourcesAvailable[genie::ResourceType(res.Type)] -= res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.erase(unit);

    for (std::unordered_set<Unit*> &group : m_unitGroups) {
        group.erase(unit);
    }

    // bleh, probably not the best, if we want to preserve them for some reason
//    std::vector<std::unordered_set<Unit*>>::iterator it;
//    for (it = unitGroups.begin(); it != unitGroups.end(); it++) {
//        if (it->empty()) {
//            it = unitGroups.erase(it);
//        }
//    }
}

void Player::addAlliedPlayer(int playerId)
{
    m_alliedPlayers.insert(playerId);
}

void Player::removeAlliedPlayer(int playerId)
{
    m_alliedPlayers.erase(playerId);
}

bool Player::isAllied(int playerId)
{
    // STL sucks
    return m_alliedPlayers.count(playerId) > 0;
}

void Player::setAvailableResource(const genie::ResourceType type, float newValue)
{
    m_resourcesAvailable[type] = newValue;

    EventManager::playerResourceChanged(this, type, newValue);
}

void Player::setUnitGroup(Unit *unit, int group)
{
    if (group < 0) {
        WARN << "Invalid group" << group;
        group = 0;
    }

    // could break out of the loop when we found it, but I don't trust myself not to be dumb enough to add to multiple groups
    for (std::unordered_set<Unit*> &group : m_unitGroups) {
        group.erase(unit);
    }

    if (group >= m_units.size()) {
        m_unitGroups.resize(group + 1);
    }
    m_unitGroups[group].insert(unit);
}

void Player::updateAvailableTechs()
{
    m_currentlyAvailableTechs.clear();

    std::unordered_map<uint16_t, genie::Tech>::const_iterator it;
    for (it = civilization.availableTechs().begin(); it != civilization.availableTechs().end(); it++) {
        if (m_activeTechs.count(it->first)) {
            continue;
        }

        bool requirementsSatisfied = false;
        for (const int reqId : it->second.RequiredTechs) {
            if (reqId == -1) {
                continue;
            }
            if (m_activeTechs.count(reqId)) {
                requirementsSatisfied = true;
            } else {
                requirementsSatisfied = false;
                break;
            }
        }

        if (!requirementsSatisfied) {
            continue;
        }
        m_currentlyAvailableTechs[it->first] = it->second;
    }
}

bool Player::canBuildUnit(const int unitId) const
{
    const genie::Unit &unit = civilization.unitData(unitId);
    if (unit.ID == -1 || !unit.Enabled || unit.Creatable.TrainLocationID == -1) {
        return false;
    }

    for (const genie::Unit::ResourceStorage &res : unit.ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }
        switch (res.Type) {
        case genie::ResourceStoreMode::GiveResourceType:
        case genie::ResourceStoreMode::GiveAndTakeResourceType:
        case genie::ResourceStoreMode::BuildingResourceType:
            break;
        default:
            continue;
        }
        int available = resourcesAvailable(genie::ResourceType(res.Type)) - resourcesUsed(genie::ResourceType(res.Type));
        if (available < res.Amount) {
            DBG << unit.Name << "Not affordable" << available << res.Amount;
            return false;
        }
    }

    for (const genie::Resource<short, short> &cost : unit.Creatable.ResourceCosts) {
        if (!cost.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(cost.Type);
        if (resourcesAvailable(type) < cost.Amount) {
            return false;
        }
    }

    return true;
}

namespace {
enum Direction : uint8_t {
    West = 1 << 0,
    South = 1 << 1,
    East = 1 << 2,
    North = 1 << 3,

    NorthWest = 1 << 4,
    NorthEast = 1 << 5,
    SouthEast = 1 << 6,
    SouthWest = 1 << 7,
};

struct EdgeTileLut {
    constexpr EdgeTileLut() : values{}
    {
        const uint8_t uninitialized = -1;

        for (size_t i=0; i<values.size(); i++) {
            values[i] = uninitialized;
        }

        uint8_t tileNum = 0;
        for (size_t edge=0; edge<values.size(); edge++) {
            const bool west      = (edge & West);
            const bool south     = (edge & South);
            const bool east      = (edge & East);
            const bool north     = (edge & North);
            const bool southWest = (edge & SouthWest);
            const bool southEast = (edge & SouthEast);
            const bool northWest = (edge & NorthWest);
            const bool northEast = (edge & NorthEast);

            if (southWest && (west || north)) {
                continue;
            }
            if (southEast && (east || north)) {
                continue;
            }
            if (northEast && (east || south)) {
                continue;
            }
            if (northWest && (west || south)) {
                continue;
            }

            values[edge] = tileNum++;
        }

        for (size_t edge=0; edge<values.size(); edge++) {
            if (values[edge] != uninitialized) {
                continue;
            }

            uint8_t aliasEdge = edge & (NorthWest | NorthEast | SouthEast |  SouthWest);

            if (edge & SouthWest) {
                aliasEdge &= ~North;
                aliasEdge &= ~West;
            }

            if (edge & SouthEast) {
                aliasEdge &= ~North;
                aliasEdge &= ~East;
            }

            if (edge & NorthEast) {
                aliasEdge &= ~South;
                aliasEdge &= ~East;
            }

            if (edge & NorthWest) {
                aliasEdge &= ~South;
                aliasEdge &= ~West;
            }

            values[edge] = values[aliasEdge];
        }
    }

    std::array<uint8_t, 256> values;
};
} // anonymous namespace

VisibilityMap::VisibilityMap()
{
#ifdef CHEAT_VISIBILITY
    m_visibility.fill(Visible);
#else
    m_visibility.fill(Unexplored);
#endif
}

int VisibilityMap::edgeTileNum(const int tileX, const int tileY, const Visibility type) const
{
    static constexpr EdgeTileLut edgetileLut;

    uint8_t edges = 0;

    if (visibilityAt(tileX - 1, tileY + 0, type) <= type) { edges |= SouthWest; }
    if (visibilityAt(tileX + 1, tileY + 0, type) <= type) { edges |= NorthEast; }
    if (visibilityAt(tileX + 0, tileY - 1, type) <= type) { edges |= NorthWest; }
    if (visibilityAt(tileX + 0, tileY + 1, type) <= type) { edges |= SouthEast; }

    if (visibilityAt(tileX - 1, tileY - 1, type) <= type) { edges |= West; }
    if (visibilityAt(tileX - 1, tileY + 1, type) <= type) { edges |= North; }
    if (visibilityAt(tileX + 1, tileY - 1, type) <= type) { edges |= South; }
    if (visibilityAt(tileX + 1, tileY + 1, type) <= type) { edges |= East; }

    return edgetileLut.values[edges];
}
