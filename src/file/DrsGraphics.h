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


#ifndef DRSGRAPHICS_H
#define DRSGRAPHICS_H

#include <map>
#include <vector>

#include "DrsFile.h"
#include "SlpFile.h"

class DrsGraphics : public DrsFile
{

public:
  DrsGraphics(std::iostream *iostr, std::streampos pos, 
              std::map<long, SlpFile *> *slp_files);
  
  DrsGraphics(std::string file_name, std::map<long, SlpFile *> *slp_files);
//  DrsGraphics(const DrsGraphics& other);
  virtual ~DrsGraphics();
    
  virtual void load();
  
  sf::Image *image_;
    
private:
  long num_of_slp_;
  
  std::streampos start_of_slp_;
  
  std::map<long, SlpFile *> *slp_files_;
  
  void readHeader();
  void readSlpHeaders();
};

#endif // DRSGRAPHICS_H
