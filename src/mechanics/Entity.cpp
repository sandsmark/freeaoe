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
#include "core/Constants.h"
#include "core/Types.h"
#include "Map.h"
#include "render/GraphicRender.h"

#include <cstddef>
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

void Entity::setMap(const MapPtr &newMap) noexcept
{
    const int tileX = m_position.x / Constants::TILE_SIZE;
    const int tileY = m_position.y / Constants::TILE_SIZE;

    MapPtr oldMap = m_map.lock();
    if (oldMap) {
        oldMap->removeEntityAt(tileX, tileY, id);

        if (newMap) { // todo assume we have a valid position
            newMap->addEntityAt(tileX, tileY, shared_from_this(), foundationTerrain());
        }
    }

    m_map = newMap;
}

MapPtr Entity::map() const noexcept
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

    if (!isUnit() && !isMissile() && !isDecayingEntity() && !isDoppleganger()) {
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
    map->addEntityAt(newTileX, newTileY, shared_from_this(), foundationTerrain());
}

MoveTargetMarker::MoveTargetMarker()
{
    renderer = std::make_unique<GraphicRender>();
    renderer->setSprite(AgeOfEmpires2);

    renderer->setCurrentFrame(renderer->frameCount() - 1); // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos) noexcept
{
    m_position = pos;
    renderer->setCurrentFrame(0);
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time) noexcept
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = renderer->update(time, true); // just assume we're always visible, doesn't matter much, todo I guess

    if (renderer->currentFrame() >= renderer->frameCount() - 1) {
        m_isRunning = false;
    }

    return updated;
}

StaticEntity::StaticEntity(const Type type_, const std::string &name, const Size size) : Entity(type_, name),
    m_tileSize(size)
{
}

DecayingEntity::DecayingEntity(const int graphicId, float decayTime, const Size size) :
    StaticEntity(Type::Decaying, "Eye Candy Things", size),
    m_decayTimeLeft(decayTime)
{
    m_renderer->setSprite(graphicId);
}

bool DecayingEntity::update(Time time) noexcept
{
    if (!shouldBeRemoved()) {
        return false;
    }

    if (!std::isinf(m_decayTimeLeft)) {
        m_decayTimeLeft -= (time - m_prevTime) * 0.0015;
        m_prevTime = time;
    }

    return Entity::update(time);
}

bool DecayingEntity::shouldBeRemoved() const noexcept
{
    return m_decayTimeLeft <= 0 && m_renderer->currentFrame() >= m_renderer->frameCount() - 1;
}
