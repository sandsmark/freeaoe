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

//------------------------------------------------------------------------------
/*FileIO::FileIO() : file(0), file_name_("")
{

}
*/

//------------------------------------------------------------------------------
FileIO::FileIO(std::string file_name) throw (FileException) 
               : file_name_(file_name)
               
{
  file = new std::fstream(file_name.c_str());
  
  if (!file->is_open() || file->bad())
  {
    delete file;
    throw FileException("Can't open " + file_name);
  }
  
  pos_ = file->tellg();
  istr_ = file;
}

//------------------------------------------------------------------------------
FileIO::FileIO(std::istream* istr, std::streampos pos) : istr_(istr), pos_(pos),
               file(0), file_name_("")
{

}

//------------------------------------------------------------------------------
FileIO::~FileIO()
{
  delete file;
}
/*
//------------------------------------------------------------------------------
void FileIO::setIstream(std::istream* istr)
{
  istr_ = istr;
}
*/
//------------------------------------------------------------------------------
std::istream* FileIO::getIstream()
{
  return istr_;
}

//------------------------------------------------------------------------------
std::streampos FileIO::getPos()
{
  return pos_;
}

//------------------------------------------------------------------------------
std::streampos FileIO::tellg()
{
  return istr_->tellg();
}


//------------------------------------------------------------------------------
void FileIO::setToPos()
{
  istr_->seekg(pos_);
}

//------------------------------------------------------------------------------
bool FileIO::eof()
{
  return istr_->eof();
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
sf::Int32 FileIO::readInt32 ()
{
  sf::Int32 ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 4);
  }
  
  return ret;
}

//------------------------------------------------------------------------------
sf::Uint32 FileIO::readUInt32 ()
{
  sf::Uint32 ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 4);
  }
  
  return ret;
}

//------------------------------------------------------------------------------
sf::Uint16 FileIO::readUInt16 ()
{
  sf::Uint16 ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 2);
  }
  
  return ret;
}

//------------------------------------------------------------------------------
sf::Int16 FileIO::readInt16 ()
{
  sf::Int16 ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 2);
  }
  
  return ret;
}

//------------------------------------------------------------------------------
sf::Uint8 FileIO::readUInt8()
{
  sf::Uint8 ret = 0;
  
  if (!istr_->eof())
  {
    istr_->read(reinterpret_cast<char *>(&ret), 1);
  }
  
  return ret;
}

//------------------------------------------------------------------------------
char FileIO::readChar()
{
  char ret;
  
  if (!istr_->eof())
  {
    istr_->read(&ret, 1);
  }
  
  return ret;
}
