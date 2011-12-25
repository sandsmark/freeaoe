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


#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "IAttribute.h"

//#include "Entity.h"

namespace attr
{

// Maybe there's a nicer way to do this
class id
{
public:
  static const char * const NAME;
  static const char * const MAP_3D_POS;
  static const char * const SCREEN_POS;
  static const char * const MOVABLE;
  static const char * const COLLIDABLE;
  static const char * const LOGICAL_SHAPE;
};

class String : public IAttribute
{
public:
  String(std::string s) : value(s) {}
  
  std::string value;
};

/// Position on a 3d map
class Map3DPos : public IAttribute
{
public:
  sf::Vector3f Pos;
};

class ScreenPos : public IAttribute
{
public:
  sf::Vector2f Pos;
  
};


class Movable : public IAttribute
{
public:
  Movable() : paralyzed(false) {}
  
  bool paralyzed;
};

class Collideable: public IAttribute
{
};

//TODO
class Shape
{};

class Rectangle : public Shape
{
public:
  Rectangle(int width, int heigth) : width_(width), heigth_(heigth) {}
  
//private:  
  int width_, heigth_;
  
};

class Circle : public Shape
{
public:
  Circle(float diameter) : diameter_(diameter) {}

  float diameter_;
};

/// Shape in the logical space. Used for collision detection ...
class LogicalShape: public IAttribute
{
public:
  enum ShapeType {
    RECTANGLE = 0,
    CIRCLE = 1
  };
  
  LogicalShape(const Rectangle &rect) : shape_(rect)
  {
    type_ = RECTANGLE;
  }
  
  LogicalShape(const Circle &circ) : shape_(circ)
  {
    type_ = CIRCLE;
  }
  
  
  ShapeType type_;
  
  Shape shape_;
};



}

#endif // ATTRIBUTES_H
