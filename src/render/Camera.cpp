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

Camera::Camera()
{
  target_.x = 0;
  target_.y = 0;
  target_.z = 0;
}

Camera::~Camera()
{

}

MapPos Camera::getTargetPosition(void ) const
{
  return target_;
}

void Camera::setTargetPosition(MapPos target)
{
  target_ = target;
}


