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


#include "DrsReader.h"

#include <string>

#include "IOHelper.h"

//Debug
#include <iostream>
using std::cout;
using std::endl;

DrsReader::DrsReader()
{

}

DrsReader::~DrsReader()
{

}

//------------------------------------------------------------------------------
void DrsReader::read ( std::istream& istr )
{
  // Copyright
  std::cout << IOHelper::readString(istr, 40) << std::endl;
  
  //Version
  std::cout << IOHelper::readString(istr, 4) << std::endl;
  
  //File type
  std::cout << IOHelper::readString(istr, 12) << std::endl;
  
  //Number of tablse 
  std::cout << IOHelper::readLong(istr) << std::endl;
  
  // Number of files
  std::cout << IOHelper::readLong(istr) << std::endl;
}
