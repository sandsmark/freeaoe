#pragma once

#include "ai/gen/enums.h"

#include "ai/gen/enums.h"

#include <string>
#include <map>
#include <iostream>
#include <memory>

struct Player;

namespace ai {

struct Condition;
struct Action;

class ScriptLoader {
public:
    ScriptLoader(const int playerId) : m_playerId(playerId) {};
    virtual ~ScriptLoader() {};

    int parse(std::istream& in, std::ostream& out);

    std::shared_ptr<Condition> createCondition(const Fact type);
    std::shared_ptr<Condition> createCondition(const Fact type, const Age age);
    std::shared_ptr<Condition> createCondition(const Fact type, const Building building);
    std::shared_ptr<Condition> createCondition(const Fact type, const Building building, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const Civ civ);
    std::shared_ptr<Condition> createCondition(const Fact type, const Commodity commodity);
    std::shared_ptr<Condition> createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const MapSizeType mapsize);
    std::shared_ptr<Condition> createCondition(const Fact type, const MapTypeName maptype);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age);
    std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const Age age);
    std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const DifficultyLevel level);
    std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const StartingResourcesType startingResources);
    std::shared_ptr<Condition> createCondition(const Fact type, const StrategicNumberName strategicNumber, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const Unit unit, const RelOp comparison, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const int number1, const RelOp comparison, const int number2);
    std::shared_ptr<Condition> createCondition(const Fact type, const int number1, const int number2);
    std::shared_ptr<Condition> createCondition(const Fact type, const int number, const WallType wallType);
    std::shared_ptr<Condition> createCondition(const Fact type, const int number);
    std::shared_ptr<Condition> createCondition(const Fact type, const ResearchItem research);
    std::shared_ptr<Condition> createCondition(const Fact type, const Unit unit);
    std::shared_ptr<Condition> createCondition(const Fact type, const VictoryConditionName condition);
    std::shared_ptr<Condition> createCondition(const Fact fact, const RelOp comparison, const int number);

    std::shared_ptr<Condition> createAndCondition(std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2);
    std::shared_ptr<Condition> createOrCondition(std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2);
    std::shared_ptr<Condition> createNotCondition(std::shared_ptr<Condition> &condition);

    std::shared_ptr<Action> createAction(const ActionType type);
    std::shared_ptr<Action> createAction(const ActionType type, const std::string &string);
    std::shared_ptr<Action> createAction(const ActionType type, const int number1, const int number2);
    std::shared_ptr<Action> createAction(const ActionType type, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const int number, const WallType wallType);
    std::shared_ptr<Action> createAction(const ActionType type, const Age age);
    std::shared_ptr<Action> createAction(const ActionType type, const Building building);
    std::shared_ptr<Action> createAction(const ActionType type, const ResearchItem research);
    std::shared_ptr<Action> createAction(const ActionType type, const Commodity commodity);
    std::shared_ptr<Action> createAction(const ActionType type, const Unit unit);
    std::shared_ptr<Action> createAction(const ActionType type, const Commodity commodity, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const StrategicNumberName strategicNumber, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const std::string &string);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const DiplomaticStance stance);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity);
    std::shared_ptr<Action> createAction(const ActionType type, const DifficultyParameter difficulty, const int number);
    std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const int number1, const int number2);

private:
    const int m_playerId;
};

}

