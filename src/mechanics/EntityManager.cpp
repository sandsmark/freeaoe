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

#include "EntityManager.h"

#include "CompMapObject.h"
#include "CompUnitData.h"
#include "ActionMove.h"
#include "render/SfmlRenderTarget.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::add(EntityPtr entity)
{
    m_entities.insert(entity);
}

bool EntityManager::update(Time time)
{
    bool updated = false;

    for (EntityPtr entity : m_entities) {
        updated = entity->update(time) || updated;
    }

    return updated;
}

void EntityManager::render(std::shared_ptr<SfmlRenderTarget> renderTarget)
{
    if (m_outlineOverlay.getSize() != renderTarget->getSize()) {
        m_outlineOverlay.create(renderTarget->getSize().x, renderTarget->getSize().y, false);
    }

    m_outlineOverlay.clear(sf::Color::Transparent);

    for (EntityPtr entity : m_entities) {
        if (entity->data.Type < genie::Unit::BuildingType) {
            continue;
        }

        entity->renderer().drawOn(m_outlineOverlay, renderTarget->absoluteScreenPos(entity->position));

        for (const Entity::Annex &annex : entity->annexes) {
            annex.entity->renderer().drawOn(m_outlineOverlay, renderTarget->absoluteScreenPos(entity->position + annex.offset));
        }
    }

    for (const EntityPtr &entity : m_entities) {
        if (m_selectedEntities.count(entity)) { // draw health indicator
            ScreenPos pos = renderTarget->absoluteScreenPos(entity->position);
            pos.x -= Map::TILE_SIZE_HORIZONTAL / 8;
            pos.y -= Map::TILE_SIZE_VERTICAL;

            sf::RectangleShape rect;
            rect.setFillColor(sf::Color::Green);
            rect.setOutlineColor(sf::Color::Transparent);

            rect.setPosition(pos);
            rect.setSize(sf::Vector2f(Map::TILE_SIZE_HORIZONTAL / 4, 2));
            m_outlineOverlay.draw(rect);
        }

        if (entity->data.Type >= genie::Unit::BuildingType) {
            continue;
        }

        entity->renderer().drawOn(*renderTarget->renderTarget_, renderTarget->absoluteScreenPos(entity->position));

        ScreenPos pos = renderTarget->absoluteScreenPos(entity->position);
        entity->renderer().drawOutlineOn(m_outlineOverlay, pos);
    }

    m_outlineOverlay.display();
    renderTarget->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));
}

void EntityManager::onRightClick(const MapPos &mapPos)
{
    if (m_selectedEntities.empty()) {
        return;
    }


    for (const EntityPtr &entity : m_selectedEntities) {
        if (entity->type == Entity::Type::Unit) {
            Entity::asUnit(entity)->setCurrentAction(act::MoveOnMap::moveUnitTo(entity, mapPos, m_map));
        }
    }
}

void EntityManager::selectEntities(const MapRect &selectionRect)
{
    m_selectedEntities.clear();

    std::vector<EntityPtr> containedEntities;
    int8_t requiredInteraction = genie::Unit::ObjectInteraction;
    for (EntityPtr entity : m_entities) {

        if (!selectionRect.contains(entity->position)) {
            continue;
        }

        requiredInteraction = std::max(entity->data.InteractionMode, requiredInteraction);
        containedEntities.push_back(entity);
    }

    for (EntityPtr entity : containedEntities) {
        if (entity->data.InteractionMode < requiredInteraction) {
            continue;
        }

        m_selectedEntities.insert(entity);
    }
}

void EntityManager::setMap(MapPtr map)
{
    m_map = map;
}

const EntitySet &EntityManager::selected()
{
    return m_selectedEntities;
}
