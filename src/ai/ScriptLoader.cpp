#include "gen/enums.h"

#include "ScriptLoader.h"

#include "ScriptTokenizer.h"
#include "grammar.gen.tab.hpp"
#include "core/Logger.h"
#include "EnumLogDefs.h"

#include "conditions/Conditions.h"
#include "actions/Actions.h"


namespace ai {

ScriptLoader::ScriptLoader(AiPlayer *player) :
    m_script(std::make_shared<AiScript>(player))
{
}

ScriptLoader::~ScriptLoader()
{
}

int ScriptLoader::parse(std::istream& in, std::ostream& out)
{

    ScriptTokenizer scanner {in, *this};
    ScriptParser parser {*this, scanner};
    //parser.set_debug_stream(out);
    //parser.set_debug_level(4);

    int res = parser.parse();
    DBG << "Got script";

    return res;
}


std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type)
{
    switch(type) {
    case Fact::Trueval:
        return std::make_shared<Conditions::ConstantCondition>(true);
    case Fact::Falseval:
        return std::make_shared<Conditions::ConstantCondition>(false);
    default:
        WARN << "unimplemented condition" << type;
        break;
    }

    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Age age)
{
    switch (type) {
    case Fact::CanResearch: // todo: handle cost
        return std::make_shared<Conditions::TechAvailableCondition>(age, m_script->m_player->playerId, false);
    case Fact::CanResearchWithEscrow: // todo: handle escrow
        return std::make_shared<Conditions::TechAvailableCondition>(age, m_script->m_player->playerId, true);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << age;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Building building)
{
    switch(type) {
    case Fact::CanBuild:
        return std::make_shared<Conditions::CanTrainOrBuildCondition>(building, m_script->m_player->playerId, false);
    case Fact::CanBuildWithEscrow:
        return std::make_shared<Conditions::CanTrainOrBuildCondition>(building, m_script->m_player->playerId, true);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << building;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Building building, const RelOp comparison, const int number)
{
    switch(type) {
    case Fact::BuildingTypeCount:
        return std::make_shared<Conditions::UnitTypeCount>(building, comparison, number, m_script->m_player->playerId);
    case Fact::BuildingTypeCountTotal:
        return std::make_shared<Conditions::UnitTypeCount>(building, comparison, number, -1);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << building << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Civ civ)
{
    WARN << "unimplemented condition" << type << civ;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Commodity commodity)
{
    switch(type) {
    case Fact::CanSellCommodity:
        return std::make_shared<Conditions::CanTrade>(commodity, Conditions::CanTrade::Sell, m_script->m_player->playerId);
    case Fact::CanBuyCommodity:
        return std::make_shared<Conditions::CanTrade>(commodity, Conditions::CanTrade::Buy, m_script->m_player->playerId);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << commodity;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number)
{
    switch(type) {
    case Fact::CommodityBuyingPrice:
        return std::make_shared<Conditions::TradingPrice>(Conditions::TradingPrice::Buy, commodity, comparison, m_script->m_player->playerId);
    case Fact::CommoditySellingPrice:
        return std::make_shared<Conditions::TradingPrice>(Conditions::TradingPrice::Sell, commodity, comparison, m_script->m_player->playerId);
    case Fact::EscrowAmount:
        return std::make_shared<Conditions::EscrowAmount>(commodity, comparison, number);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const MapSizeType mapsize)
{
    WARN << "unimplemented condition" << type << mapsize;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const MapTypeName maptype)
{
    WARN << "unimplemented condition" << type << maptype;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber)
{
    WARN << "unimplemented condition" << type << playerNumber;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << building << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ)
{
    WARN << "unimplemented condition" << type << playerNumber << civ;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance)
{
    WARN << "unimplemented condition" << type << playerNumber << stance;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << age;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const Age age)
{
    switch(type) {
    case Fact::CurrentAge:
        return std::make_shared<Conditions::ResourceValue>(genie::ResourceType::CurrentAge, comparison, int(age), m_script->m_player->playerId);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << comparison << age;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const DifficultyLevel level)
{
    switch(type) {
    case ai::Fact::Difficulty:
        return std::make_shared<Conditions::DifficultyCondition>(comparison, level);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << comparison << level;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const RelOp comparison, const StartingResourcesType startingResources)
{
    WARN << "unimplemented condition" << type << comparison << startingResources;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const StrategicNumberName strategicNumber, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << strategicNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Unit unit, const RelOp comparison, const int number)
{
    switch(type) {
    case Fact::UnitTypeCount:
        return std::make_shared<Conditions::UnitTypeCount>(unit, comparison, number, m_script->m_player->playerId);
    case Fact::UnitTypeCountTotal:
        return std::make_shared<Conditions::UnitTypeCount>(unit, comparison, number, -1);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number1, const RelOp comparison, const int number2)
{
    WARN << "unimplemented condition" << type << number1 << comparison << number2;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number1, const int number2)
{
    switch(type) {
    case Fact::Goal:
        return std::make_shared<Conditions::Goal>(number1, RelOp::Equal, number2);
    default:
        break;

    }

    WARN << "unimplemented condition" << type << number1 << number2;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number, const WallType wallType)
{
    WARN << "unimplemented condition" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const int number)
{
    switch(type) {
    case Fact::TimerTriggered:
        return std::make_shared<Conditions::TimerTriggered>(m_script.get(), number);
    default:
        break;
    }
    WARN << "unimplemented condition" << type << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const ResearchItem research)
{
    switch (type) {
    case Fact::CanResearchWithEscrow: // todo: handle escrow
        return std::make_shared<Conditions::TechAvailableCondition>(research, m_script->m_player->playerId, true);
    case Fact::CanResearch: // todo: handle cost
    case Fact::ResearchAvailable:
        return std::make_shared<Conditions::TechAvailableCondition>(research, m_script->m_player->playerId, false);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << research;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const Unit unit)
{
    switch(type) {
    case Fact::CanTrain:
        return std::make_shared<Conditions::CanTrainOrBuildCondition>(unit, m_script->m_player->playerId, false);
    default:
        break;
    }

    WARN << "unimplemented condition" << type << unit;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact type, const VictoryConditionName condition)
{
    WARN << "unimplemented condition" << type << condition;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createCondition(const Fact fact, const RelOp comparison, const int number)
{
    genie::ResourceType type = genie::ResourceType::InvalidResource;
    switch(fact) {
    case Fact::PopulationHeadroom:
        return std::make_shared<Conditions::PopulationHeadroomCondition>(comparison, number, m_script->m_player->playerId);
    case Fact::AttackWarboatCount:
    case Fact::AttackSoldierCount:
    case Fact::DefendWarboatCount:
    case Fact::DefendSoldierCount:
    case Fact::WarboatCount:
    case Fact::SoldierCount:
        return std::make_shared<Conditions::CombatUnitsCount>(fact, comparison, number, m_script->m_player->playerId);
    case Fact::HousingHeadroom:
        type = genie::ResourceType::PopulationHeadroom;
        break;
    case Fact::StoneAmount:
        type = genie::ResourceType::StoneStorage;
        break;
    case Fact::GoldAmount:
        type = genie::ResourceType::GoldStorage;
        break;
    case Fact::FoodAmount:
        type = genie::ResourceType::FoodStorage;
        break;
    case Fact::WoodAmount:
        type = genie::ResourceType::WoodStorage;
        break;
    default:
        break;
    }

    if (type != genie::ResourceType::InvalidResource) {
        return std::make_shared<Conditions::ResourceValue>(type, comparison, number, m_script->m_player->playerId);
    }

    WARN << "unimplemented condition" << fact << comparison << number;
    return nullptr;
}

std::shared_ptr<Condition> ScriptLoader::createAndCondition(std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2)
{
    WARN << "Creating and condition for" << condition1.get() << condition2.get();
    return std::make_shared<Conditions::AndCondition>(condition1, condition2);
}

std::shared_ptr<Condition> ScriptLoader::createOrCondition(std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2)
{
    return std::make_shared<Conditions::OrCondition>(condition1, condition2);
}

std::shared_ptr<Condition> ScriptLoader::createNotCondition(std::shared_ptr<Condition> &condition)
{
    WARN << "unimplemented not condition for" << condition.get();
    return nullptr;
}

////////////// actions

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type)
{
    switch(type) {
    case ActionType::DisableSelf:
        return std::make_shared<Actions::DisableSelf>();
    case ActionType::Resign:
        return std::make_shared<Actions::Resign>();
    default:
        WARN << "unimplemented action" << type;
        break;
    }

    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const std::string &string)
{
    switch(type) {
    case ActionType::ChatLocalToSelf:
        return std::make_shared<Actions::ShowDebugMessage>(string);
    default:
        WARN << "unimplemented action" << type << string;
    }

    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number1, const int number2)
{
    switch(type) {
    case ActionType::SetGoal:
        return std::make_shared<Actions::SetGoal>(number1, number2);
    default:
        WARN << "unimplemented action" << type << number1 << number2;
        break;
    }

    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number)
{
    WARN << "unimplemented action" << type << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const int number, const WallType wallType)
{
    WARN << "unimplemented action" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Age age)
{
    switch(type) {
    case ActionType::Research:
        return std::make_shared<Actions::Research>(age);
    default:
        WARN << "unimplemented action" << type << age;
        break;
    }
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Building building)
{
    switch(type) {
    case ActionType::Build:
        return std::make_shared<Actions::BuildBuilding>(building);
    default:
        WARN << "unimplemented action" << type << building;
        break;
    }

    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const ResearchItem research)
{
    switch(type) {
    case ActionType::Research:
        return std::make_shared<Actions::Research>(research);
    default:
        WARN << "unimplemented action" << type << research;
        break;
    }
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Commodity commodity)
{
    switch(type) {
    case ActionType::BuyCommodity:
        return std::make_shared<Actions::BuyCommodity>(commodity, 100);
    case ActionType::SellCommodity:
        return std::make_shared<Actions::SellCommodity>(commodity, 100);
    case ActionType::ReleaseEscrow:
        return std::make_shared<Actions::ReleaseEscrow>(commodity);
    default:
        WARN << "unimplemented action" << type << commodity;
        break;
    }
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Unit unit)
{
    switch(type) {
    case ActionType::Train:
        return std::make_shared<Actions::TrainUnit>(unit);
    default:
        WARN << "unimplemented action" << type << unit;
    }
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const Commodity commodity, const int number)
{
    switch(type) {
    case ActionType::SetEscrowPercentage:
        return std::make_shared<Actions::SetEscrowPercent>(commodity, number);
    default:
        WARN << "unimplemented action" << type << commodity << number;
        break;
    }
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const int number)
{
    WARN << "unimplemented action" << type << playernumber << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const StrategicNumberName strategicNumber, const int number)
{
    switch(type) {
    case ActionType::SetStrategicNumber:
        return std::make_shared<Actions::SetStrategicNumber>(strategicNumber, number);
    default:
        WARN << "unimplemented action" << type << strategicNumber << number;
        break;
    }

    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity, const int number)
{
    WARN << "unimplemented action" << type << playernumber << commodity << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const std::string &string)
{
    WARN << "unimplemented action" << type << playernumber << string;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const DiplomaticStance stance)
{
    WARN << "unimplemented action" << type << playernumber << stance;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity)
{
    WARN << "unimplemented action" << type << playernumber << commodity;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const DifficultyParameter difficulty, const int number)
{
    WARN << "unimplemented action" << type << difficulty << number;
    return nullptr;
}

std::shared_ptr<Action> ScriptLoader::createAction(const ActionType type, const PlayerNumberType playernumber, const int number1, const int number2)
{
    WARN << "unimplemented action" << type << playernumber << number1 << number2;
    return nullptr;
}

void ScriptLoader::addRule(const std::vector<std::shared_ptr<Condition>> &conditions, const std::vector<std::shared_ptr<Action>> &actions)
{
    std::shared_ptr<AiRule> ret = std::make_shared<AiRule>(m_script.get());
    for (const std::shared_ptr<Condition> &condition : conditions) {
        ret->addCondition(condition);
    }
    for (const std::shared_ptr<Action> &action : actions) {
        ret->addAction(action);
    }
    m_script->rules.push_back(ret);
}
} // namespace ai
