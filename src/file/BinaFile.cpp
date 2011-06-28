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


#include "BinaFile.h"

#include "ColorPalette.h"

#include <iostream>

BinaFile::BinaFile(sf::Uint32 id, sf::Uint32 pos, sf::Uint32 len, 
                   std::iostream* iostr) : id_(id), FileIO(iostr, pos), 
                   len_(len)
{
  palette_ = 0;
}

BinaFile::~BinaFile()
{
  delete palette_;
}


ColorPalette* BinaFile::readPalette()
{
  if (palette_ == 0)
  {
    palette_ = new ColorPalette();
    setToPos();
     
    palette_->parsePalette(*getIOStream());
  }
  
  return palette_;
}

sf::Uint32 BinaFile::getId()
{
  return id_;
}
