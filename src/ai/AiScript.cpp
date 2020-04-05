#include "AiScript.h"

#include "mechanics/Player.h"

namespace ai
{

void AiScript::setEscrow(const genie::ResourceType resource, float amount)
{
    m_player->m_reserved[resource] = amount;
}

float AiScript::escrowAmount(const genie::ResourceType resource) const
{
    ResourceMap::const_iterator escrowIt = m_player->m_reserved.find(resource);
    if (escrowIt != m_player->m_reserved.end()) {
        return escrowIt->second;
    }

    return 0.f;
}

} // namespace ai
