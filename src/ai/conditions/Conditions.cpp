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
    switch(type) {
    case Unit::ArcherLine:
        m_typeIds.insert(unitId(Unit::Archer));
        m_typeIds.insert(unitId(Unit::Crossbowman));
        m_typeIds.insert(unitId(Unit::Arbalest));
        break;

    case Unit::CavalryArcherLine:
        m_typeIds.insert(unitId(Unit::CavalryArcher));
        m_typeIds.insert(unitId(Unit::HeavyCavalryArcher));
        break;

    case Unit::SkirmisherLine:
        m_typeIds.insert(unitId(Unit::Skirmisher));
        m_typeIds.insert(unitId(Unit::EliteSkirmisher));
//        m_typeIds.insert(unitId(Unit::ImperialSkirmisher)); TODO: HD rise of the rajas
        break;

    case Unit::EagleWarriorLine:
//        m_typeIds.insert(unitId(Unit::EagleScout)); // TODO the forgotten
        m_typeIds.insert(unitId(Unit::EagleWarrior));
        m_typeIds.insert(unitId(Unit::EliteEagleWarrior));
        break;

    case Unit::MilitiamanLine:
        m_typeIds.insert(unitId(Unit::Militiaman));
        m_typeIds.insert(unitId(Unit::ManAtArms));
        m_typeIds.insert(unitId(Unit::LongSwordsman));
        m_typeIds.insert(unitId(Unit::TwoHandedSwordsman));
        m_typeIds.insert(unitId(Unit::Champion));
        break;

    case Unit::SpearmanLine:
        m_typeIds.insert(unitId(Unit::Spearman));
        m_typeIds.insert(unitId(Unit::Pikeman));
        m_typeIds.insert(unitId(Unit::Halberdier));
        break;

    case Unit::BerserkLine:
        m_typeIds.insert(unitId(Unit::Berserk));
        m_typeIds.insert(unitId(Unit::EliteBerserk));
        break;

    case Unit::CataphractLine:
        m_typeIds.insert(unitId(Unit::Cataphract));
        m_typeIds.insert(unitId(Unit::EliteCataphract));
        break;

    case Unit::ChuKoNuLine:
        m_typeIds.insert(unitId(Unit::ChuKoNu));
        m_typeIds.insert(unitId(Unit::EliteChuKoNu));
        break;

    case Unit::ConquistadorLine:
        m_typeIds.insert(unitId(Unit::Conquistador));
        m_typeIds.insert(unitId(Unit::EliteConquistador));
        break;

    case Unit::HuskarlLine:
        m_typeIds.insert(unitId(Unit::Huskarl));
        m_typeIds.insert(unitId(Unit::EliteHuskarl));
        break;

    case Unit::JaguarWarriorLine:
        m_typeIds.insert(unitId(Unit::JaguarWarrior));
        m_typeIds.insert(unitId(Unit::EliteJaguarWarrior));
        break;

    case Unit::JanissaryLine:
        m_typeIds.insert(unitId(Unit::Janissary));
        m_typeIds.insert(unitId(Unit::EliteJanissary));
        break;

    case Unit::LongbowmanLine:
        m_typeIds.insert(unitId(Unit::Longbowman));
        m_typeIds.insert(unitId(Unit::EliteLongbowman));
        break;

    case Unit::MamelukeLine:
        m_typeIds.insert(unitId(Unit::Mameluke));
        m_typeIds.insert(unitId(Unit::EliteMameluke));
        break;

    case Unit::MangudaiLine:
        m_typeIds.insert(unitId(Unit::Mangudai));
        m_typeIds.insert(unitId(Unit::EliteMangudai));
        break;

    case Unit::PlumedArcherLine:
        m_typeIds.insert(unitId(Unit::PlumedArcher));
        m_typeIds.insert(unitId(Unit::ElitePlumedArcher));
        break;

    case Unit::SamuraiLine:
        m_typeIds.insert(unitId(Unit::Samurai));
        m_typeIds.insert(unitId(Unit::EliteSamurai));
        break;

    case Unit::TarkanLine:
        m_typeIds.insert(unitId(Unit::Tarkan));
        m_typeIds.insert(unitId(Unit::EliteTarkan));
        break;

    case Unit::TeutonicKnightLine:
        m_typeIds.insert(unitId(Unit::TeutonicKnight));
        m_typeIds.insert(unitId(Unit::EliteTeutonicKnight));
        break;

    case Unit::ThrowingAxemanLine:
        m_typeIds.insert(unitId(Unit::ThrowingAxeman));
        m_typeIds.insert(unitId(Unit::EliteThrowingAxeman));
        break;

    case Unit::WarElephantLine:
        m_typeIds.insert(unitId(Unit::WarElephant));
        m_typeIds.insert(unitId(Unit::EliteWarElephant));
        break;

    case Unit::WarWagonLine:
        m_typeIds.insert(unitId(Unit::WarWagon));
        m_typeIds.insert(unitId(Unit::EliteWarWagon));
        break;

    case Unit::WoadRaiderLine:
        m_typeIds.insert(unitId(Unit::WoadRaider));
        m_typeIds.insert(unitId(Unit::EliteWoadRaider));
        break;

    case Unit::CannonGalleonLine:
        m_typeIds.insert(unitId(Unit::CannonGalleon));
        m_typeIds.insert(unitId(Unit::EliteCannonGalleon));
        break;

    case Unit::DemolitionShipLine:
        // todo: hd demolition raft
        m_typeIds.insert(unitId(Unit::DemolitionShip));
        m_typeIds.insert(unitId(Unit::HeavyDemolitionShip));
        break;

    case Unit::FireShipLine:
        // todo: hd fire galley
        m_typeIds.insert(unitId(Unit::FireShip));
        m_typeIds.insert(unitId(Unit::FastFireShip));
        break;

    case Unit::GalleyLine:
        m_typeIds.insert(unitId(Unit::Galley));
        m_typeIds.insert(unitId(Unit::WarGalley));
        m_typeIds.insert(unitId(Unit::Galleon));
        break;

    case Unit::TurtleShipLine:
        m_typeIds.insert(unitId(Unit::TurtleShip));
        m_typeIds.insert(unitId(Unit::EliteTurtleShip));
        break;

    case Unit::LongboatLine:
        m_typeIds.insert(unitId(Unit::Longboat));
        m_typeIds.insert(unitId(Unit::EliteLongboat));
        break;

    case Unit::BatteringRamLine:
        m_typeIds.insert(unitId(Unit::BatteringRam));
        m_typeIds.insert(unitId(Unit::CappedRam));
        m_typeIds.insert(unitId(Unit::SiegeRam));
        break;

    case Unit::MangonelLine:
        m_typeIds.insert(unitId(Unit::Mangonel));
        m_typeIds.insert(unitId(Unit::Onager));
        m_typeIds.insert(unitId(Unit::SiegeOnager));
        break;

    case Unit::ScorpionLine:
        m_typeIds.insert(unitId(Unit::Scorpion));
        m_typeIds.insert(unitId(Unit::HeavyScorpion));
        break;

    case Unit::CamelLine:
        m_typeIds.insert(unitId(Unit::Camel));
        m_typeIds.insert(unitId(Unit::HeavyCamel));
        // todo: imperial camel hd
        break;

    case Unit::KnightLine:
        m_typeIds.insert(unitId(Unit::Knight));
        m_typeIds.insert(unitId(Unit::Cavalier));
        m_typeIds.insert(unitId(Unit::Paladin));
        break;

    case Unit::ScoutCavalryLine:
        m_typeIds.insert(unitId(Unit::ScoutCavalry));
        m_typeIds.insert(unitId(Unit::LightCavalry));
        m_typeIds.insert(unitId(Unit::Hussar));
        break;

    case Unit::MyUniqueUnit:
    case Unit::MyUniqueUnitLine:
    case Unit::MyEliteUniqueUnit:
        WARN << "Civ specific stuff not implemented yet";
        break;

    default:
        m_typeIds.insert(unitId(type));
        break;
    }
}

UnitTypeCount::UnitTypeCount(const Building type, const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_playerId(playerId)
{
    switch(type) {
    case Building::WatchTowerLine:
    case Building::WatchTower: // apparently a bug that WatchTower means the entire upgrade line
        m_typeIds.insert(unitId(Building::WatchTower));
        m_typeIds.insert(unitId(Building::GuardTower));
        m_typeIds.insert(unitId(Building::Keep));
        break;
    default:
        m_typeIds.insert(unitId(type));
        break;
    }
}

UnitTypeCount::UnitTypeCount(const WallType type, const RelOp comparison, const int targetValue, int playerId) :
    m_relOp(comparison),
    m_playerId(playerId)
{
    switch(type) {
    case WallType::StoneWallLine:
        m_typeIds.insert(unitId(WallType::StoneWall));
        m_typeIds.insert(unitId(WallType::FortifiedWall));
        break;
    default:
        m_typeIds.insert(unitId(type));
        break;
    }
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
