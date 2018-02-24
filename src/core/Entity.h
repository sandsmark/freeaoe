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

#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include "Utility.h"
#include "render/GraphicRender.h"

#include "IComponent.h"
#include "IAction.h"

namespace genie {
class Unit;
}

struct Unit;
struct Entity;

namespace comp {
class GraphicRender;
}

typedef std::shared_ptr<Entity> EntityPtr;

struct Entity
{
public:
    enum class Type {
        None,
        Unit
    };
    const Type type = Type::None;

    struct Annex {
        EntityPtr entity;
        MapPos offset;
    };

    Entity() = delete;

    const genie::Unit &data;
    int playerId;

    std::string readableName();

    virtual ~Entity();

    virtual bool update(Time time);

    MapPos position;

    comp::GraphicRender &renderer() { return m_graphics; }

    static std::shared_ptr<Unit> asUnit(EntityPtr entity);

    std::vector<Annex> annexes;

protected:
    Entity(const genie::Unit &data_, int playerId_, const Type type_);

    comp::GraphicRender m_graphics;

    res::GraphicPtr defaultGraphics;
};

struct Unit : public Entity
{
    Unit() = delete;

    Unit(const genie::Unit &data_, int playerId);

    bool selected = false;

    void setAngle(const float angle);
    void setCurrentAction(ActionPtr action);
    void removeAction(IAction *action);

    bool update(Time time) override;

protected:
    res::GraphicPtr movingGraphics;
    ActionPtr currentAction;
};
typedef std::shared_ptr<Unit> UnitPtr;


#endif // ENTITY_H
