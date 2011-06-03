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


// Disable "warning C4103: used #pragma pack to change alignment"
//#pragma warning(disable: 4103)

// For unknowns:
typedef unsigned char raw;

#include "structs/unitparts.h"

#include "buffer.h"

class genie_civ
{
public:

  genie_civ();
  ~genie_civ();

  char one;
  char name1[16];
  short unknown01[2];
  short unknown04_length;
  short unknown02[2];
  char name2[20];
  short unknown03[4];
  float* unknown04;
  char graphicsset;
  short unit_count;

};

class genie_unit
{
public:
  genie_unit();
  ~genie_unit();

  void Read ( Buffer *DataBuffer, int VersionNum );
  void Write ( Buffer *DataBuffer, int VersionNum );

  char type;

  genie_unit_head head;

  char unknown01_length;
  raw* unknown01; // x 4*unknown01_length

  short sounds[3];
  char* name1; // x head.name1_length
  short name2_length;
  char* name2;
  short unitline_id;
  char mintechlevel;
  short id2;
  short id3;

  genie_unit_part2* part2;
  genie_unit_part3* part3;
  genie_unit_part4* part4;
  genie_unit_part5* part5;

  short attacks_length;
  short* attacks; // x 2*attacks_length
  short armour_length;
  short* armour; // x 2*armour_length

  genie_unit_part6* part6;
  genie_unit_part7* part7;
  genie_unit_part8* part8;
  genie_unit_part9* part9;
  genie_unit_part10* part10;
  genie_unit_part11* part11;
  genie_unit_part12* part12;
  genie_unit_part14* part14;
  genie_unit_part15* part15;

private:
  Buffer *DataBuffer_;
  
  template<typename T>
  inline void brds ( T &i )
  {
    DataBuffer_->read(&i, sizeof(i));
  }
  
  template<typename T>
  inline void brdm (T *i)
  {
    i = new T;
    DataBuffer_->read(i, sizeof(T));
  }
  
  template<typename T>
  inline void brdl(T *i, unsigned int s)
  {
    i = new T[s];
    DataBuffer_->read(i, s*sizeof(T));
  }
  
// and allocate it too
//#define brdm(i, t) i = new t; DataBuffer->read(i, sizeof(t))
// and handle multiple small types
//#define brdl(i, s, t) i = new t[s]; DataBuffer->read(i, s*sizeof(t))

  template<typename T>
  inline void bwrs(T &i) { DataBuffer_->write(&i, sizeof(i)); }
  
  template<typename T>
  inline void bwrm(T *i) { DataBuffer_->write(i, sizeof(T)); }
  
  template<typename T>
  inline void bwrl(T *i, unsigned int s) 
  { 
    DataBuffer_->write(i, s*sizeof(T)); 
  }
/*#define bwrs(i) DataBuffer->write(&##i, sizeof(i))
#define bwrm(i, t) DataBuffer->write(i, sizeof(t))
#define bwrl(i, s, t) DataBuffer->write(i, s*sizeof(t))
*/
};
