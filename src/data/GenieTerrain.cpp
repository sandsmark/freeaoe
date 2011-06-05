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


#include "GenieTerrain.h"

#include <file/FileIO.h>

using sf::Uint16;
using sf::Uint32;
using sf::Int16;

const unsigned int GenieTerrain::TERRAIN_NAME_SIZE = 13; //17 in swgb

void GenieTerrain::read(FileIO *file)
{
  unknown1 = file->read<Int16>();
  unknown2 = file->read<Int16>();
  
  name1 = file->readString(TERRAIN_NAME_SIZE);
  name2 = file->readString(TERRAIN_NAME_SIZE);
  
  slp_id = file->read<Uint32>();
  unknown3 = file->read<Uint32>();
  unknown4 = file->read<Uint32>();
  unknown5 = file->read<Uint32>();
  color = file->read<Uint32>();
  
  unknown6 = file->readString(382); //406 in swgb
}
