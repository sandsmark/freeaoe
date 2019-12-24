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
        m_housingAvailable = newValue + player->resourcesUsed[genie::ResourceType::CurrentPopulation];
        break;
    default:
        return;
    }

    if (m_populationCap == -1) {
        m_populationCap = player->resourcesAvailable(genie::ResourceType::CurrentPopulation) + player->resourcesUsed[genie::ResourceType::CurrentPopulation];
    }

    DBG << "housing available:" << m_housingAvailable << "pop cap" << m_populationCap;
    m_currentValue = m_populationCap - m_housingAvailable;

    bool satisfied = CompareCondition::actualCompare(m_targetValue, m_relOp, m_currentValue);
    if (satisfied == m_isSatisfied) {
        return;
    }
    m_isSatisfied = satisfied;
    emit(SatisfiedChanged);

}

} // namespace Conditions
} //namespace ai
