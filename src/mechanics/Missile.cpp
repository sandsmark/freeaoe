#include "Missile.h"

#include "resource/LanguageManager.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Map.h"

#include <genie/dat/Unit.h>

Missile::Missile(const genie::Unit &data, const std::shared_ptr<Player> &player, UnitManager &unitManager, const MapPos &target) :
    Entity(Type::Missile, LanguageManager::getString(data.LanguageDLLName) + " (" + std::to_string(data.ID) + ")", unitManager.map()),
    m_player(player),
    m_data(data),
    m_targetPosition(target)
{
    DBG << "Firing at" << target;
    defaultGraphics = AssetManager::Inst()->getGraphic(data.StandingGraphic.first);
    m_renderer.setGraphic(defaultGraphics);
}


bool Missile::update(Time time)
{
    MapPtr map = m_map.lock();
    if (!map) {
        WARN << "No map!";
        return false;
    }
    if (position().z <= map->elevationAt(position())) {
        DBG << "we hit the ground";
        m_isFlying = false;
        return false;
    }
//    DBG << "MIssile moving" << time;
    if (m_previousUpdateTime == 0) {
        const float distance = position().distance(m_targetPosition);
        m_angle = std::atan2(m_targetPosition.y - position().y, m_targetPosition.x - position().x);
        DBG << m_angle;
        m_zVelocity = m_data.Speed * sin(m_data.Missile.ProjectileArc);
        m_zAcceleration = 2 * m_zVelocity / distance;
        m_previousUpdateTime = time;
        m_sourcePosition = position();
        return false;
    }

    const float elapsed = time - m_previousUpdateTime;
//    m_previousUpdateTime = time;

    const float movement = elapsed * m_data.Speed * 0.015;
    DBG << movement;

    MapPos newPos = position();
    newPos.x = movement * cos(m_angle) + m_sourcePosition.x;
    newPos.y = movement * sin(m_angle) + m_sourcePosition.y;

    m_zVelocity -= m_zAcceleration;
    newPos.z += m_zVelocity;
//    DBG << position() << newPos;
    setPosition(newPos);

    return true;
}
