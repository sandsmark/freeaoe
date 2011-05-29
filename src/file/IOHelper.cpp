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


#include "IOHelper.h"

//------------------------------------------------------------------------------
std::string IOHelper::readString ( std::istream& istr, size_t size )
{
  if (!istr.eof())
  {
    char *buf = new char[size];
    
    istr.read(buf, size);
    
    return std::string(buf);
  }

  return "";
}

//------------------------------------------------------------------------------
long int IOHelper::readLong ( std::istream& istr )
{
  long ret = 0;
  
  if (!istr.eof())
  {
    istr.read(reinterpret_cast<char *>(&ret), 4); //TODO: Long??
  }
  
  return ret;
}


IOHelper::IOHelper()
{

}

IOHelper::IOHelper ( const IOHelper& other )
{

}

IOHelper::~IOHelper()
{

}

