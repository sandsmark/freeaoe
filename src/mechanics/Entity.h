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

#pragma once

#include "core/Types.h"

#include "render/GraphicRender.h"
#include "core/SignalEmitter.h"

namespace genie {
class Unit;
}

class Map;
class GraphicRender;

struct Unit;
struct Entity;
struct MoveTargetMarker;
struct Missile;

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Entity> EntityPtr;

struct Entity: std::enable_shared_from_this<Entity>, SignalEmitter<Entity>
{
    const size_t id;

    Entity() = delete;

    virtual ~Entity();

    virtual bool update(Time time);


    virtual GraphicRender &renderer() { return m_renderer; }

    static std::shared_ptr<Unit> asUnit(const EntityPtr &entity);
    static std::shared_ptr<Unit> asUnit(const std::weak_ptr<Entity> &entity);
    static std::shared_ptr<Missile> asMissile(const std::shared_ptr<Entity> &entity);

    const std::string debugName;

    bool isVisible = false;

    MapPtr map() const;
    const MapPos &position() const { return m_position; }
    virtual void setPosition(const MapPos &pos);

    bool isUnit() const { return m_type >= Type::Unit; }
    bool isBuilding() const { return m_type >= Type::Building; }
    bool isMissile() const { return m_type == Type::Missile; }
    bool isCorpse() const { return m_type == Type::Corpse; }

protected:
    enum class Type {
        None,
        MoveTargetMarker,
        Corpse,
        Missile,
        Unit,
        Building,
    };
    Entity(const Type type_, const std::string &name, const MapPtr &map_);

    GraphicRender m_renderer;
    GraphicPtr defaultGraphics;
    std::weak_ptr<Map> m_map;

private:
    const Type m_type = Type::None;

    friend struct MoveTargetMarker;
    MapPos m_position;
};

struct MoveTargetMarker : public Entity
{
    typedef std::shared_ptr<MoveTargetMarker> Ptr;

    MoveTargetMarker(const MapPtr &map);

    void moveTo(const MapPos &pos);

    bool update(Time time) override;

private:
    bool m_isRunning = false;
};

struct Corpse : public Entity
{
    typedef std::shared_ptr<Corpse> Ptr;

    Corpse(const MapPtr &map, const int corpseGraphic);

    bool update(Time time) override;

    bool decaying() const { return m_renderer.currentFrame() < m_renderer.frameCount() - 1; }
};
