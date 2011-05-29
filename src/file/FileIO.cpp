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


#include "FileIO.h"

FileIO::FileIO()
{

}

FileIO::FileIO(std::istream* istr, std::streampos pos) : istr_(istr), pos_(pos)
{

}


FileIO::~FileIO()
{

}

//------------------------------------------------------------------------------
void FileIO::setIstream(std::istream* istr)
{
  istr_ = istr;
}

//------------------------------------------------------------------------------
std::istream* FileIO::getIstream()
{
  return istr_;
}


//------------------------------------------------------------------------------
void FileIO::setToPos()
{
  istr_->seekg(pos_);
}

//------------------------------------------------------------------------------
std::string FileIO::readString ( size_t size )
{
  if (!istr_->eof())
  {
    char *buf = new char[size + 1];
    
    istr_->read(buf, size);
    
    buf[size] = '\0';
    
    return std::string(buf);
  }

  return "";
}

//------------------------------------------------------------------------------
long int FileIO::readLong ()
{
  long ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 4);
  }
  
  return ret;
}
