#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.h"

class UnitManager;
struct Player;

struct Missile : public Entity
{
public:
    typedef std::shared_ptr<Missile> Ptr;

    Missile(const genie::Unit &data, const std::shared_ptr<Player> &player, UnitManager &unitManager, const MapPos &target);

    bool update(Time time) override;

    bool isFlying() const { return m_isFlying; }

private:
    bool m_isFlying = true;
    std::weak_ptr<Player> m_player;
    const genie::Unit &m_data;
    MapPos m_targetPosition;
    MapPos m_sourcePosition;
    float m_zVelocity = 0.f;
    float m_zAcceleration = 0.f;
    Time m_previousUpdateTime = 0.f;
    float m_angle = 0.f;
};

#endif // MISSILE_H
