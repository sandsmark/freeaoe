#include "Conditions.h"
#include "global/EventManager.h"

namespace ai {
namespace Conditions {

CurrentAge::CurrentAge(const Age targetAge) : m_targetAge(targetAge)
{
    EventManager::registerListener(this, EventManager::PlayerResourceChanged);
}

} // namespace Conditions
} //namespace ai
