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


#include "Resource.h"

#include <global/Types.h>

namespace res
{

//------------------------------------------------------------------------------
Resource::Resource(Uint32 id, Type type) : id_(id), type_(type), loaded_(false)
{

}

//------------------------------------------------------------------------------
Resource::~Resource()
{

}

//------------------------------------------------------------------------------
Uint32 Resource::getId() const
{
  return id_;
}

//------------------------------------------------------------------------------
Resource::Type Resource::getType() const
{
  return type_;
}

//------------------------------------------------------------------------------
bool Resource::isLoaded() const
{
  return loaded_;
}

//------------------------------------------------------------------------------
void Resource::load()
{
  setLoaded(true);
}

//------------------------------------------------------------------------------
void Resource::unload()
{
  setLoaded(false);
}


//------------------------------------------------------------------------------
void Resource::setLoaded(bool loaded)
{
  loaded_ = loaded;
}

}
