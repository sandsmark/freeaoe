#pragma once

#include "global/EventListener.h"
#include "core/SignalEmitter.h"
#include "gen/enums.h"

#include <memory>
#include <vector>

class UnitManager;

namespace ai {

struct AiRule
{
    struct Condition : public EventListener, public SignalEmitter<Condition> {
        virtual ~Condition();
        virtual bool satisfied() = 0;
    };

    // Mostly things resolved at parse time, like difficulty
    struct ConstantCondition : public Condition {
        ConstantCondition(const bool _value) : value(_value) {}
        bool satisfied() override { return value; }
        const bool value;
    };

    static std::shared_ptr<Condition> createCondition(const Fact type);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Age building);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Building building);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Building building, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Civ civ);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Commodity commodity);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const MapSizeType mapsize);
    static std::shared_ptr<Condition> createCondition(const Fact type, const MapTypeName maptype);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age);
    static std::shared_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const Age age);
    static std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const DifficultyLevel level);
    static std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const StartingResourcesType startingResources);
    static std::shared_ptr<Condition> createCondition(const Fact type, const StrategicNumberName strategicNumber, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Unit unit, const RelOp comparison, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const int number1, const RelOp comparison, const int number2);
    static std::shared_ptr<Condition> createCondition(const Fact type, const int number1, const int number2);
    static std::shared_ptr<Condition> createCondition(const Fact type, const int number, const WallType wallType);
    static std::shared_ptr<Condition> createCondition(const Fact type, const int number);
    static std::shared_ptr<Condition> createCondition(const Fact type, const ResearchItem research);
    static std::shared_ptr<Condition> createCondition(const Fact type, const Unit unit);
    static std::shared_ptr<Condition> createCondition(const Fact type, const VictoryConditionName condition);
    static std::shared_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const int number);

    static std::shared_ptr<Condition> createOrCondition(const RelOp type, std::shared_ptr<Condition> &condition1, std::shared_ptr<Condition> &condition2);
    static std::shared_ptr<Condition> createNotCondition(const RelOp type, std::shared_ptr<Condition> &condition);

    struct Action {
        virtual ~Action();
        virtual void trigger(UnitManager *unitManager) = 0;
    };

    static std::shared_ptr<Action> createAction(const ActionType type);
    static std::shared_ptr<Action> createAction(const ActionType type, const std::string &string);
    static std::shared_ptr<Action> createAction(const ActionType type, const int number1, const int number2);
    static std::shared_ptr<Action> createAction(const ActionType type, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const int number, const WallType wallType);
    static std::shared_ptr<Action> createAction(const ActionType type, const Age age);
    static std::shared_ptr<Action> createAction(const ActionType type, const Building building);
    static std::shared_ptr<Action> createAction(const ActionType type, const ResearchItem research);
    static std::shared_ptr<Action> createAction(const ActionType type, const Commodity commodity);
    static std::shared_ptr<Action> createAction(const ActionType type, const Unit unit);
    static std::shared_ptr<Action> createAction(const ActionType type, const Commodity building, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const StrategicNumberName strategicNumber, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const std::string &string);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const DiplomaticStance stance);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const Commodity commodity);
    static std::shared_ptr<Action> createAction(const ActionType type, const DifficultyParameter difficulty, const int number);
    static std::shared_ptr<Action> createAction(const ActionType type, const PlayerNumberType playernumber, const int number1, const int number2);

    // should really have unique_ptr, but bison is a pile of shit
    std::vector<std::shared_ptr<Condition>> conditions;
    std::vector<std::shared_ptr<Action>> actions;
};

} // namespace ai
