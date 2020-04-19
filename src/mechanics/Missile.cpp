#include "Missile.h"

#include <genie/Types.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/Combat.h>
#include <genie/dat/unit/Missile.h>
#include <genie/dat/unit/Moving.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <limits>
#include <string>
#include <utility>

#include "audio/AudioPlayer.h"
#include "resource/LanguageManager.h"
#include "resource/AssetManager.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include "mechanics/UnitManager.h"
#include "resource/AssetManager.h"
#include "resource/Sprite.h"
#include "resource/LanguageManager.h"
#include "render/GraphicRender.h"

Missile::Missile(const genie::Unit &data, const Unit::Ptr &sourceUnit, const MapPos &target, const Unit::Ptr &targetUnit) :
    Entity(Type::Missile, LanguageManager::getString(data.LanguageDLLName) + " (" + std::to_string(data.ID) + ")"),
    playerId(sourceUnit->playerId()),
    m_sourceUnit(sourceUnit),
    m_targetUnit(targetUnit),
    m_player(sourceUnit->player()),
    m_unitManager(sourceUnit->unitManager()),
    m_data(data),
    m_targetPosition(target)
{
    m_startingElevation = sourceUnit->position().z;
    m_attacks = sourceUnit->data()->Combat.Attacks;
    sourceUnit->activeMissiles++;
    DBG << "Firing at" << target;
    defaultGraphics = AssetManager::Inst()->getGraphic(data.StandingGraphic.first);
    m_renderer->setSprite(defaultGraphics);
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
    case DamageResources:
    case DamageTrees:
    case DamageTargetOnly:
        break;
    case DamageNearby:
        m_blastRadius = radius;
        break;
    default:
        m_blastType = DamageTargetOnly;
        break;
    }
}


bool Missile::update(Time time) noexcept
{
    if (isExploding()) {
        m_renderer->setCurrentFrame(m_renderer->currentFrame() + 1);
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
        DBG << "we hit the ground, we're at" << position().z << "ground at" << map->elevationAt(position());
        die();
        return false;
    }

    if (m_previousUpdateTime == 0) {
        Unit::Ptr sourceUnit = m_sourceUnit.lock();
        if (!sourceUnit) {
            WARN << "Source unit gone before we could start";
            die();
            return false;
        }

        m_distanceLeft = std::min(position().distance(m_targetPosition), sourceUnit->data()->Combat.MaxRange * Constants::TILE_SIZE);;
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
    if (movement != 0.f && m_zVelocity != 0.f) {
        const int nextFrame = std::round((0.5 + m_zVelocity / movement) * m_renderer->frameCount());
        m_renderer->setCurrentFrame(std::clamp(nextFrame, 0, m_renderer->frameCount()));
    } else {
        m_renderer->setCurrentFrame(0);
    }

    m_renderer->setAngle(position().toScreen().angleTo(newPos.toScreen()));

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
                    Unit::Ptr otherUnit = Unit::fromEntity(entity);
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

    if (!m_data.Missile.HitMode || m_distanceLeft <= 0) {
        die();
    }

    int playerId = player ? player->playerId : -1;
    for (Unit::Ptr &hitUnit : hitUnits) {
        if (m_blastType != DamageTrees && hitUnit->data()->Class == genie::Unit::Tree) {
            continue;
        }

        if (m_data.Missile.HitMode && hitUnit->playerId() == playerId) {
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

bool Missile::isExploding() const noexcept
{
    return !m_isFlying && m_renderer->currentFrame() < m_renderer->frameCount() - 1;
}

void Missile::die()
{
    m_isFlying = false;
    m_renderer->setSprite(m_data.DyingGraphic);

    Player::Ptr player = m_player.lock();
    if (player && m_data.DyingSound != -1) {
        AudioPlayer::instance().playSound(m_data.DyingSound, player->civilization.id());
    }
}
