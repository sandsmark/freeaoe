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
    m_unitIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btnunit.shp"));
    if (!m_unitIconsSlp) {
        std::cerr << "Failed to load unit icons" << std::endl;
        return false;
    }

    // ico_bld1-4.shp looks identical, for some reason
    m_buildingIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("ico_bld2.shp"));
    if (!m_buildingIconsSlp) {
        std::cerr << "Failed to load building icons" << std::endl;
        return false;
    }

    m_actionIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btncmd.shp"));
    if (!m_actionIconsSlp) {
        std::cerr << "Failed to load action icons" << std::endl;
        return false;
    }

    m_researchIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btntech.shp"));
    if (!m_researchIconsSlp) {
        std::cerr << "Failed to load research icons" << std::endl;
        return false;
    }

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
        m_outlineOverlay.create(renderTarget->getSize().x, renderTarget->getSize().y, false);
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

        entity->renderer().drawOn(m_outlineOverlay, renderTarget->absoluteScreenPos(entity->position));

        for (const Entity::Annex &annex : unit->annexes) {
            annex.entity->renderer().drawOn(m_outlineOverlay, renderTarget->absoluteScreenPos(entity->position + annex.offset));
        }
    }

    for (const EntityPtr &entity : m_entities) {
        Unit::Ptr unit = Entity::asUnit(entity);
        if (!unit) {
            continue;
        }

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

        if (unit->data.Type >= genie::Unit::BuildingType) {
            continue;
        }

        entity->renderer().drawOn(*renderTarget->renderTarget_, renderTarget->absoluteScreenPos(entity->position));

        ScreenPos pos = renderTarget->absoluteScreenPos(entity->position);
        entity->renderer().drawOutlineOn(m_outlineOverlay, pos);
    }

    m_outlineOverlay.display();
    renderTarget->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));

    m_moveTargetMarker->renderer().drawOn(*renderTarget->renderTarget_, renderTarget->absoluteScreenPos(m_moveTargetMarker->position));
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

        m_selectedEntities.insert(entity);
    }

    updateButtons();
}

void EntityManager::setMap(MapPtr map)
{
    m_map = map;
}

const EntitySet &EntityManager::selected()
{
    return m_selectedEntities;
}

void EntityManager::updateButtons()
{
    currentButtons.clear();
    if (m_selectedEntities.empty()) {
        return;
    }

    Unit::Ptr unit = Entity::asUnit(*selected().begin());
    if (!unit) {
        return;
    }

    for (const genie::Unit *creatable : unit->creatableEntities()) {
        if (creatable->IconID >= m_unitIconsSlp->getFrameCount()) {
            std::cerr << "invalid icon id: " << creatable->IconID << std::endl;
            continue;
        }

        InterfaceButton button;
        if (unit->data.InterfaceKind == genie::Unit::CiviliansInterface) {
            button.tex.loadFromImage(res::Resource::convertFrameToImage(m_buildingIconsSlp->getFrame(creatable->IconID)));
        } else {
            button.tex.loadFromImage(res::Resource::convertFrameToImage(m_unitIconsSlp->getFrame(creatable->IconID)));
        }
        button.index = std::max(creatable->Creatable.ButtonID - 1, 0);
        button.interfacePage = creatable->InterfaceKind;
        std::cerr << button.index << " " << LanguageManager::getString(creatable->LanguageDLLName) << " " << LanguageManager::getString(creatable->LanguageDLLCreation) << std::endl;;
        std::cerr << int(creatable->InterfaceKind) << std::endl;
        std::cerr << int(unit->data.InterfaceKind) << std::endl;


        currentButtons.push_back(std::move(button));
    }
}
