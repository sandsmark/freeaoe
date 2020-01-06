/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Entity.h"
#include "Unit.h"
#include "Missile.h"
#include "Building.h"
#include "core/Constants.h"
#include "core/Types.h"
#include "Map.h"
#include "render/GraphicRender.h"

#include <stddef.h>
#include <cmath>
#include <memory>
#include <string>

static size_t s_entityCount = 0;

Entity::Entity(const Entity::Type type_, const std::string &name) :
    id(s_entityCount++),
    debugName(name + " #" + std::to_string(id)),
    m_type(type_)
{
    m_renderer = std::make_unique<GraphicRender>();
}

Entity::~Entity()
{
    MapPtr map = m_map.lock();

    if (map) {
        int tileX = m_position.x / Constants::TILE_SIZE;
        int tileY = m_position.y / Constants::TILE_SIZE;
        map->removeEntityAt(tileX, tileY, id);
    }
}

bool Entity::update(Time time) noexcept
{
    bool updated = false;

    updated = m_renderer->update(time, isVisible) || updated;

    return updated && isVisible;
}

std::shared_ptr<Unit> Entity::asUnit(const EntityPtr &entity) noexcept {
    if (!entity) {
        return nullptr;
    }
    if (!entity->isUnit()) {
        return nullptr;
    }
    return std::static_pointer_cast<Unit>(entity);
}

std::shared_ptr<Missile> Entity::asMissile(const std::shared_ptr<Entity> &entity) noexcept
{
    if (!entity) {
        return nullptr;
    }

    if (!entity->isMissile()) {
        return nullptr;
    }

    return std::static_pointer_cast<Missile>(entity);
}

void Entity::setMap(const MapPtr &newMap) noexcept
{
    const int tileX = m_position.x / Constants::TILE_SIZE;
    const int tileY = m_position.y / Constants::TILE_SIZE;

    MapPtr oldMap = m_map.lock();
    if (oldMap) {
        oldMap->removeEntityAt(tileX, tileY, id);
    }

    m_map = newMap;
    if (newMap) {
        newMap->addEntityAt(tileX, tileY, shared_from_this());
    }
}

MapPtr Entity::map() const noexcept
{
    return m_map.lock();
}

void Entity::setPosition(const MapPos &pos, const bool initial) noexcept
{
    const int oldTileX = m_position.x / Constants::TILE_SIZE;
    const int oldTileY = m_position.y / Constants::TILE_SIZE;
    const int newTileX = pos.x / Constants::TILE_SIZE;
    const int newTileY = pos.y / Constants::TILE_SIZE;

    m_position = pos;

    if (!isUnit() && !isMissile() && !isDecayingEntity()) {
        return;
    }
    if (newTileX == oldTileX && newTileY == oldTileY) {
        return;
    }


    MapPtr map = m_map.lock();
    if (!map) {
        return;
    }
    if (!initial) {
        map->removeEntityAt(oldTileX, oldTileY, id);
    }
    map->addEntityAt(newTileX, newTileY, shared_from_this());
}

MoveTargetMarker::MoveTargetMarker() :
    Entity(Type::MoveTargetMarker, "Move target marker")
{
    m_renderer->setGraphic(2961);

    m_renderer->setCurrentFrame(m_renderer->frameCount() - 1); // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos) noexcept
{
    m_position = pos;
    m_renderer->setCurrentFrame(0);
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time) noexcept
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = Entity::update(time);

    if (m_renderer->currentFrame() >= m_renderer->frameCount() - 1) {
        m_isRunning = false;
    }

    return updated;
}

DecayingEntity::DecayingEntity(const int graphicId, float decayTime) :
    Entity(Type::Decaying, "Eye Candy Things"),
    m_decayTimeLeft(decayTime)
{
    m_renderer->setGraphic(graphicId);
}

bool DecayingEntity::update(Time time) noexcept
{
    if (!decaying()) {
        return false;
    }

    if (!std::isinf(m_decayTimeLeft)) {
        m_decayTimeLeft -= (time - m_prevTime) * 0.0015;
        m_prevTime = time;
    }

    return Entity::update(time);
}

bool DecayingEntity::decaying() const noexcept
{
    return m_decayTimeLeft > 0 || m_renderer->currentFrame() < m_renderer->frameCount() - 1;
}
