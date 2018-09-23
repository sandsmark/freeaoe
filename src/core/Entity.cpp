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

#include "global/Constants.h"
#include "Entity.h"
#include "render/GraphicRender.h"
#include "mechanics/Map.h"
#include "mechanics/Unit.h"

static size_t s_entityCount = 0;

Entity::Entity(const Entity::Type type_, const std::string &name, const MapPtr &map) :
    id(s_entityCount++),
    type(type_),
    debugName(name),
    m_map(map)
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

    updated = m_renderer.update(time) || updated;

    return updated && isVisible;
}

std::shared_ptr<Unit> Entity::asUnit(const EntityPtr &entity)
{
    if (!entity) {
        return nullptr;
    }

    if (entity->type != Type::Unit) {
        return nullptr;
    }
    return std::static_pointer_cast<Unit>(entity);
}

std::shared_ptr<Unit> Entity::asUnit(const std::weak_ptr<Entity> &entity)
{
    return asUnit(entity.lock());
}

void Entity::setPosition(const MapPos &pos)
{
    MapPtr map = m_map.lock();

    if (!map) {
        WARN << "No map";
        return;
    }

    int oldTileX = m_position.x / Constants::TILE_SIZE;
    int oldTileY = m_position.y / Constants::TILE_SIZE;
    int newTileX = pos.x / Constants::TILE_SIZE;
    int newTileY = pos.y / Constants::TILE_SIZE;

    m_position = pos;
    if (newTileX == oldTileX && newTileY == oldTileY) {
        return;
    }

    map->removeEntityAt(oldTileX, oldTileY, id);
    map->addEntityAt(newTileX, newTileY, shared_from_this());
}

MoveTargetMarker::MoveTargetMarker(const MapPtr &map) :
    Entity(Type::MoveTargetMarker, "Move target marker", map)
{
    m_renderer.setGraphic(AssetManager::Inst()->getGraphic(2961));

    m_renderer.currentFrame = m_renderer.frameCount() - 1; // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos)
{
    m_position = pos;
    m_renderer.currentFrame = 0;
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time)
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = Entity::update(time);

    if (m_renderer.currentFrame >= m_renderer.frameCount() - 1) {
        m_isRunning = false;
    }

    return updated;
}
