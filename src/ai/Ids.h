#pragma once
#include "gen/enums.h"

#include "core/Logger.h"

#include <unordered_set>

namespace ai
{
    int researchId(const Age age);
    int researchId(const ResearchItem item);

    enum class OtherUnits {
        Gate
    };

    int unitId(const OtherUnits &unit);

    int unitId(const WallType &wall);

    int unitId(const Building &building);

    int unitId(const Unit &unit);

    std::unordered_set<int> unitIds(const Unit type);

    std::unordered_set<int> unitIds(const Building type);

    std::unordered_set<int> unitIds(const WallType type);

} // namespace ai
