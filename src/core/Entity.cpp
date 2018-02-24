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
#include <genie/dat/Unit.h>

Entity::Entity(const genie::Unit &data_, int playerId_, const Entity::Type type_) :
    type(type_),
    data(data_),
    playerId(playerId_),
    defaultGraphics(ResourceManager::Inst()->getGraphic(data.StandingGraphic.first))
{
    m_graphics.setGraphic(defaultGraphics);
}

Entity::~Entity()
{
}

bool Entity::update(Time time)
{
    bool updated = false;

    updated = m_graphics.update(time) || updated;

    for (Annex &annex : annexes) {
        updated = annex.entity->update(time) || updated;
    }

    return updated;
}

std::string Entity::readableName()
{
    return LanguageManager::getString(data.LanguageDLLName);
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

Unit::Unit(const genie::Unit &data_, int playerId_) :
    Entity(data_, playerId_, Type::Unit)
{
    movingGraphics = ResourceManager::Inst()->getGraphic(data.Moving.WalkingGraphic);
}

bool Unit::update(Time time)
{
    bool updated = false;

    updated = m_graphics.update(time) || updated;

    if (currentAction) {
        updated = currentAction->update(time) || updated;
    }

    return updated || Entity::update(time);
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
