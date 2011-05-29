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


#ifndef DRSREADER_H
#define DRSREADER_H

#include <istream>

class DrsReader
{

public:
  DrsReader();
  virtual ~DrsReader();
    
  //----------------------------------------------------------------------------
  /// Reads a drs formated file from istream.
  ///
  /// @param istr stream to read from
  //
  void read(std::istream &istr);
};

#endif // DRSREADER_H
