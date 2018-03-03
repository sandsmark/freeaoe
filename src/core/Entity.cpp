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
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "render/GraphicRender.h"
#include "mechanics/Civilization.h"
#include <genie/dat/Unit.h>

Entity::Entity(const Entity::Type type_, const std::string &name) :
    type(type_),
    readableName(name)
{
}

Entity::~Entity()
{
}

bool Entity::update(Time time)
{
    bool updated = false;

    updated = m_graphics.update(time) || updated;

    return updated;
}

std::shared_ptr<Unit> Entity::asUnit(EntityPtr entity)
{
    if (!entity) {
        return nullptr;
    }

    if (entity->type != Type::Unit) {
        return nullptr;
    }
    return std::static_pointer_cast<Unit>(entity);
}

Unit::Unit(const genie::Unit &data_, int playerId_, std::shared_ptr<Civilization> civilization) :
    Entity(Type::Unit, LanguageManager::getString(data_.LanguageDLLName) + " (" + std::to_string(data_.ID) + ")"),
    data(data_),
    playerId(playerId_),
    m_civilization(civilization)
{
    defaultGraphics = ResourceManager::Inst()->getGraphic(data.StandingGraphic.first),
    movingGraphics = ResourceManager::Inst()->getGraphic(data.Moving.WalkingGraphic);
    if (!defaultGraphics) {
        std::cerr << "Failed to load default graphics" << std::endl;
    }

    m_graphics.setGraphic(defaultGraphics);
}

bool Unit::update(Time time)
{
    bool updated = false;

    for (Annex &annex : annexes) {
        updated = annex.entity->update(time) || updated;
    }

    if (currentAction) {
        updated = currentAction->update(time) || updated;
    }

    return Entity::update(time) || updated;
}

const std::vector<const genie::Unit *> Unit::creatableEntities()
{
    return m_civilization->creatableUnits(data.ID);
}

void Unit::setAngle(const float angle)
{
    m_graphics.angle = angle;
}

void Unit::setCurrentAction(ActionPtr action)
{
    currentAction = action;

    if (!action) {
        return;
    }

    if (action->type == IAction::Type::Move) {
        m_graphics.setGraphic(movingGraphics);
    } else {
        m_graphics.setGraphic(defaultGraphics);
    }
}

void Unit::removeAction(IAction *action)
{
    if (currentAction.get() == action) {
        currentAction.reset();
        m_graphics.setGraphic(defaultGraphics);
    }
}

MoveTargetMarker::MoveTargetMarker() :
    Entity(Type::MoveTargetMarker, "Move target marker")
{
    m_graphics.setGraphic(ResourceManager::Inst()->getGraphic(2961));

    m_graphics.current_frame_ = m_graphics.graphic_->data_.FrameCount - 1; // don't play immediately
}

void MoveTargetMarker::moveTo(const MapPos &pos)
{
    position = pos;
    m_graphics.current_frame_ = 0;
    m_isRunning = true;
}

bool MoveTargetMarker::update(Time time)
{
    if (!m_isRunning) {
        return false;
    }

    bool updated = Entity::update(time);

    if (m_graphics.current_frame_ >= m_graphics.graphic_->data_.FrameCount - 1) {
        m_isRunning = false;
    }

    return updated;
}
