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


#include "Unit.h"

Unit::Unit(sf::Uint32 id) : id_(id)
{

}

Unit::Unit(const Unit& other)
{

}

Unit::~Unit()
{

}

void Unit::setPos(sf::Uint32 x, sf::Uint32 y)
{
  x_ = x;
  y_ = y;
}

sf::Uint32 Unit::getX(void ) const
{
  return x_;
}

sf::Uint32 Unit::getY(void ) const
{
  return y_;
}

GenieUnit Unit::getData(void ) const
{
  return data_;
}
