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

#include <iostream>

using sf::Uint32;

//------------------------------------------------------------------------------
SlpFile::SlpFile(sf::Uint32 id, sf::Uint32 pos, sf::Uint32 len, 
                 std::iostream* iostr) : id_(id), FileIO(iostr, pos), len_(len)
{
}

//------------------------------------------------------------------------------
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
  if (frames_.size() > 0) //already loaded
    return;
  
  setToPos(); //TODO: Segfault why?
  
  readHeader();
  
  SlpFrame *frame = 0;
  
  for (u_int32_t i = 0; i < num_frames_; i++)
  {
    frame = new SlpFrame(getIOStream(), tellg(), getPos(), 0);
    frame->loadHeader();
    
    frames_.push_back(frame);
  }

  for (std::vector<SlpFrame *>::iterator it = frames_.begin(); 
       it != frames_.end(); it ++)
  {
    (*it)->load();
  }
}

//------------------------------------------------------------------------------
sf::Uint32 SlpFile::getFrameCount()
{
  return num_frames_;
}

//------------------------------------------------------------------------------
sf::Int32 SlpFile::getId()
{
  return id_;
}

//------------------------------------------------------------------------------
sf::Image* SlpFile::getImage(sf::Uint32 frame)
{
  if (frame >= frames_.size())
    return 0;
  
  return frames_[frame]->getImage();
}


//------------------------------------------------------------------------------
void SlpFile::readHeader()
{
  std::string version = readString(4);
  num_frames_ = read<Uint32>();
  
  std::string comment = readString(24);
}

