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

    static std::unique_ptr<Condition> createCondition(const Fact type);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Building building);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Building building, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Civ civ);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Commodity commodity);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Commodity commodity, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const MapSizeType mapsize);
    static std::unique_ptr<Condition> createCondition(const Fact type, const MapTypeName maptype);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Building building, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Civ civ);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Commodity commodity, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const DiplomaticStance stance);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const RelOp comparison, const Age age);
    static std::unique_ptr<Condition> createCondition(const Fact type, const PlayerNumberType playerNumber, const Unit unit, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const Age age);
    static std::unique_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const DifficultyLevel age);
    static std::unique_ptr<Condition> createCondition(const Fact type, const RelOp comparison, const StartingResourcesType startingResources);
    static std::unique_ptr<Condition> createCondition(const Fact type, const StrategicNumberName, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Unit unit, const RelOp comparison, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const int number1, const RelOp comparison, const int number2);
    static std::unique_ptr<Condition> createCondition(const Fact type, const int number1, const int number2);
    static std::unique_ptr<Condition> createCondition(const Fact type, const int number, const WallType wallType);
    static std::unique_ptr<Condition> createCondition(const Fact type, const int number);
    static std::unique_ptr<Condition> createCondition(const Fact type, const ResearchItem research);
    static std::unique_ptr<Condition> createCondition(const Fact type, const Unit unit);
    static std::unique_ptr<Condition> createCondition(const Fact type, const VictoryConditionName);

    static std::unique_ptr<Condition> createOrCondition(const RelOp type, std::unique_ptr<Condition> &condition1, std::unique_ptr<Condition> &condition2);
    static std::unique_ptr<Condition> createNotCondition(const RelOp type, std::unique_ptr<Condition> &condition);

    struct Action {
        virtual ~Action();
        virtual void trigger(UnitManager *unitManager);
    };

    std::vector<std::unique_ptr<Condition>> conditions;
    std::vector<std::unique_ptr<Action>> actions;
};

} // namespace ai
