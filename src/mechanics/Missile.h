#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.h"

class UnitManager;
struct Player;

struct Missile : public Entity
{
public:
    enum BlastType : uint8_t {
        DamageResources = 0,
        DamageTrees = 1,
        DamageNearby = 2,
        DamageTargetOnly = 3
    };

    typedef std::shared_ptr<Missile> Ptr;

    Missile(const genie::Unit &data, const std::shared_ptr<Player> &player, UnitManager &unitManager, const MapPos &target);

    void setBlastType(const BlastType type, const float radius);

    bool update(Time time) override;

    bool isFlying() const { return m_isFlying; }
    bool isExploding() const { return !m_isFlying && m_renderer.currentFrame() < m_renderer.frameCount() - 1; }

private:
    bool m_isFlying = true;
    std::weak_ptr<Player> m_player;
    const genie::Unit &m_data;
    MapPos m_targetPosition;
    float m_zVelocity = 0.f;
    float m_zAcceleration = 0.f;
    Time m_previousUpdateTime = 0.f;
    float m_angle = 0.f;
    float m_startingElevation = 0;
    float m_blastRadius = 0.f;
    BlastType m_blastType = DamageTargetOnly;
};

#endif // MISSILE_H
