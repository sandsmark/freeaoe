#include "Player.h"
#include "mechanics/Civilization.h"
#include "mechanics/Unit.h"
#include "core/Logger.h"

#include <genie/dat/TechageEffect.h>
#include "resource/DataManager.h"

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

VisibilityMap::VisibilityMap()
{
    int count = 0;
    for (int edge=0; edge<256; edge++) {
        bool isValid = true;
//        bool west = (edge & West);
//        bool south = (edge & South);
//        bool east = (edge & East);
//        bool north = (edge & North);

//        bool southWest = (edge & SouthWest);
//        bool southEast = (edge & SouthEast);
//        bool northWest = (edge & NorthWest);
//        bool northEast = (edge & NorthEast);

        bool west = (edge & West) == West;
        bool south = (edge & South) == South;
        bool east = (edge & East) == East;
        bool north = (edge & North) == North;

        bool southWest = (edge & SouthWest) == SouthWest;
        bool southEast = (edge & SouthEast) == SouthEast;
        bool northWest = (edge & NorthWest) == NorthWest;
        bool northEast = (edge & NorthEast) == NorthEast;

        if (southWest && (west || north)) {
            isValid = false;
        }
        if (southEast && (east || north)) {
            isValid = false;
        }
        if (northEast && (east || south)) {
            isValid = false;
        }
//        if (northWest && (east || south)) {
//            isValid = false;
//        }

//        if (edge & SouthWest && (edge & West || edge & North)) {
//            isValid = false;
//        }
//        if (edge & SouthEast && (edge & East || edge & North)) {
//            isValid = false;
//        }
//        if (edge & NorthEast && (edge & South || edge & East)) {
//            isValid = false;
//        }
//        if (edge & NorthWest && (edge & West || edge & South)) {
//            isValid = false;
//        }
//        if (isValid) {
        if ((((edge & NorthWest) != NorthWest) || ((!west && (!south)))) && (isValid)) {
            m_edgetileLut[edge] = count++;
        } else {
            m_edgetileLut[edge] = -1;
//            m_edgetileLut[edge] = 0;
        }
    }

    for (int edge=0; edge<256; edge++) {
        if (m_edgetileLut[edge] != -1) {
            continue;
        }
//        int west = num & 1;
//        int south = num & 2;
//        int east = num & 4;
//        int north = num & 8;
//        if ((num & 0x80) != 0) {
//            north = 0;
//            west = 0;
//        }
//        if ((num & 0x40) != 0) {
//            north = 0;
//            east = 0;
//        }
//        if ((num & 0x20) != 0) {
//            east = 0;
//            south = 0;
//        }
//        if ((num & 0x10) != 0) {
//            south = 0;
//            west = 0;
//        }
//        m_edgetileLut[num] = m_edgetileLut[(num & 0xf0) | north | east | south | west];

        int west = edge & West;
        int south = edge & South;
        int east = edge & East;
        int north = edge & North;

        if (edge & SouthWest) {
            north = 0;
            west = 0;
        }

        if (edge & SouthEast) {
            north = 0;
            east = 0;
        }

        if (edge & NorthEast) {
            east = 0;
            south = 0;
        }

        if (edge & NorthWest) {
            south = 0;
            west = 0;
        }
        m_edgetileLut[edge] = m_edgetileLut[west | south | east | north | (edge & (NorthWest | NorthEast | SouthEast |  SouthWest))];
    }
    for (int edge=0; edge<256; edge++) {
        if (m_edgetileLut[edge] != -1) {
            continue;
        }
        WARN << edge;
        m_edgetileLut[edge] = 0;
    }
    m_visibility.fill(Explored);
}

int VisibilityMap::edges(const int tileX, const int tileY) const
{
    if (visibilityAt(tileX, tileY) != Visible) {
        return 0;
    }
    int edges = 0;
//    if (visibilityAt(tileX    , tileY - 1) == Visible) { ret |= SouthWest; }
//    if (visibilityAt(tileX + 1, tileY + 0) == Visible) { ret |= 0x40; }
//    if (visibilityAt(tileX    , tileY + 1) == Visible) { ret |= 0x20; }
//    if (visibilityAt(tileX - 1, tileY + 1) == Visible) { ret |= 0x10; }
//    if (visibilityAt(tileX + 1, tileY    ) == Visible) { ret |= 8; }
//    if (visibilityAt(tileX + 1, tileY + 1) == Visible) { ret |= 4; }
//    if (visibilityAt(tileX - 1, tileY + 1) == Visible) { ret |= 2; }
//    if (visibilityAt(tileX - 1, tileY    ) == Visible) { ret |= 1; }

//    if (visibilityAt( tileX    , tileY    ) != Visible) { ret |= 0x80; }
//    if (visibilityAt( tileX + 1, tileY + 1) != Visible) { ret |= 0x40; }
//    if (visibilityAt( tileX + 2, tileY    ) != Visible) { ret |= 0x20; }
//    if (visibilityAt( tileX + 1, tileY - 1) != Visible) { ret |= 0x10; }
//    if (visibilityAt( tileX    , tileY + 1) != Visible) { ret |= 8; }
//    if (visibilityAt( tileX + 2, tileY + 1) != Visible) { ret |= 4; }
//    if (visibilityAt( tileX + 2, tileY - 1) != Visible) { ret |= 2; }
//    if (visibilityAt( tileX    , tileY - 1) != Visible) { ret |= 1; }

//    if (visibilityAt(tileX - 1, tileY + 0) != Visible) { ret |= NorthWest; }
//    if (visibilityAt(tileX + 1, tileY + 0) != Visible) { ret |= SouthEast; }
//    if (visibilityAt(tileX + 0, tileY - 1) != Visible) { ret |= SouthWest; }
//    if (visibilityAt(tileX + 0, tileY + 1) != Visible) { ret |= NorthEast; }
//    if (visibilityAt(tileX - 1, tileY - 1) != Visible) { ret |= East; }
//    if (visibilityAt(tileX - 1, tileY + 1) != Visible) { ret |= South; }
//    if (visibilityAt(tileX + 1, tileY - 1) != Visible) { ret |= North; }
//    if (visibilityAt(tileX + 1, tileY + 1) != Visible) { ret |= West; }

    if (visibilityAt(tileX - 1, tileY + 0) != Visible) { edges |= SouthWest; }
    if (visibilityAt(tileX + 1, tileY + 0) != Visible) { edges |= NorthEast; }
    if (visibilityAt(tileX + 0, tileY - 1) != Visible) { edges |= NorthWest; }
    if (visibilityAt(tileX + 0, tileY + 1) != Visible) { edges |= SouthEast; }

    if (visibilityAt(tileX - 1, tileY - 1) != Visible) { edges |= East; }
    if (visibilityAt(tileX - 1, tileY + 1) != Visible) { edges |= North; }
    if (visibilityAt(tileX + 1, tileY - 1) != Visible) { edges |= South; }
    if (visibilityAt(tileX + 1, tileY + 1) != Visible) { edges |= West; }

//    return ret + 1;
//    return m_edgetileLut[ret ^ 0xff]*2;
    return m_edgetileLut[edges]*2 + 1;
}
