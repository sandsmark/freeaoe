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

//TODO maybe observer pattern
class Camera
{

public:
  Camera();
  virtual ~Camera();
  
  /// Returns the map position the camera is pointing at
  MapPos getTargetPosition(void) const;
  
  void setTargetPosition(MapPos target);
  
  //void move(int x, int y);
  
private:
  MapPos target_;
};

typedef std::shared_ptr<Camera> CameraPtr;

#endif // CAMERA_H
