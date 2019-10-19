#include "AiRule.h"

#include "core/Logger.h"
#include "EnumLogDefs.h"

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type)
{
    switch(type) {
    case Fact::Trueval:
        return std::make_shared<ConstantCondition>(true);
    case Fact::Falseval:
        return std::make_shared<ConstantCondition>(false);
    default:
        break;
    }

    WARN << "unimplemented 0-arg condition" << int(type);
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::Age building)
{
    WARN << "unimplemented condition" << type << building;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Building building)
{
    WARN << "unimplemented condition" << type << building;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << building << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Civ civ)
{
    WARN << "unimplemented condition" << type << civ;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Commodity commodity)
{
    WARN << "unimplemented condition" << type << commodity;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const MapSizeType mapsize)
{
    WARN << "unimplemented condition" << type << mapsize;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const MapTypeName maptype)
{
    WARN << "unimplemented condition" << type << maptype;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber)
{
    WARN << "unimplemented condition" << type << playerNumber;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::PlayerNumberType playerNumber, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << building << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ)
{
    WARN << "unimplemented condition" << type << playerNumber << civ;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << commodity << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance)
{
    WARN << "unimplemented condition" << type << playerNumber << stance;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age)
{
    WARN << "unimplemented condition" << type << playerNumber << comparison << age;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << playerNumber << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::Age age)
{
    WARN << "unimplemented condition" << type << comparison << age;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::DifficultyLevel level)
{
    WARN << "unimplemented condition" << type << comparison << level;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::StartingResourcesType startingResources)
{
    WARN << "unimplemented condition" << type << comparison << startingResources;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::StrategicNumberName strategicNumber, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << strategicNumber << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::Unit unit, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << unit << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number1, const ai::RelOp comparison, const int number2)
{
    WARN << "unimplemented condition" << type << number1 << comparison << number2;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number1, const int number2)
{
    WARN << "unimplemented condition" << type << number1 << number2;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number, const ai::WallType wallType)
{
    WARN << "unimplemented condition" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number)
{
    WARN << "unimplemented condition" << type << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::ResearchItem research)
{
    WARN << "unimplemented condition" << type << research;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::Unit unit)
{
    WARN << "unimplemented condition" << type << unit;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::VictoryConditionName condition)
{
    WARN << "unimplemented condition" << type << condition;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition" << type << comparison << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createOrCondition(const ai::RelOp type, std::shared_ptr<ai::AiRule::Condition> &condition1, std::shared_ptr<ai::AiRule::Condition> &condition2)
{
    WARN << "unimplemented or condition" << type;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Condition> ai::AiRule::createNotCondition(const ai::RelOp type, std::shared_ptr<ai::AiRule::Condition> &condition)
{
    WARN << "unimplemented not condition" << type;
    return nullptr;
}

////////////// actions

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type)
{
    WARN << "unimplemented action" << type;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const std::string &string)
{
    WARN << "unimplemented action" << type << string;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const int number1, const int number2)
{
    WARN << "unimplemented action" << type << number1 << number2;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const int number)
{
    WARN << "unimplemented action" << type << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const int number, const ai::WallType wallType)
{
    WARN << "unimplemented action" << type << number << wallType;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::Age age)
{
    WARN << "unimplemented action" << type << age;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::Building building)
{
    WARN << "unimplemented action" << type << building;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::ResearchItem research)
{
    WARN << "unimplemented action" << type << research;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::Commodity commodity)
{
    WARN << "unimplemented action" << type << commodity;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::Unit unit)
{
    WARN << "unimplemented action" << type << unit;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::Commodity commodity, const int number)
{
    WARN << "unimplemented action" << type << commodity << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const int number)
{
    WARN << "unimplemented action" << type << playernumber << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::StrategicNumberName strategicNumber, const int number)
{
    WARN << "unimplemented action" << type << strategicNumber << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const ai::Commodity commodity, const int number)
{
    WARN << "unimplemented action" << type << playernumber << commodity << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const std::string &string)
{
    WARN << "unimplemented action" << type << playernumber << string;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const ai::DiplomaticStance stance)
{
    WARN << "unimplemented action" << type << playernumber << stance;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const ai::Commodity commodity)
{
    WARN << "unimplemented action" << type << playernumber << commodity;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::DifficultyParameter difficulty, const int number)
{
    WARN << "unimplemented action" << type << difficulty << number;
    return nullptr;
}

std::shared_ptr<ai::AiRule::Action> ai::AiRule::createAction(const ai::ActionType type, const ai::PlayerNumberType playernumber, const int number1, const int number2)
{
    WARN << "unimplemented action" << type << playernumber << number1 << number2;
    return nullptr;
}

ai::AiRule::Condition::~Condition() { }
