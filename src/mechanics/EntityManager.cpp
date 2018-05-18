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
#include "resource/LanguageManager.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
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

bool EntityManager::init()
{

    m_moveTargetMarker = std::make_shared<MoveTargetMarker>();

    return true;
}

bool EntityManager::update(Time time)
{
    bool updated = false;

    for (EntityPtr entity : m_entities) {
        updated = entity->update(time) || updated;
    }

    updated = m_moveTargetMarker->update(time) || updated;

    return updated;
}

void EntityManager::render(std::shared_ptr<SfmlRenderTarget> renderTarget)
{
    if (m_outlineOverlay.getSize() != renderTarget->getSize()) {
        m_outlineOverlay.create(renderTarget->getSize().x, renderTarget->getSize().y);
    }

    m_outlineOverlay.clear(sf::Color::Transparent);

    for (EntityPtr entity : m_entities) {
        Unit::Ptr unit = Entity::asUnit(entity);
        if (!unit) {
            continue;
        }

        if (unit->data.Type < genie::Unit::BuildingType) {
            continue;
        }
        const ScreenPos unitPosition = renderTarget->camera()->absoluteScreenPos(entity->position);

        ScreenRect unitRect = unit->renderer().rect() + unitPosition;
        if (renderTarget->camera()->isVisible(unitRect)) {
            entity->renderer().drawOn(m_outlineOverlay, unitPosition);
        }


        for (const Entity::Annex &annex : unit->annexes) {
            const ScreenPos annexPosition = renderTarget->camera()->absoluteScreenPos(entity->position + annex.offset);
            ScreenRect annexRect = annex.entity->renderer().rect() + annexPosition;
            if (!renderTarget->camera()->isVisible(annexRect)) {
                continue;
            }

            annex.entity->renderer().drawOn(m_outlineOverlay, renderTarget->camera()->absoluteScreenPos(entity->position + annex.offset));
        }
    }

    for (const EntityPtr &entity : m_entities) {
        Unit::Ptr unit = Entity::asUnit(entity);
        if (!unit) {
            continue;
        }

        if (!renderTarget->camera()->isVisible(MapRect(unit->position.x, unit->position.y, 10, 10))) {
            continue;
        }

        if (m_selectedEntities.count(entity)) { // draw health indicator
            ScreenPos pos = renderTarget->camera()->absoluteScreenPos(entity->position);
            pos.x -= unit->data.CollisionSize.first * Map::TILE_SIZE_HORIZONTAL/2;
            pos.y -= unit->data.CollisionSize.second * Map::TILE_SIZE_VERTICAL/2;

            sf::RectangleShape rect;
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1);

            circle.setPosition(pos);
            circle.setRadius(unit->data.CollisionSize.first * Map::TILE_SIZE);
            const float ratio = unit->data.CollisionSize.second * Map::TILE_SIZE_VERTICAL / (unit->data.CollisionSize.first * Map::TILE_SIZE_HORIZONTAL);
            circle.setScale(1, ratio);
            renderTarget->draw(circle);

            pos = renderTarget->camera()->absoluteScreenPos(entity->position);
            pos.x -= Map::TILE_SIZE_HORIZONTAL / 8;
            pos.y -= Map::TILE_SIZE_VERTICAL;

            rect.setFillColor(sf::Color::Green);
            rect.setOutlineColor(sf::Color::Transparent);

            rect.setPosition(pos);
            rect.setSize(sf::Vector2f(Map::TILE_SIZE_HORIZONTAL / 4, 2));
            m_outlineOverlay.draw(rect);
        }

        if (unit->data.Type >= genie::Unit::BuildingType) {
            continue;
        }

        entity->renderer().drawOn(*renderTarget->renderTarget_, renderTarget->camera()->absoluteScreenPos(entity->position));

        ScreenPos pos = renderTarget->camera()->absoluteScreenPos(entity->position);
        entity->renderer().drawOutlineOn(m_outlineOverlay, pos);
    }

    m_outlineOverlay.display();
    renderTarget->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));

    m_moveTargetMarker->renderer().drawOn(*renderTarget->renderTarget_, renderTarget->camera()->absoluteScreenPos(m_moveTargetMarker->position));
}

void EntityManager::onRightClick(const MapPos &mapPos)
{
    if (m_selectedEntities.empty()) {
        return;
    }


    for (const EntityPtr &entity : m_selectedEntities) {
        if (entity->type == Entity::Type::Unit) {
            Entity::asUnit(entity)->setCurrentAction(act::MoveOnMap::moveUnitTo(entity, mapPos, m_map, this));
        }
    }

    m_moveTargetMarker->moveTo(mapPos);
}

void EntityManager::selectEntities(const MapRect &selectionRect)
{
    m_selectedEntities.clear();

    std::vector<Unit::Ptr> containedEntities;
    int8_t requiredInteraction = genie::Unit::ObjectInteraction;
    for (EntityPtr entity : m_entities) {
        if (!selectionRect.contains(entity->position)) {
            continue;
        }

        Unit::Ptr unit = Entity::asUnit(entity);
        if (!unit) {
            continue;
        }

        requiredInteraction = std::max(unit->data.InteractionMode, requiredInteraction);
        containedEntities.push_back(unit);
    }

    for (Unit::Ptr entity : containedEntities) {
        if (entity->data.InteractionMode < requiredInteraction) {
            continue;
        }

        std::cout << "Selected " << entity->readableName << " at " << entity->position << std::endl;
        m_selectedEntities.insert(entity);
    }
    if (m_selectedEntities.empty()) {
        std::cout << "Unable to find anything to select in " << selectionRect << std::endl;
    }
}

void EntityManager::setMap(MapPtr map)
{
    m_map = map;
}
