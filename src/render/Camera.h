/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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

#ifndef CAMERA_H
#define CAMERA_H
#include <global/Types.h>

#include <memory>

struct Camera
{
    bool isVisible(const MapRect &rect);
    bool isVisible(const ScreenRect &rect) {
        return m_visibleArea.overlaps(rect);
    }

    const MapPos &targetPosition() { return m_target; }

    void setTargetPosition(const MapPos &pos);
    void setViewportSize(const Size &size);

    bool operator==(const Camera &other) {
        return m_visibleArea == other.m_visibleArea &&
               m_target == other.m_target;
    }

    ScreenPos absoluteScreenPos(const MapPos &mpos);

    MapPos absoluteMapPos(ScreenPos pos);

    MapRect absoluteMapRect(const ScreenRect &screenRect) {
        return MapRect(absoluteMapPos(screenRect.topLeft()), absoluteMapPos(screenRect.bottomRight()));
    }

    ScreenRect absoluteScreenRect(const MapRect &mapRect)
    {
        return ScreenRect(absoluteScreenPos(mapRect.topRight()), absoluteScreenPos(mapRect.bottomRight()));
    }

    ScreenRect m_visibleArea;
private:
    MapPos m_target;
    Size m_viewportSize;
};

typedef std::shared_ptr<Camera> CameraPtr;

#endif // CAMERA_H
