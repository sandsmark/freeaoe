#pragma once

#include "gen/enums.h"

#include <memory>
#include <vector>

struct Condition;
struct Action;

namespace ai {

struct AiRule
{

    // should really have unique_ptr, but bison is a pile of shit
    std::vector<std::shared_ptr<Condition>> conditions;
    std::vector<std::shared_ptr<Action>> actions;
};

} // namespace ai
