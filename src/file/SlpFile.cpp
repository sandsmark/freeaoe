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


#include "SlpFile.h"

#include "IOHelper.h"


SlpFile::SlpFile()
{

}

SlpFile::SlpFile(long int id, long int len, std::istream* istr, 
                 std::streampos pos) : FileIO(istr, pos), id_(id), len_(len)
{
}

SlpFile::~SlpFile()
{

}

//------------------------------------------------------------------------------
void SlpFile::load()
{
  setToPos();
  
  readHeader();
}

//------------------------------------------------------------------------------
void SlpFile::readHeader()
{
  std::string version = readString(4);
  long frame_cnt = readLong();
  std::string comment = readString(24);
}

