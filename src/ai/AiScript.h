#pragma once

#include "ai/gen/enums.h"

#include <memory>
#include <unordered_map>
#include <vector>

class UnitManager;
struct Player;

namespace ai {

struct AiRule;

struct AiScript
{
public:
    AiScript(Player *player);
    AiScript() = delete;

    std::unordered_map<StrategicNumberName, int> strategicNumbers;

    std::vector<std::shared_ptr<AiRule>> rules;


    Player *m_player = nullptr;
};

} // namespace ai
