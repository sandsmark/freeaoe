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
#include "SlpFrame.h"


SlpFile::SlpFile()
{

}

SlpFile::SlpFile(int32_t id, int32_t len, std::istream* istr, 
                 std::streampos pos) : FileIO(istr, pos), id_(id), len_(len)
{
}

SlpFile::~SlpFile()
{
  for (std::vector<SlpFrame *>::iterator it = frames_.begin(); 
       it != frames_.end(); it ++)
  {
    delete (*it);
  }
}

//------------------------------------------------------------------------------
void SlpFile::load()
{
  setToPos();
  
  readHeader();
  
  SlpFrame *frame;
  
  for (u_int32_t i = 0; i < num_frames_; i++)
  {
    frame = new SlpFrame(getIstream(), tellg(), getPos(), 0);
    frame->loadHeader();
    
    frames_.push_back(frame);
  }
  
  for (std::vector<SlpFrame *>::iterator it = frames_.begin(); 
       it != frames_.end(); it ++)
  {
    (*it)->load();
    image_ = (*it)->getImage();
  }
}

//------------------------------------------------------------------------------
void SlpFile::readHeader()
{
  std::string version = readString(4);
  num_frames_ = readUInt32();
  
  std::string comment = readString(24);
}

