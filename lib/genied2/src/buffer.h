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


#pragma once

// For memcpy:
#include <string.h>

class Buffer
{
public:
  Buffer ( int size );
  ~Buffer();

  /*
  void read(void*, const int size);
  void write(void*, const int size);
  void seek(const int pos);
  void jump(const int diat);
  int tell();
  */

  inline void read ( void* item, const int size )
  {
    memcpy ( item, &rawData[rawBufferPos], size );
    rawBufferPos += size;
  }
  
  inline void write ( void* item, const int size )
  {
    memcpy ( &rawData[rawBufferPos], item, size );
    rawBufferPos += size;
  }

  int find ( const char* str );

  inline void seek ( const int pos )
  {
    rawBufferPos = pos;
  }

  inline void jump ( const int dist )
  {
    rawBufferPos += dist;
  }

  inline int tell()
  {
    return rawBufferPos;
  }

// almost private:
  char *rawData;
  int rawBufferSize;
private:
  int rawBufferPos;
};
