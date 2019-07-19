#include "Missile.h"

#include "audio/AudioPlayer.h"
#include "resource/LanguageManager.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include "mechanics/Civilization.h"
#include "core/Constants.h"

#include <genie/dat/Unit.h>

Missile::Missile(const genie::Unit &data, const Unit::Ptr &sourceUnit, const MapPos &target, const Unit::Ptr &targetUnit) :
    Entity(Type::Missile, LanguageManager::getString(data.LanguageDLLName) + " (" + std::to_string(data.ID) + ")"),
    playerId(sourceUnit->playerId),
    m_sourceUnit(sourceUnit),
    m_targetUnit(targetUnit),
    m_player(sourceUnit->player),
    m_unitManager(sourceUnit->unitManager()),
    m_data(data),
    m_targetPosition(target)
{
    m_startingElevation = sourceUnit->position().z;
    m_attacks = sourceUnit->data()->Combat.Attacks;
    sourceUnit->activeMissiles++;
    DBG << "Firing at" << target;
    defaultGraphics = AssetManager::Inst()->getGraphic(data.StandingGraphic.first);
    m_renderer.setGraphic(defaultGraphics);
}

Missile::~Missile()
{
    Unit::Ptr sourceUnit = m_sourceUnit.lock();
    if (sourceUnit) {
        sourceUnit->activeMissiles--;
    }
}

void Missile::setBlastType(const BlastType type, const float radius) noexcept
{
    m_blastType = type;

    switch(type) {
    case DamageNearby:
        m_blastRadius = radius;
        break;
    case DamageResources:
        break;
    case DamageTrees:
        break;
    case DamageTargetOnly:
        break;
    default:
        m_blastType = DamageTargetOnly;
        break;
    }
}


bool Missile::update(Time time) noexcept
{
    if (isExploding()) {
        m_renderer.setCurrentFrame(m_renderer.currentFrame() + 1);
        return true;
    }

    if (!m_isFlying) {
        return false;
    }

    MapPtr map = m_map.lock();
    if (!map) {
        WARN << "No map!";
        return false;
    }

    Player::Ptr player = m_player.lock();

    if (position().z <= map->elevationAt(position())) {
        DBG << "we hit the ground";
        die();
        return false;
    }

    if (m_previousUpdateTime == 0) {
        m_distanceLeft = position().distance(m_targetPosition);
        m_angle = std::atan2(m_targetPosition.y - position().y, m_targetPosition.x - position().x);
        float flightTime = m_distanceLeft / m_data.Speed;
        float timeToApex = flightTime / 2;
        m_zVelocity = m_data.Missile.ProjectileArc * m_distanceLeft / timeToApex;
        m_zAcceleration = m_zVelocity / timeToApex;
        m_previousUpdateTime = time;
        m_previousSmokeTime = time;
        return false;
    }

    const float elapsed = time - m_previousUpdateTime;
    m_previousUpdateTime = time;

    const float movement = elapsed * m_data.Speed * 0.15;
    m_distanceLeft -= movement;

    MapPos newPos = position();
    newPos.x += movement * cos(m_angle);
    newPos.y += movement * sin(m_angle);

    m_zVelocity -= m_zAcceleration * elapsed * 0.15;
    newPos.z += m_zVelocity * elapsed * 0.15;

    int tileX = newPos.x / Constants::TILE_SIZE;
    int tileY = newPos.y / Constants::TILE_SIZE;

    if (!map->isValidTile(tileX, tileY)) {
        DBG << "out of bounds";
        m_isFlying = false;
        return false;
    }

    if (m_data.Moving.TrackingUnit != -1&& rand() % 100 < m_data.Moving.TrackingUnitDensity * 100 * 0.15) {
//        DBG << (m_data.Moving.TrackingUnitDensity / 0.015) << time - m_previousSmokeTime ;
        m_previousSmokeTime = time;
        if (player) {
            const genie::Unit &trailingData = player->civilization.unitData(m_data.Moving.TrackingUnit);
            DecayingEntity::Ptr trailingUnit = std::make_shared<DecayingEntity>(trailingData.StandingGraphic.first, 0.f);
            trailingUnit->setMap(m_map.lock());
            trailingUnit->setPosition(position());
            m_unitManager.addDecayingEntity(trailingUnit);
        }

    }

    m_renderer.setAngle(position().toScreen().angleTo(newPos.toScreen()));

    setPosition(newPos);

    std::vector<Unit::Ptr> hitUnits;

    if (m_blastType == DamageTargetOnly) {
        Unit::Ptr targetUnit = m_targetUnit.lock();
        if (!targetUnit) {
            return true;
        }
        const float xSize = (targetUnit->data()->Size.x + m_data.Size.x) * Constants::TILE_SIZE;
        const float ySize = (targetUnit->data()->Size.y + m_data.Size.y) * Constants::TILE_SIZE;
        const float xDistance = std::abs(targetUnit->position().x - newPos.x);
        const float yDistance = std::abs(targetUnit->position().y - newPos.y);

        if (xDistance > xSize || yDistance > ySize) {
            return true;
        }
        DBG << debugName << "hit out target" << targetUnit->debugName;

        hitUnits.push_back(targetUnit);
    } else {
        Unit::Ptr sourceUnit = m_sourceUnit.lock();
        for (int dx = tileX-1; dx<=tileX+1; dx++) {
            for (int dy = tileY-1; dy<=tileY+1; dy++) {
                const std::vector<std::weak_ptr<Entity>> &entities = map->entitiesAt(dx, dy);
                if (entities.empty()) {
                    continue;
                }

                for (const std::weak_ptr<Entity> &entity : entities) {
                    Unit::Ptr otherUnit = Entity::asUnit(entity);
                    if (IS_UNLIKELY(!otherUnit)) {
                        continue;
                    }

                    if (IS_UNLIKELY(otherUnit == sourceUnit)) {
                        continue;
                    }

                    if (newPos.z > otherUnit->data()->Size.z) {
                        continue;
                    }

                    const float xSize = (otherUnit->data()->Size.x + m_data.Size.x + m_blastRadius) * Constants::TILE_SIZE;
                    const float ySize = (otherUnit->data()->Size.y + m_data.Size.y + m_blastRadius) * Constants::TILE_SIZE;
                    const float xDistance = std::abs(otherUnit->position().x - newPos.x);
                    const float yDistance = std::abs(otherUnit->position().y - newPos.y);

                    if (IS_UNLIKELY(xDistance < xSize && yDistance < ySize)) {
                        hitUnits.push_back(otherUnit);
                        break;
                    }
                }
            }
        }
    }

    if (hitUnits.empty()) {
        return true;
    }

    // Only pick the closest
    if (m_blastType != DamageNearby) {
        Unit::Ptr closestUnit;
        float closestDistance = std::numeric_limits<float>::infinity();
        for (const Unit::Ptr &unit : hitUnits) {
            const float distance = unit->position().distance(position());
            if (distance < closestDistance || !closestUnit) {
                closestDistance = distance;
                closestUnit = unit;
            }
        }
        hitUnits.clear();
        hitUnits.push_back(closestUnit);
    }

    if (!m_data.Missile.HitMode) {
        die();
    } else if (m_distanceLeft <= 0) {
        die();
    }

    int playerId = player ? player->playerId : -1;
    for (Unit::Ptr &hitUnit : hitUnits) {
        if (m_blastType != DamageTrees && hitUnit->data()->Class == genie::Unit::Tree) {
            continue;
        }

        if (m_data.Missile.HitMode && hitUnit->playerId == playerId) {
            continue;
        }

        float damageMultiplier = 1.f;
        if (hitUnit->position().z < m_startingElevation) {
            damageMultiplier = 3.f/2.f;
        }
        DBG << debugName << "hit a unit" << hitUnit->debugName << "damage multiplier" << damageMultiplier;
        for (const genie::unit::AttackOrArmor &attack : m_attacks) {
            hitUnit->takeDamage(attack, damageMultiplier);
        }
    }

    return true;
}

void Missile::die()
{
    m_isFlying = false;
    m_renderer.setGraphic(m_data.DyingGraphic);

    Player::Ptr player = m_player.lock();
    if (player && m_data.DyingSound != -1) {
        AudioPlayer::instance().playSound(m_data.DyingSound, player->civilization.id());
    }
}
