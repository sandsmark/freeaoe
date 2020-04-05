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

void AiScript::showDebugMessage(const std::string &message)
{
    // TODO: for now just print it to the terminal
    // Should probably show it on screen or separate window or something
    WARN << " ========== AI " << m_player->name << message;

}

} // namespace ai
