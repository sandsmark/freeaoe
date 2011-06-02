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


#ifndef SUBFILE_H
#define SUBFILE_H

#include "FileIO.h"


class SubFile : public FileIO
{

public:
  SubFile(sf::Uint32 id, sf::Uint32 pos, sf::Uint32 len, std::iostream* iostr);
  
  virtual ~SubFile();
    
private:
  SubFile();
  SubFile(std::string file_name);
  
  sf::Uint32 id_;
  std::streampos pos_;
  sf::Uint32 len_;
};

#endif // SUBFILE_H
