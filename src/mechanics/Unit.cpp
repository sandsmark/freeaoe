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
#include <communication/UnitStatus.h>
#include "IAction.h"

//------------------------------------------------------------------------------
Unit::Unit(sf::Uint32 id) : id_(id), action_(0)
{

}

//------------------------------------------------------------------------------
Unit::~Unit()
{

}

//------------------------------------------------------------------------------
void Unit::setPos(MapPos pos)
{
  pos_ = pos;
}

//------------------------------------------------------------------------------
MapPos Unit::getPos(void ) const
{
  return pos_;
}

//------------------------------------------------------------------------------
sf::Uint32 Unit::getID(void ) const
{
  return id_;
}

//------------------------------------------------------------------------------
void Unit::setData(gdat::Unit data)
{
  data_ = data;
}

//------------------------------------------------------------------------------
gdat::Unit Unit::getData(void ) const
{
  return data_;
}

//------------------------------------------------------------------------------
/*
UnitStatus Unit::getStatus (void)
{
  return UnitStatus(id_, data_.ID1, pos_);
}
*/

//------------------------------------------------------------------------------
void Unit::setCurrentAction(IAction* action)
{
  action_ = action;
}

//------------------------------------------------------------------------------
IAction* Unit::getCurrentAction(void ) const
{
  return action_;
}


