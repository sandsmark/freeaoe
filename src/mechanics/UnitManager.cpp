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

#include "UnitManager.h"

#include "CompMapObject.h"
#include "CompUnitData.h"
#include "ActionMove.h"
#include "ActionBuild.h"
#include "render/SfmlRenderTarget.h"
#include "resource/LanguageManager.h"
#include "global/Constants.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

void UnitManager::add(Unit::Ptr unit)
{
    m_units.insert(unit);
}

bool UnitManager::init()
{
    m_moveTargetMarker = std::make_shared<MoveTargetMarker>();

    return true;
}

bool UnitManager::update(Time time)
{
    bool updated = false;

    for (Unit::Ptr unit : m_units) {
        updated = unit->update(time) || updated;
    }

    updated = m_moveTargetMarker->update(time) || updated;

    return updated;
}

void UnitManager::render(std::shared_ptr<SfmlRenderTarget> renderTarget)
{
    CameraPtr camera = renderTarget->camera();

    if (camera->targetPosition() != m_previousCameraPos || m_outlineOverlay.getSize().x == 0) {
        updateVisibility(camera);
        m_previousCameraPos = camera->targetPosition();
    }

    if (Size(m_outlineOverlay.getSize()) != renderTarget->getSize()) {
        m_outlineOverlay.create(renderTarget->getSize().width, renderTarget->getSize().height);
    }

    m_outlineOverlay.clear(sf::Color::Transparent);

    for (Unit::Ptr unit : m_units) {
        if (!(unit->data.OcclusionMode & genie::Unit::OccludeOthers)) {
            continue;
        }
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position);

        for (const Unit::Annex &annex : unit->annexes) {
            if (!annex.unit->isVisible) {
                continue;
            }
            annex.unit->renderer().render(m_outlineOverlay,
                                          renderTarget->camera()->absoluteScreenPos(unit->position + annex.offset),
                                          comp::RenderType::Base
                                          );
        }
        if (unit->isVisible) {
            unit->renderer().render(m_outlineOverlay, unitPosition, comp::RenderType::Base);
        }
    }

    for (const Unit::Ptr &unit : m_units) {
        if (!unit->isVisible) {
            continue;
        }

        if (m_selectedUnits.count(unit)) { // draw health indicator
            sf::RectangleShape rect;
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1);

            double width = unit->data.OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL;
            double height =  unit->data.OutlineSize.y * Constants::TILE_SIZE_VERTICAL;

            if (unit->data.ObstructionType == genie::Unit::UnitObstruction) {
                width /= 2.;
                height /= 2.;
            } else {
                circle.setPointCount(4);
            }

            ScreenPos pos = camera->absoluteScreenPos(unit->position);

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setRadius(width);
            circle.setScale(1, height / width);
            renderTarget->draw(circle);

            circle.setPosition(pos.x - width, pos.y - height + 1);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            pos.x -= Constants::TILE_SIZE_HORIZONTAL / 8;
            pos.y -= height + Constants::TILE_SIZE_HEIGHT * unit->data.HPBarHeight;

            rect.setOutlineColor(sf::Color::Transparent);
            rect.setPosition(pos);

            if (unit->creationProgress() < 1.) {
                rect.setFillColor(sf::Color::Red);
                rect.setSize(sf::Vector2f(Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                m_outlineOverlay.draw(rect);
            }

            rect.setFillColor(sf::Color::Green);
            rect.setSize(sf::Vector2f(unit->creationProgress() * Constants::TILE_SIZE_HORIZONTAL / 4., 2));
            m_outlineOverlay.draw(rect);
        }

        if (!(unit->data.OcclusionMode & genie::Unit::ShowOutline)) {
            continue;
        }

        unit->renderer().render(*renderTarget->renderTarget_,
                                renderTarget->camera()->absoluteScreenPos(unit->position),
                                comp::RenderType::Base);

        const ScreenPos pos = renderTarget->camera()->absoluteScreenPos(unit->position);
        unit->renderer().render(m_outlineOverlay, pos, comp::RenderType::Outline);
    }

    m_outlineOverlay.display();
    renderTarget->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));

    m_moveTargetMarker->renderer().render(*renderTarget->renderTarget_,
                                          renderTarget->camera()->absoluteScreenPos(m_moveTargetMarker->position),
                                          comp::RenderType::Base);

    if (m_buildingToPlace) {
        m_buildingToPlace->renderer().render(*renderTarget->renderTarget_,
                                             renderTarget->camera()->absoluteScreenPos(m_buildingToPlace->position),
                                             comp::RenderType::ConstructAvailable);
    }
}

void UnitManager::onLeftClick(const MapPos &/*mapPos*/)
{
    if (m_buildingToPlace) {
        for (const Unit::Ptr &unit : m_selectedUnits) {
            unit->setCurrentAction(act::MoveOnMap::moveUnitTo(unit, m_buildingToPlace->position, m_map, this));
            unit->queueAction(std::make_shared<act::ActionBuild>(unit, m_buildingToPlace));
        }

        m_buildingToPlace->isVisible = true;
        m_units.insert(m_buildingToPlace);
        m_buildingToPlace->setCreationProgress(0);

        m_buildingToPlace.reset();
    }
}

void UnitManager::onRightClick(const MapPos &mapPos)
{
    if (m_selectedUnits.empty()) {
        return;
    }

    for (const Unit::Ptr &unit : m_selectedUnits) {
        unit->setCurrentAction(act::MoveOnMap::moveUnitTo(unit, mapPos, m_map, this));
    }

    m_moveTargetMarker->moveTo(mapPos);
}

void UnitManager::onMouseMove(const MapPos &mapPos)
{
    if (m_buildingToPlace) {
        const int x = std::round(mapPos.x / Constants::TILE_SIZE);
        const int y = std::round(mapPos.y / Constants::TILE_SIZE);
        m_buildingToPlace->position.x = x * Constants::TILE_SIZE;
        m_buildingToPlace->position.y = y * Constants::TILE_SIZE;
    }
}

void UnitManager::selectUnits(const ScreenRect &selectionRect, const CameraPtr &camera)
{
    m_selectedUnits.clear();
    m_currentActions.clear();

    std::vector<Unit::Ptr> containedUnits;
    int8_t requiredInteraction = genie::Unit::ObjectInteraction;
    for (Unit::Ptr unit : m_units) {
        if (!selectionRect.overlaps(unit->rect() + camera->absoluteScreenPos(unit->position))) {
            continue;
        }

        requiredInteraction = std::max(unit->data.InteractionMode, requiredInteraction);
        containedUnits.push_back(unit);
    }

    if (!containedUnits.empty()) {
        m_currentActions = containedUnits[0]->availableActions();
    }

    for (Unit::Ptr unit : containedUnits) {
        if (unit->data.InteractionMode < requiredInteraction) {
            continue;
        }

        DBG << "Selected" << unit->readableName << "at" << unit->position << unit->renderer().angle() << unit->renderer().graphic_->data_.SLP;
        m_selectedUnits.insert(unit);

        // stl is shit
        for (std::unordered_set<const genie::Task*>::iterator it = m_currentActions.begin(); it != m_currentActions.end();) {
            if (unit->availableActions().count(*it) == 0) {
                it = m_currentActions.erase(it);
            } else {
                it++;
            }
        }
    }

    if (m_selectedUnits.empty()) {
        DBG << "Unable to find anything to select in " << selectionRect;
    }
}

void UnitManager::setMap(MapPtr map)
{
    m_map = map;
}

void UnitManager::placeBuilding(const Unit::Ptr &unit)
{
    m_buildingToPlace = unit;
}

Unit::Ptr UnitManager::unitAt(const ScreenPos &pos, const CameraPtr &camera) const
{
    for (Unit::Ptr unit : m_units) {
        if (!unit->isVisible) {
            continue;
        }

        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position);
        const ScreenRect unitRect = unit->renderer().rect() + unitPosition;
        if (unitRect.contains(pos)) {
            return unit;
        }
    }

    return nullptr;
}

const genie::Task *UnitManager::defaultActionAt(const ScreenPos &pos, const CameraPtr &camera)
{
    Unit::Ptr target = unitAt(pos, camera);
    if (!target) {
        return nullptr;
    }

    // One of the selected themselves
    if (m_selectedUnits.count(target)) {
        return nullptr;
    }

    for (const genie::Task *action : availableActions()) {
        if (action->ActionType == genie::Task::Combat) {
            return action;
        }
    }

    return nullptr;
}

void UnitManager::updateVisibility(const CameraPtr &camera)
{
    for (Unit::Ptr unit : m_units) {
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position);
        const ScreenRect unitRect = unit->renderer().rect() + unitPosition;
        unit->isVisible = camera->isVisible(unitRect);

        for (Unit::Annex &annex : unit->annexes) {
            const ScreenPos annexPosition = camera->absoluteScreenPos(unit->position + annex.offset);
            ScreenRect annexRect = annex.unit->renderer().rect() + annexPosition;
            annex.unit->isVisible = camera->isVisible(annexRect);
        }
    }
}
