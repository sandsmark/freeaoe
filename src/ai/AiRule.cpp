#include "AiRule.h"

#include "core/Logger.h"

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Building building)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Civ civ)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Commodity commodity)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const MapSizeType mapsize)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const MapTypeName maptype)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::Age age)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::DifficultyLevel age)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::RelOp comparison, const ai::StartingResourcesType startingResources)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::StrategicNumberName, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::Unit unit, const ai::RelOp comparison, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number1, const ai::RelOp comparison, const int number2)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number1, const int number2)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number, const ai::WallType wallType)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const int number)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::ResearchItem research)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::Unit unit)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createCondition(const ai::Fact type, const ai::VictoryConditionName)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createOrCondition(const ai::RelOp type, std::unique_ptr<ai::AiRule::Condition> &condition1, std::unique_ptr<ai::AiRule::Condition> &condition2)
{
    WARN << "unimplemented condition";
    return nullptr;
}

std::unique_ptr<ai::AiRule::Condition> ai::AiRule::createNotCondition(const ai::RelOp type, std::unique_ptr<ai::AiRule::Condition> &condition)
{
    WARN << "unimplemented condition";
    return nullptr;
}
