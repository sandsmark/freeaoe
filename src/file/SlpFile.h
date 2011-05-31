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


#ifndef SLPFILE_H
#define SLPFILE_H

#include <istream>
#include <vector>

#include "FileIO.h"
#include <SFML/Graphics/Image.hpp>

class SlpFrame;

class SlpFile : public FileIO
{

public:
  SlpFile();
  SlpFile(int32_t id, int32_t len, std::istream *istr, std::streampos pos);
  virtual ~SlpFile();
  
  void load();
  
  sf::Image *image_;
  
private:
  int32_t id_;
  int32_t len_;
  
  u_int32_t num_frames_;
  
  std::vector<SlpFrame *> frames_;
  
  void readHeader();
};

#endif // SLPFILE_H
