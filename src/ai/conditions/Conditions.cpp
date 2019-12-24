#include "Conditions.h"
#include "global/EventManager.h"

#include "mechanics/Unit.h"

#include "ai/Ids.h"
#include "ai/EnumLogDefs.h"

namespace ai {
namespace Conditions {

ResourceValue::ResourceValue(const genie::ResourceType type, const RelOp comparison, const int targetValue, int playerId) :
    m_type(type),
    m_relOp(comparison),
    m_playerId(playerId)
{
    if (type == genie::ResourceType::CurrentAge) {
        switch(Age(targetValue)) {
        case Age::DarkAge:
            m_targetValue = Player::Age::DarkAge;
            break;
        case Age::FeudalAge:
            m_targetValue = Player::Age::FeudalAge;
            break;
        case Age::CastleAge:
            m_targetValue = Player::Age::CastleAge;
            break;
        case Age::ImperialAge:
            m_targetValue = Player::Age::ImperialAge;
            break;
        case Age::PostImperialAge:
            m_targetValue = int(Player::Age::ImperialAge) + 1;
            break;
        }
    }

    EventManager::registerListener(this, EventManager::PlayerResourceChanged);
}

UnitTypeCount::UnitTypeCount(const Unit type, const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_playerId(playerId)
{
    m_typeIds = unitIds(type);
}

UnitTypeCount::UnitTypeCount(const Building type, const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_playerId(playerId)
{
    m_typeIds = unitIds(type);
}

UnitTypeCount::UnitTypeCount(const WallType type, const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_playerId(playerId)
{
    m_typeIds = unitIds(type);

    EventManager::registerListener(this, EventManager::UnitCreated);
    EventManager::registerListener(this, EventManager::UnitDestroyed);
    EventManager::registerListener(this, EventManager::UnitChangedOwner);
    EventManager::registerListener(this, EventManager::UnitCaptured);
}

void UnitTypeCount::onUnitCreated(::Unit *unit)
{
    if (!m_typeIds.count(unit->data()->ID)) {
        return;
    }
    if (m_playerId != -1 && unit->playerId != m_playerId) {
        return;
    }
    m_unitCount++;
    onValueChanged();
}

void UnitTypeCount::onUnitDying(::Unit *unit)
{
    if (!m_typeIds.count(unit->data()->ID)) {
        return;
    }
    if (m_playerId != -1 && unit->playerId != m_playerId) {
        return;
    }
    m_unitCount--;
    onValueChanged();
}

void UnitTypeCount::onUnitOwnerChanged(::Unit *unit, int oldPlayerId, int newPlayerId)
{
    if (!m_typeIds.count(unit->data()->ID)) {
        return;
    }
    if (m_playerId != -1 && oldPlayerId == m_playerId) {
        m_unitCount--;
        onValueChanged();
    }
    if (newPlayerId == m_playerId) {
        m_unitCount++;
        onValueChanged();
    }
}

void UnitTypeCount::onUnitCaptured(::Unit *unit, int oldPlayerId, int newPlayerId)
{
    if (!m_typeIds.count(unit->data()->ID)) {
        return;
    }
    if (m_playerId != -1 && oldPlayerId == m_playerId) {
        m_unitCount--;
        onValueChanged();
    }
    if (newPlayerId == m_playerId) {
        m_unitCount++;
        onValueChanged();
    }
}

void UnitTypeCount::onValueChanged()
{
    bool satisfied = CompareCondition::actualCompare(int(m_targetValue), m_relOp, m_unitCount);
    if (satisfied != m_isSatisfied) {
        m_isSatisfied = satisfied;
        emit(SatisfiedChanged);
    }
}

PopulationHeadroomCondition::PopulationHeadroomCondition(const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_targetValue(targetValue),
    m_playerId(playerId)
{
    EventManager::registerListener(this, EventManager::PlayerResourceChanged);
}

void PopulationHeadroomCondition::onPlayerResourceChanged(Player *player, const genie::ResourceType resourceType, float newValue)
{
    if (player->playerId != m_playerId) {
        return;
    }
    switch(resourceType) {
    case genie::ResourceType::CurrentPopulation:
        m_housingAvailable = player->resourcesAvailable(genie::ResourceType::PopulationHeadroom) + newValue;
        break;
    case genie::ResourceType::PopulationHeadroom:
        m_housingAvailable = newValue + player->resourcesUsed(genie::ResourceType::CurrentPopulation);
        break;
    default:
        return;
    }

    const int populationCap = player->resourcesAvailable(genie::ResourceType::CurrentPopulation) + player->resourcesUsed(genie::ResourceType::CurrentPopulation);

    DBG << "housing available:" << m_housingAvailable << "pop cap" << populationCap;
    m_currentValue = populationCap - m_housingAvailable;

    bool satisfied = CompareCondition::actualCompare(m_targetValue, m_relOp, m_currentValue);
    if (satisfied == m_isSatisfied) {
        return;
    }
    m_isSatisfied = satisfied;
    emit(SatisfiedChanged);
}

CanTrainOrBuildCondition::CanTrainOrBuildCondition(const Unit type, const int playerId) :
    m_playerId(playerId)
{
    m_typeIds = unitIds(type);
    EventManager::registerListener(this, EventManager::PlayerResourceChanged);
}

CanTrainOrBuildCondition::CanTrainOrBuildCondition(const Building type, const int playerId) :
    m_playerId(playerId)
{
    m_typeIds = unitIds(type);
    EventManager::registerListener(this, EventManager::PlayerResourceChanged);

}

void CanTrainOrBuildCondition::onPlayerResourceChanged(Player *player, const genie::ResourceType resourceType, float newValue)
{
    // todo: I'm lazy, add the rest that we want to ignore
    switch(resourceType) {
    case genie::ResourceType::InvalidResource:
    case genie::ResourceType::ConversionRange:
    case genie::ResourceType::CurrentAge:
    case genie::ResourceType::RelicsCaptured:
    case genie::ResourceType::RemarkableDiscovery:
    case genie::ResourceType::MonumentsCaptured:
    case genie::ResourceType::UnitsKilled:
    case genie::ResourceType::PercentMapExplored:
    case genie::ResourceType::Faith:
    case genie::ResourceType::FaithRechargingRate:
    case genie::ResourceType::FarmFoodAmount:
    case genie::ResourceType::CivilianPopulation:
    case genie::ResourceType::MilitaryPopulation:
    case genie::ResourceType::HitPointsKilled:
    case genie::ResourceType::HitPointsRazed:
        DBG << "Ignoring resource type" << resourceType;
        return;

    default:
        break;
    }

    bool satisfied = checkCanBuild(player);
    if (satisfied == m_isSatisfied) {
        return;
    }

    m_isSatisfied = satisfied;
    emit(SatisfiedChanged);
}

bool CanTrainOrBuildCondition::checkCanBuild(const Player *player) const
{
    for (const int id : m_typeIds) {
        if (player->canBuildUnit(id)) {
            return true;
        }
    }
    return false;

}

TechAvailableCondition::TechAvailableCondition(ResearchItem tech, int playerId) :
    m_playerId(playerId),
    m_techId(researchId(tech))
{
    if (m_techId == -1) {
        WARN << "Unhandled tech" << tech;
    }
    EventManager::registerListener(this, EventManager::ResearchComplete);
}

TechAvailableCondition::TechAvailableCondition(Age targetAge, int playerId) :
    m_playerId(playerId),
    m_techId(researchId(targetAge))
{
    if (m_techId == -1) {
        WARN << "Unhandled age" << targetAge;
    }
    EventManager::registerListener(this, EventManager::ResearchComplete);
}

void TechAvailableCondition::onResearchCompleted(Player *player, int researchId)
{
    bool satisfied = player->researchAvailable(m_techId);
    if (satisfied == m_isSatisfied) {
        return;
    }

    m_isSatisfied = satisfied;
    emit(SatisfiedChanged);
}

bool TechAvailableCondition::satisfied(AiRule *owner)
{
    m_isSatisfied = owner->m_owner->m_player->researchAvailable(m_techId);
    return m_isSatisfied;
}

CombatUnitsCount::CombatUnitsCount(Fact type, const RelOp comparison, int targetNumber, const int playerId) :
    m_playerId(playerId),
    m_type(type),
    m_comparison(comparison),
    m_targetValue(targetNumber)
{
    EventManager::registerListener(this, EventManager::UnitChangedGroup);
}


bool Conditions::CombatUnitsCount::satisfied(AiRule *owner)
{
    m_isSatisfied = actualCheck(owner->m_owner->m_player);
    return m_isSatisfied;
}

void ai::Conditions::CombatUnitsCount::onUnitChangedGroup(::Unit *unit, int oldGroup, int newGroup)
{
    if (unit->playerId != m_playerId) {
        return;
    }

    switch (m_type) {
    case Fact::DefendWarboatCount:
    case Fact::DefendSoldierCount:
    case Fact::AttackWarboatCount:
    case Fact::AttackSoldierCount:
        // We only care about those who are either new defenders or attackers (i. e. assigned a group)
        if (oldGroup != 0 && newGroup != 0) {
            return;
        }
        break;
    default:
        break;
    }


    Player::Ptr player = unit->player.lock();
    if (!player) {
        WARN << "unit without player!";
        emit(SatisfiedChanged);// just in case
        return;
    }

    const bool satisfied = actualCheck(player.get());
    if (satisfied != m_isSatisfied) {
        m_isSatisfied = satisfied;
        emit(SatisfiedChanged);
    }
}

bool CombatUnitsCount::actualCheck(Player *player) const
{
    std::vector<int> unitGroupsToCheck;

    switch (m_type) {
    case Fact::DefendWarboatCount:
    case Fact::DefendSoldierCount:
        unitGroupsToCheck.push_back(0);
        break;
    case Fact::AttackWarboatCount:
    case Fact::AttackSoldierCount:
        for (int i=1; i< player->unitGroupCount(); i++) {
            unitGroupsToCheck.push_back(i);
        }
        break;
    case Fact::WarboatCount:
    case Fact::SoldierCount:
        for (int i=0; i< player->unitGroupCount(); i++) {
            unitGroupsToCheck.push_back(i);
        }
        break;
    default:
        WARN << "unhandled type" << m_type;
        return false;
    }

    int unitCount = 0;
    for (const int group : unitGroupsToCheck) {
        for (const ::Unit *unit : player->unitsInGroup(group)) {
            if (!checkType(unit->data())) {
                continue;
            }
            unitCount++;
        }
    }

    return CompareCondition::actualCompare(m_targetValue, m_comparison, unitCount);
}

bool CombatUnitsCount::checkType(const genie::Unit *unit) const
{
    if (unit->Type < genie::Unit::CombatantType) {
        return false;
    }
    if (unit->CombatLevel != genie::Unit::SoldierCombatLevel) {
        return false;
    }

    switch (m_type) {
    case Fact::DefendWarboatCount:
    case Fact::AttackWarboatCount:
    case Fact::WarboatCount:
        return unit->Class == genie::Unit::Warship;

    case Fact::DefendSoldierCount:
    case Fact::AttackSoldierCount:
    case Fact::SoldierCount:
        break;

    default:
        WARN << "unhandled type" << m_type;
        return false;
    }

    return true;

    // Could do this, but we just check combatlevel above
//    switch (unit->Class) {
//    case genie::Unit::Archer:
//    case genie::Unit::Infantry:
//    case genie::Unit::Cavalry:
//    case genie::Unit::Conquistador:
//    case genie::Unit::WarElephant:
//    case genie::Unit::ElephantArcher:
//    case genie::Unit::Phalanx:
//    case genie::Unit::Petard:
//    case genie::Unit::CavalryArcher:
//    case genie::Unit::HandCannoneer:
//    case genie::Unit::TwoHandedSwordsman:
//    case genie::Unit::Pikeman:
//    case genie::Unit::Scout:
//    case genie::Unit::Spearman:

//    case genie::Unit::Raider:
//    case genie::Unit::CavalryRaider:

//    case genie::Unit::SiegeWeapon:
//    case genie::Unit::UnpackedSiegeUnit: // HMM
//    case genie::Unit::PackedUnit: // HMMM
//    case genie::Unit::Hero: // HMMMM
//        return true;

//    default:
//        return false;
//    }
}

Goal::Goal(const int goalId, const RelOp comparison, const int targetValue) :
    m_goalId(goalId),
    m_comparison(comparison),
    m_targetValue(targetValue)
{ }

bool Goal::satisfied(AiRule *owner)
{
    // hackish, TODO: fixme pass in script
    if (owner->m_owner != m_script) {
        if (m_script) {
            // never going to happen, but meh
            m_script->disconnect(this);
        }

        m_script = owner->m_owner;
        m_script->connect(AiScript::GoalChanged, this, &Goal::onGoalChanged);
    }

    return CompareCondition::actualCompare(m_targetValue, m_comparison, m_script->goal(m_goalId));
}

} // namespace Conditions
} //namespace ai
