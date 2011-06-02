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
    aint32_t with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "DrsGraphics.h"

//Debug
#include <iostream>

using std::ios_base;
using std::streampos;

DrsGraphics::DrsGraphics(std::map< long int, SlpFile *> *slp_files): DrsFile(),
                         slp_files_(slp_files)
{

}

DrsGraphics::~DrsGraphics()
{

}

//------------------------------------------------------------------------------
void DrsGraphics::load(std::istream& istr)
{
    DrsFile::load(istr);
    
    readHeader();
    readSlpHeaders();
}

//------------------------------------------------------------------------------
void DrsGraphics::readHeader()
{
  //dunno 4 bytes
  readString(4);
  
  int32_t header_len = readInt32();
  start_of_slp_ = streampos(header_len);
  
  //dunno 8 bytes
  //istr_->seekg(8, ios_base::cur);
  //Maybe file ending
  std::cout << readString(8) << std::endl;
  
  num_of_slp_ = readInt32();
}

//------------------------------------------------------------------------------
void DrsGraphics::readSlpHeaders()
{
  for (int32_t i=0; i < num_of_slp_; i++)
  {
    int32_t id = readInt32();
    int32_t pos = readInt32();
    int32_t len = readInt32();
    
    (*slp_files_)[id] = new SlpFile(id, len, getIstream(), streampos(pos));
  }
//  slp_files_[15000]->load();
//  image_ = slp_files_[15000].getImage(0);
}



