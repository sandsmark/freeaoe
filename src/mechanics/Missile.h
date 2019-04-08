#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.h"
#include "Unit.h"
#include "genie/dat/unit/AttackOrArmor.h"

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

    ~Missile();

    typedef std::shared_ptr<Missile> Ptr;

    Missile(const genie::Unit &data, const Unit::Ptr &sourceUnit, const MapPos &target, const Unit::Ptr &targetUnit);

    void setBlastType(const BlastType type, const float radius);

    bool update(Time time) override;

    bool isFlying() const { return m_isFlying; }
    bool isExploding() const { return !m_isFlying && m_renderer.currentFrame() < m_renderer.frameCount() - 1; }

private:
    void die();

    bool m_isFlying = true;
    std::weak_ptr<Unit> m_sourceUnit;
    std::weak_ptr<Unit> m_targetUnit;
    std::weak_ptr<Player> m_player;
    UnitManager &m_unitManager;
    const genie::Unit &m_data;
    MapPos m_targetPosition;
    float m_zVelocity = 0.f;
    float m_zAcceleration = 0.f;
    Time m_previousUpdateTime = 0.f;
    Time m_previousSmokeTime = 0.f;
    float m_angle = 0.f;
    float m_startingElevation = 0;
    float m_blastRadius = 0.f;
    float m_distanceLeft = 0.f;
    BlastType m_blastType = DamageTargetOnly;
    std::vector<genie::unit::AttackOrArmor> m_attacks;
};

#endif // MISSILE_H
