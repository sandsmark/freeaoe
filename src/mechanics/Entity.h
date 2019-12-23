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

#include "core/SignalEmitter.h"
#include "core/Types.h"

#include <memory>

namespace genie {
class Unit;
}

class Map;

struct Unit;
struct Entity;
struct MoveTargetMarker;
struct Missile;
class GraphicRender;
class Graphic;

typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::shared_ptr<Graphic> GraphicPtr;

/// The most basic class thing, has a position on a map and can be rendered
struct Entity : std::enable_shared_from_this<Entity>, SignalEmitter<Entity>
{
    const size_t id;
    int32_t spawnId = -1;

    Entity() = delete;

    virtual ~Entity();

    virtual bool update(Time time) noexcept;

    virtual GraphicRender &renderer() noexcept { return *m_renderer; }

    static std::shared_ptr<Unit> asUnit(const EntityPtr &entity) noexcept;

    static inline std::shared_ptr<Unit> asUnit(const std::weak_ptr<Entity> &entity) noexcept {
        return asUnit(entity.lock());
    }

    static std::shared_ptr<Missile> asMissile(const std::shared_ptr<Entity> &entity) noexcept;

    const std::string debugName;

    bool isVisible = false;

    virtual void setMap(const MapPtr &newMap) noexcept;
    MapPtr map() const noexcept;
    inline const MapPos &position() const noexcept { return m_position; }
    virtual void setPosition(const MapPos &pos, const bool initial = false) noexcept;

    inline bool isUnit() const noexcept { return m_type >= Type::Unit; }
    inline bool isBuilding() const noexcept { return m_type >= Type::Building; }
    inline bool isMissile() const noexcept { return m_type == Type::Missile; }
    inline bool isDecayingEntity() const noexcept { return m_type == Type::Decaying; }
    inline bool isDoppleganger() const noexcept { return m_type == Type::Doppleganger; }

protected:
    enum class Type {
        None,
        MoveTargetMarker,
        Decaying,
        Doppleganger, // units that we have seen, but have lost vision of (typically buildings)
        Missile,
        Unit,
        Building,
    };
    Entity(const Type type_, const std::string &name);

    std::unique_ptr<GraphicRender> m_renderer;
    GraphicPtr defaultGraphics;
    std::weak_ptr<Map> m_map;

private:
    const Type m_type = Type::None;

    friend struct MoveTargetMarker;
    MapPos m_position;
};



struct MoveTargetMarker : public Entity
{
    typedef std::unique_ptr<MoveTargetMarker> Ptr;

    MoveTargetMarker();

    void moveTo(const MapPos &pos) noexcept;

    bool update(Time time) noexcept override;

private:
    bool m_isRunning = false;
};

/// Dumb name, but is corpses and smoke trails and stuff
struct DecayingEntity : public Entity
{
    typedef std::shared_ptr<DecayingEntity> Ptr;

    DecayingEntity(const int graphicId, float decayTime);

    bool update(Time time) noexcept override;

    bool decaying() const noexcept;

private:
    float m_decayTimeLeft = 0.f;
    Time m_prevTime = 0;
};
