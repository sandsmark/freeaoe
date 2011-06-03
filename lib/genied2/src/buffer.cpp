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


#include "buffer.h"

#include <assert.h>
#include <string.h>

Buffer::Buffer ( int size )
{
  rawData = new char[size];
  rawBufferPos = 0;
  rawBufferSize = size;
}

Buffer::~Buffer()
{
  delete[] rawData;
}


// A bit like strstr, but for not-NULL-terminated data
int memmem_naive ( const char* data, int data_len, const char* search, int search_len )
{
  bool matched;
  for ( int s = 0; s <= data_len - search_len; ++s )
  {
    matched = true;
    for ( int i = 0; i < search_len; ++i )
      if ( data[s+i] != search[i] )
      {
        matched = false;
        break;
      }
    if ( matched )
      return s;
  }
  return -1;
}

// Well, at least it's the same general concept as Rabin-Karp...
// (and it's ever so very slightly faster than the 'naive' method,
// for the uses which I use it for. And an awful lot faster/simpler
// than real Rabin-Karp for those uses.)
int memmem_mutant_rabin_karp ( const char* data, int data_len, const char* search, int search_len )
{
  bool matched;

  char p = 0; // provides automatic modulo 256 (sort of)
  char t = 0;

  int max = data_len-search_len;

  for ( int j = 0; j < search_len; ++j )
  {
    p += search[j];
    t += data[j];
  }
  for ( int s = 0; s <= max; ++s )
  {
    if ( p == t )
    {
      matched = true;
      for ( int i = 0; i < search_len; ++i )
        if ( data[s+i] != search[i] )
        {
          matched = false;
          break;
        }
      if ( matched )
        return s;
    }
    t = t - data[s] + data[s+search_len]; // very very cheap hash
  }

  return -1;
}


int Buffer::find ( const char* str )
{
// return memmem_naive(rawData, rawBufferSize, str, strlen(str));
  return memmem_mutant_rabin_karp ( rawData, rawBufferSize, str, strlen ( str ) );
}

/*
void Buffer::read(void* item, const int size)
{
 int read_size = size;
 // Avoid falling off the end
 if (rawBufferPos+size >= rawBufferSize)
 {
  assert(! "Fell of the end!");
  read_size = rawBufferSize-rawBufferPos;
 }

 memcpy(item, &rawData[rawBufferPos], read_size);
 rawBufferPos += read_size;
}

void Buffer::write(void* item, const int size)
{
 int write_size = size;
 // Avoid falling off the end
 if (rawBufferPos+size >= rawBufferSize)
 {
  assert(! "Fell of the end!");
  write_size = rawBufferSize-rawBufferPos;
 }

 memcpy(&rawData[rawBufferPos], item, write_size);
 rawBufferPos += write_size;
}

void Buffer::seek(const int pos)
{
 rawBufferPos = pos;
}

void Buffer::jump(const int pos)
{
 rawBufferPos = pos;
}

int Buffer::tell()
{
 return rawBufferPos;
}
*/
