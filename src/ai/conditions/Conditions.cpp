#include "Conditions.h"
#include "global/EventManager.h"

#include "mechanics/Unit.h"

#include "ai/Ids.h"

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

} // namespace Conditions
} //namespace ai
