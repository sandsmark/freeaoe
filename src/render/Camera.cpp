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

#include "Camera.h"

bool Camera::isVisible(const MapRect &rect)
{
    return m_visibleArea.contains(absoluteScreenPos(rect.topLeft())) ||
            m_visibleArea.contains(absoluteScreenPos(rect.topRight())) ||
            m_visibleArea.contains(absoluteScreenPos(rect.bottomLeft())) ||
            m_visibleArea.contains(absoluteScreenPos(rect.bottomRight()));
}

void Camera::setTargetPosition(const MapPos &pos)
{
    m_target = pos;
}

void Camera::setViewportSize(const Size &size)
{
    m_viewportSize = size;
    m_visibleArea.width = size.width;
    m_visibleArea.height = size.height;
}

ScreenPos Camera::absoluteScreenPos(const MapPos &mpos)
{
    const MapPos absoluteMapPos = m_target - mpos;
    const ScreenPos screenPosition = absoluteMapPos.toScreen();
    const ScreenPos screenCenter(m_viewportSize.width / 2.f, m_viewportSize.height / 2.f);

    return ScreenPos(screenCenter.x - screenPosition.x, screenCenter.y + screenPosition.y);
}

MapPos Camera::absoluteMapPos(ScreenPos pos)
{
    ScreenPos camCenter;
    camCenter.x = m_viewportSize.width / 2.0;
    camCenter.y = m_viewportSize.height / 2.0;

    pos.y = m_viewportSize.height - pos.y;

    // relative map positions (from center)
    MapPos nullCenterMp = camCenter.toMap();

    MapPos nullPos = pos.toMap();

    MapPos absMapPos = m_target + (nullPos - nullCenterMp);

    return absMapPos;
}
