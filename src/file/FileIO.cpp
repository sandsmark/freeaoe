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

#include <iostream>

FileIO::FileIO() : file(0)
{
}

//------------------------------------------------------------------------------
FileIO::FileIO(std::string file_name) throw (FileException) 
               : file_name_(file_name), file(0)
               
{
  try 
  {
    file = new std::fstream();
    file->open(file_name.c_str(), std::ios::binary | std::ios::out | std::ios::in);
  }
  catch (std::bad_alloc &e)
  {
    delete file;
    file = 0;
    throw;
  }
  
  if (!file->is_open() || file->bad())
  {
    delete file;
    throw FileException("Can't open " + file_name);
  }
  
  pos_ = file->tellg();
  iostr_ = file;
}

//------------------------------------------------------------------------------
FileIO::FileIO(std::iostream* iostr, std::streampos pos) : iostr_(iostr),
               pos_(pos), file_name_(""), file(0)  
{

}

FileIO::FileIO(const FileIO& fio)
{
  iostr_ = fio.iostr_;
  pos_ = fio.tellg();
  
  file = fio.file;
  file_name_ = fio.file_name_;
}


//------------------------------------------------------------------------------
FileIO::~FileIO()
{
  if (file)
  {
    file->close();
    delete file;
  }
}

//------------------------------------------------------------------------------
std::iostream* FileIO::getIOStream() const
{
  return iostr_;
}

//------------------------------------------------------------------------------
std::streampos FileIO::getPos() const
{
  return pos_;
}

//------------------------------------------------------------------------------
std::streampos FileIO::tellg() const
{
  return iostr_->tellg();
}


//------------------------------------------------------------------------------
void FileIO::setToPos()
{
  iostr_->seekg(pos_);
}

//------------------------------------------------------------------------------
bool FileIO::eof() const
{
  return iostr_->eof();
}

//------------------------------------------------------------------------------
std::string FileIO::readString ( size_t len )
{
  if (!iostr_->eof())
  {
    char *buf = new char[len + 1];
    
    iostr_->read(buf, len);
    
    buf[len] = '\0';
    
    std::string ret(buf);
    
    delete buf;
    return ret;
  }

  return "";
}

