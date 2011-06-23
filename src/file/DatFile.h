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


#ifndef DATFILE_H
#define DATFILE_H

#include <string>
#include <fstream>
#include <sstream>

#include <global/Logger.h>
#include <vector>

#include <boost/interprocess/streams/vectorstream.hpp>

class DatFile
{

public:
  DatFile();
  virtual ~DatFile();

  //----------------------------------------------------------------------------
  void open(std::string filename);
  
private:
  static Logger &log;
  
  DatFile(const DatFile& other);
  //virtual DatFile& operator=(const DatFile& other);
  
  typedef boost::interprocess::basic_vectorstream< std::vector<char> > v_stream;
  v_stream *buf_stream_;
  
  //----------------------------------------------------------------------------
  /// Decompress and return a vectorstream buffering the decompressed file
  ///
  /// @param file file to decompress and buffer
  /// @return buffered vector stream
  ///
  v_stream* decompress(std::ifstream &file);
};

#endif // DATFILE_H
