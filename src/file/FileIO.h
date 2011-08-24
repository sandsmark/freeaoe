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


#ifndef FILEIO_H
#define FILEIO_H

#include <istream>
#include <fstream>
#include <memory>
#include <SFML/Config.hpp>
#include <global/FileException.h>

//------------------------------------------------------------------------------
/// Base class for file input/output. Used for managing an input stream.
//
class FileIO
{

public:
  //----------------------------------------------------------------------------
  /// If this Constructor is called, FileIO will manage the file and its 
  /// streams..
  ///
  /// @param file_name 
  //
  FileIO(std::string file_name) throw (FileException);
  
  //----------------------------------------------------------------------------
  /// Constructor
  //
  FileIO(std::iostream *iostr, std::streampos pos);
  
  //----------------------------------------------------------------------------
  /// Copy Constructor
  FileIO(const FileIO &fio);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~FileIO();
  
  //----------------------------------------------------------------------------
  /// Sets input stream
  //
  //void setIstream(std::istream *istr);
  
  //----------------------------------------------------------------------------
  /// Get input stream
  //
  std::iostream* getIOStream();
  
  //----------------------------------------------------------------------------
  /// Get start pos.
  //
  std::streampos getPos();
  
  //----------------------------------------------------------------------------
  /// Get file pos
  //
  std::streampos tellg();
  
  //----------------------------------------------------------------------------
  /// Sets file pointer to Pos
  //
  void setToPos();
  
  //----------------------------------------------------------------------------
  /// Check eof bit
  //
  bool eof();
  
  //----------------------------------------------------------------------------
  /// Reads a string from stream.
  ///
  /// @param istr input stream
  /// @param size string len
  /// @return read string
  //
  std::string readString(size_t len);
  
  //----------------------------------------------------------------------------
  /// Generic read method for non pointers
  //
  template <typename T>
  T read()
  {
    T ret;
  
    if (!iostr_->eof())
      iostr_->read(reinterpret_cast<char *>(&ret), sizeof(ret));
    
    return ret;
  }
  
  //----------------------------------------------------------------------------
  /// Generic read method for arrays
  //
  template <typename T>
  T* read(size_t len)
  {
    T* ret = 0;
    
    if (!iostr_->eof())
    {
      ret = new T[len];
      iostr_->read(reinterpret_cast<char *>(ret), sizeof(T) * len);
    }
    
    return ret;
  }
  
  
private:
  FileIO();
  
  std::iostream *iostr_;
  std::streampos pos_;
  
  std::string file_name_;
  std::fstream *file; //is only used if FileIO is called with file_name
  
  FileIO& operator=(const FileIO &fio);
};

#endif // FILEIO_H
