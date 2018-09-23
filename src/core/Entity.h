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

#include "render/GraphicRender.h"

namespace genie {
class Unit;
}

class Map;
class GraphicRender;

struct Unit;
struct Entity;
struct MoveTargetMarker;

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Entity> EntityPtr;

struct Entity: std::enable_shared_from_this<Entity>
{
    const size_t id;

    enum class Type {
        None,
        Unit,
        MoveTargetMarker
    };
    const Type type = Type::None;

    Entity() = delete;

    virtual ~Entity();

    virtual bool update(Time time);


    virtual GraphicRender &renderer() { return m_renderer; }

    static std::shared_ptr<Unit> asUnit(const EntityPtr &entity);
    static std::shared_ptr<Unit> asUnit(const std::weak_ptr<Entity> &entity);

    const std::string debugName;

    bool isVisible = false;

    const MapPos &position() const { return m_position; }
    void setPosition(const MapPos &pos);

protected:
    Entity(const Type type_, const std::string &name, const MapPtr &map_);

    GraphicRender m_renderer;
    GraphicPtr defaultGraphics;
    std::weak_ptr<Map> m_map;

private:
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
