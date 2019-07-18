#include "Player.h"
#include "mechanics/Civilization.h"
#include "mechanics/Unit.h"
#include "core/Logger.h"

#include <genie/dat/TechageEffect.h>
#include "resource/DataManager.h"

#define CHEAT_VISIBILITY 1

Player::Player(const int id, const std::shared_ptr<Civilization> &c, const ResourceMap &startingResources) :
    visibility(std::make_shared<VisibilityMap>()),
    playerId(id),
    civ(c),
    resourcesAvailable(civ->startingResources()),
    name("Player " + std::to_string(id))
{
    for (const std::pair<const genie::ResourceType, float> &r : startingResources) {
        resourcesAvailable[r.first] = r.second;
    }
}

void Player::applyResearch(const int researchId)
{
    if (researchId == -1) {
        return;
    }

    const genie::Tech &research = DataManager::Inst().getTech(researchId);
    applyTechEffect(research.EffectID);

    // Apply all implicit research
    for (const genie::Tech &research : DataManager::Inst().allTechs()) {
        if (research.ResearchLocation != -1) {
            continue;
        }
        if (research.EffectID == -1) {
            continue;
        }
        if (research.Civ != -1 && research.Civ != civ->id()) {
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
            resourcesAvailable[resourceType] += effect.Amount;
        } else {
            resourcesAvailable[resourceType] = effect.Amount;
        }
        break;
    }
    case genie::EffectCommand::EnableUnit:
        civ->enableUnit(effect.TargetUnit);
        break;
    case genie::EffectCommand::UpgradeUnit: {
        uint16_t fromUnitID = effect.TargetUnit;
        const genie::Unit &toUnitData = civ->unitData(effect.UnitClassID);
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
        civ->applyUnitAttributeModifier(effect);
        break;
    case genie::EffectCommand::ResourceMultiplier:
        resourcesAvailable[genie::ResourceType(effect.TargetUnit)] *= effect.Amount;
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
    resourcesAvailable[genie::ResourceType::CurrentAge] = age;

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
    applyTechEffect(civ->startingResource(effectResourceType));
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
                resourcesUsed[genie::ResourceType(res.Type)] -= res.Amount;
            } else {
                resourcesAvailable[genie::ResourceType(res.Type)] += res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.insert(unit);
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
                resourcesUsed[genie::ResourceType(res.Type)] += res.Amount;
            } else {
                resourcesAvailable[genie::ResourceType(res.Type)] -= res.Amount;
            }
            break;
        default:
            break;
        }
    }
    m_units.insert(unit);
    m_units.erase(unit);
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

namespace {
    enum Direction {
        West = 1 << 0,
        South = 1 << 1,
        East = 1 << 2,
        North = 1 << 3,

        NorthWest = 1 << 4,
        NorthEast = 1 << 5,
        SouthEast = 1 << 6,
        SouthWest = 1 << 7,
    };
}


VisibilityMap::VisibilityMap()
{
    m_edgetileLut.fill(-1);
    for (size_t edge=0, tileNum = 0; edge<m_edgetileLut.size(); edge++) {
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

        m_edgetileLut[edge] = tileNum++;
    }

    for (size_t edge=0; edge<m_edgetileLut.size(); edge++) {
        if (m_edgetileLut[edge] != -1) {
            continue;
        }

        int aliasEdge = edge & (NorthWest | NorthEast | SouthEast |  SouthWest);

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

        m_edgetileLut[edge] = m_edgetileLut[aliasEdge];
    }

#ifdef CHEAT_VISIBILITY
    m_visibility.fill(Visible);
#else
    m_visibility.fill(Unexplored);
#endif
}

int VisibilityMap::edgeTileNum(const int tileX, const int tileY, const Visibility type) const
{
    int edges = 0;

    if (visibilityAt(tileX - 1, tileY + 0, type) <= type) { edges |= SouthWest; }
    if (visibilityAt(tileX + 1, tileY + 0, type) <= type) { edges |= NorthEast; }
    if (visibilityAt(tileX + 0, tileY - 1, type) <= type) { edges |= NorthWest; }
    if (visibilityAt(tileX + 0, tileY + 1, type) <= type) { edges |= SouthEast; }

    if (visibilityAt(tileX - 1, tileY - 1, type) <= type) { edges |= West; }
    if (visibilityAt(tileX - 1, tileY + 1, type) <= type) { edges |= North; }
    if (visibilityAt(tileX + 1, tileY - 1, type) <= type) { edges |= South; }
    if (visibilityAt(tileX + 1, tileY + 1, type) <= type) { edges |= East; }

    return m_edgetileLut[edges];
}
