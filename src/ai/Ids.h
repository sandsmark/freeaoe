#pragma once
#include "gen/enums.h"

#include "core/Logger.h"

#include <unordered_set>

namespace ai
{
    int researchId(const Age age);
    int researchId(const ResearchItem item, const Civ civ);

    enum class OtherUnits {
        Gate
    };


//    int unitId(const WallType &wall);

//    int unitId(const Building &building);

//    int unitId(const Unit &unit);

    Civ civFromId(const int id);

    std::unordered_set<int> unitIds(const OtherUnits &unit);

    std::unordered_set<int> unitIds(const Unit type, const Civ civ);

    std::unordered_set<int> unitIds(const Building type);

    std::unordered_set<int> unitIds(const WallType type);

} // namespace ai
