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

const unsigned int GenieTerrain::TERRAIN_NAME_SIZE = 17; //13 in aok

void GenieTerrain::read(FileIO *file)
{
  unknown1 = file->readInt16();
  unknown2 = file->readInt16();
  
  name1 = file->readString(TERRAIN_NAME_SIZE);
  name2 = file->readString(TERRAIN_NAME_SIZE);
  
  slp_id = file->readUInt32();
  unknown3 = file->readUInt32();
  unknown4 = file->readUInt32();
  unknown5 = file->readUInt32();
  color = file->readUInt32();
  
  unknown6 = file->readString(406); //382 in aok
}
