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


#ifndef GENIETERRAIN_H
#define GENIETERRAIN_H
#include <string>

class FileIO;

class GenieTerrain
{
public:
  static const unsigned int TERRAIN_NAME_SIZE;
  
  short unknown1, unknown2;
  //char name1[TERRAIN_NAME1_SIZE];
  std::string name1;
  //char name2[TERRAIN_NAME2_SIZE];
  std::string name2;
  long slp_id;
  long unused1;   //always 0
  long unknown3;
  long unknown4;
  long unknown5;
  long color;
  std::string unknown6;
  //char unknown6[TERRAIN_UNKWN_SIZE];
  
  void read(FileIO *file);
};

#endif // GENIETERRAIN_H
