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

#include <iostream>

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::add(EntityPtr entity)
{
    entities_.push_back(entity);
}

bool EntityManager::update(Time time)
{
    bool updated = false;
    for (EntityVector::iterator it = entities_.begin(); it != entities_.end();
         it++) {
        updated = (*it)->update(time) || updated;
    }

    return updated;
}

void EntityManager::onRightClick(const MapPos &mapPos)
{
    if (m_selectedEntities.empty()) {
        return;
    }


    for (EntityPtr entity : m_selectedEntities) {
        act::MoveOnMap::moveUnitTo(entity, mapPos, m_map);
    }

}

void EntityManager::selectEntities(const MapRect &selectionRect)
{
    for (EntityPtr entity : m_selectedEntities) {
        entity->selected = false;
    }

    m_selectedEntities.clear();

    for (EntityPtr entity : entities_) {
        comp::MapObjectPtr mapObject = entity->getComponent<comp::MapObject>(comp::MAP_OBJECT);
        genie::Unit gunit = entity->getComponent<comp::UnitData>(comp::UNIT_DATA)->getData();
        if (gunit.Type >= genie::UT_Building) {
            continue;
        }

        if (selectionRect.contains(mapObject->getPos())) {
            m_selectedEntities.push_back(entity);
            entity->selected = true;
        }
    }
}

void EntityManager::setMap(MapPtr map)
{
    m_map = map;
}
