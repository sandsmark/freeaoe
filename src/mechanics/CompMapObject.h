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

#include <memory>

#include "core/IComponent.h"

#include "global/Types.h"

#include "core/Entity.h"
#include "core/IAction.h"

const std::string MAP_OBJECT("map_object");

// TODO: Rename to MapUnit?
/// Component that enables an entity to be placed on a map.
class MapObject : public IComponent
{
public:
    MapObject();
    virtual ~MapObject();

    bool update(Time time) override;

    void setPos(const MapPos pos);

    MapPos getPos(void) const;
    MapRect getRect();
    void setRect(const MapRect &rect);

    float angle_ = 0.f;
    bool moving_ = false;

private:
    MapRect rect_;
};

typedef std::shared_ptr<MapObject> MapObjectPtr;

    class PlaceMapObject : public IAction
    {
    public:
        PlaceMapObject(EntityPtr entity, MapPos pos) :
            IAction(IAction::Type::PlaceOnMap),
            target_(entity), new_pos_(pos)
        {
        }

        virtual bool update(Time /*time*/)
        {
            target_->position = new_pos_;
            return true;
        }

    private:
        EntityPtr target_;
        MapPos new_pos_;
    };

