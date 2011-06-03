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
