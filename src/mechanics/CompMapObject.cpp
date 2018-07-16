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

#include "CompMapObject.h"

namespace comp {

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

bool MapObject::update(Time /*time*/)
{
    return false;
}

MapPos MapObject::getPos(void) const
{
    return rect_.topLeft();
}

MapRect MapObject::getRect()
{
    return rect_;
}

void MapObject::setRect(const MapRect &rect)
{
    rect_ = rect;
}

void MapObject::setPos(const MapPos pos)
{
    rect_.x = pos.x;
    rect_.y = pos.y;
}

}
