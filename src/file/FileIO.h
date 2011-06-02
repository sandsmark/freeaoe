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
  /// Constructor
  //
  //FileIO();
  
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
  FileIO(std::istream *istr, std::streampos pos);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~FileIO();
  
protected:
  
  //----------------------------------------------------------------------------
  /// Sets input stream
  //
  //void setIstream(std::istream *istr);
  
  //----------------------------------------------------------------------------
  /// Get input stream
  //
  std::istream* getIstream();
  
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
  std::string readString(size_t size);
  
  //----------------------------------------------------------------------------
  /// Reads a 4 byte int from stream.
  ///
  /// @param istr input stream
  /// @return read number
  //
  sf::Int32 readInt32(); 
  
  //----------------------------------------------------------------------------
  /// Reads a 4 byte unsigned int from stream.
  ///
  /// @param istr input stream
  /// @return read number
  //
  sf::Uint32 readUInt32(); 
  
  //----------------------------------------------------------------------------
  /// Reads a 2 byte unsigned int from stream.
  ///
  /// @param istr input stream
  /// @return read number
  //
  sf::Uint16 readUInt16(); 
  
  //----------------------------------------------------------------------------
  /// Reads a 2 byte int from stream.
  ///
  /// @param istr input stream
  /// @return read number
  //
  sf::Int16 readInt16(); 
  
  //----------------------------------------------------------------------------
  /// Reads a 1 byte unsigned int from stream.
  ///
  /// @return read number
  //
  sf::Uint8 readUInt8(); 
  
  //----------------------------------------------------------------------------
  /// Reads an array of 8 bit unsigned int from stream.
  ///
  /// @param size number of values
  /// @return read number
  //
  sf::Uint8* readUInt8(size_t size); 
  
  //----------------------------------------------------------------------------
  ///
  //
  char readChar();
  
private:
  std::istream *istr_;
  std::streampos pos_;
  
  std::string file_name_;
  std::fstream *file; //is only used if FileIO is called with file_name
};

#endif // FILEIO_H
