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

#include "core/Constants.h"
#include "Entity.h"
#include "render/GraphicRender.h"
#include "mechanics/Map.h"
#include "mechanics/Unit.h"
#include "mechanics/Missile.h"
#include "genie/dat/Unit.h"

static size_t s_entityCount = 0;

Entity::Entity(const Entity::Type type_, const std::string &name) :
    id(s_entityCount++),
    debugName(name),
    m_type(type_)
{
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

bool Entity::update(Time time)
{
    bool updated = false;

    updated = (m_renderer.update(time) && isVisible) || updated;

    return updated && isVisible;
}

std::shared_ptr<Unit> Entity::asUnit(const EntityPtr &entity)
{
    if (!entity) {
        return nullptr;
    }

    if (!entity->isUnit()) {
        return nullptr;
    }

    return std::static_pointer_cast<Unit>(entity);
}

std::shared_ptr<Unit> Entity::asUnit(const std::weak_ptr<Entity> &entity)
{
    return asUnit(entity.lock());
}

std::shared_ptr<Missile> Entity::asMissile(const std::shared_ptr<Entity> &entity)
{
    if (!entity) {
        return nullptr;
    }

    if (!entity->isMissile()) {
        return nullptr;
    }

    return std::static_pointer_cast<Missile>(entity);
}

void Entity::setMap(const MapPtr &newMap)
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

MapPtr Entity::map() const
{
    return m_map.lock();
}

void Entity::setPosition(const MapPos &pos, const bool initial)
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
    m_renderer.setGraphic(2961);

    m_renderer.setCurrentFrame(m_renderer.frameCount() - 1); // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos)
{
    m_position = pos;
    m_renderer.setCurrentFrame(0);
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time)
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = Entity::update(time);

    if (m_renderer.currentFrame() >= m_renderer.frameCount() - 1) {
        m_isRunning = false;
    }

    return updated;
}

DecayingEntity::DecayingEntity(const int graphicId, float decayTime) :
    Entity(Type::Decaying, "Eye Candy Things"),
    m_decayTimeLeft(decayTime)
{
    m_renderer.setGraphic(graphicId);
}

bool DecayingEntity::update(Time time)
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
