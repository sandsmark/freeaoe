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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <unordered_set>
#include <core/Entity.h>
#include "Map.h"
class SfmlRenderTarget;

// IDEA: Class containing all entities, (adds, removes, updates them).
// Base class (EntitySpace?)
typedef std::unordered_set<EntityPtr> EntitySet;

class EntityManager
{

public:

    EntityManager();
    virtual ~EntityManager();

    void add(EntityPtr entity);

    bool update(Time time);
    void render(std::shared_ptr<SfmlRenderTarget> renderTarget);

    void onRightClick(const MapPos &mapPos);

    void selectEntities(const MapRect &selectionRect);
    void setMap(MapPtr map);

    const EntitySet &selected();

private:
    EntitySet m_entities;
    EntitySet m_selectedEntities;
    MapPtr m_map;
    sf::RenderTexture m_outlineOverlay;
};

#endif // ENTITYMANAGER_H
