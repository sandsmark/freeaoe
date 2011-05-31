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


#include "SlpFrame.h"

#include <SFML/Graphics/Image.hpp>

#include <iostream>
#include "ColorPalette.h"

//Debug
#include <assert.h>

using sf::Uint8;
using sf::Uint32;

SlpFrame::SlpFrame(std::istream* istr, std::streampos pos, 
                   std::streampos file_pos, ColorPalette *palette) 
                   : FileIO(istr, pos), file_pos_(file_pos), palette_(palette)
{
  palette_ = new ColorPalette("../aoe2/50500.pal"); //TODO: Warning
  
  left_edges_   = 0;
  right_edges_  = 0;
  image_        = 0;
}


SlpFrame::~SlpFrame()
{
  delete palette_; //TODO
}

sf::Image* SlpFrame::getImage()
{
  return image_;
}

void SlpFrame::loadHeader()
{
  cmd_table_offset_     = readUInt32();
  outline_table_offset_ = readUInt32();
  palette_offset_       = readUInt32();
  properties_           = readUInt32();
  
  width_     = readInt32();
  height_    = readInt32();
  hotspot_x_ = readInt32();
  hotspot_y_ = readInt32();
  
  std::cout << palette_offset_ << std::endl;
}

void SlpFrame::load()
{
  assert(!image_); //TODO: Not implemented
  image_ = new sf::Image(width_, height_);
  
  readEdges();
  
  // Skipping command offsets. They are not needed now but
  // they can be used for checking file integrity.
  for (Uint32 i=0; i < height_; i++)
  {
    readUInt32();
  }
  
  // Each row has it's commands, 0x0F signals the end of a rows commands.
  for (Uint32 row = 0; row < height_; row++)
  {
    std::cout << row << ": ";
    Uint8 data = 0;
    
    while (data != 0x0F)
    {
      data = readUInt8();
      
      if (data == 0x0F)
        break;
      
      /*
       * Command description kindly taken from  Bryce Schroeders SLPLib
       * bryce@lanset.com
       */
      Uint8 cmd = data & 0xF;
      
      Uint32 pix_cnt = 0;
      //Uint32 pix_pos = left_edges_[row];
      
      switch (cmd) //0x00
      {
        case 0: // Lesser block copy
        case 4:
        case 8:
        case 0xC:
          pix_cnt = data >> 2;
          readPixelsToImage(row, left_edges_[row], pix_cnt);
          break;
        
    /*    case 1: // lesser skip
        case 5:
        case 9:
        case 0xD:
          pix_cnt = (data & 0xFC) >> 2;
          
          for (int j=0; j < pix_cnt; j++)
          {
            image_->SetPixel(pix_pos, i, palette_->getColorAt(readUInt8()));
          }
          break;
          
        case 2: // greater block copy
          pix_cnt = ((data & 0xF0) << 4) + readUInt8();
          for (int j=0; j <pix_cnt; j++)
          {
            u_int8_t nc = readUInt8();
            image_->SetPixel(pix_pos, i, palette_->getColorAt(nc));
            pix_pos++;
          }
        
          break;
          
        */
      }
      
     /* if ( (cmd_ch >> 4) == 0x02 ) 
      {
        int num_pix = (cmd_ch >> 4) * 256;
        num_pix += readUInt8();
        
        int pix_pos = left_edges_[i];
        for (int j=0; j <num_pix; j++)
        {
          u_int8_t nc = readUInt8();
          image_->SetPixel(pix_pos, i, pf.getColorAt(nc));
          pix_pos++;
        }
        continue;
      }
      */
      
      
    }
    
    std::cout << std::endl;
  }
  
}

//------------------------------------------------------------------------------
void SlpFrame::readEdges()
{
  std::streampos cmd_table_pos = file_pos_ + std::streampos(cmd_table_offset_);
  
  left_edges_ = new sf::Uint16[height_];
  right_edges_= new sf::Uint16[height_];
  
  sf::Uint32 row_cnt = 0;
  
  while (tellg() < cmd_table_pos)
  {
    left_edges_[row_cnt] = readUInt16();
    right_edges_[row_cnt] = readUInt16();
    
    // Set edges transparent
    for (sf::Uint32 i=0; i < left_edges_[row_cnt]; i++)
      image_->SetPixel(i, row_cnt, sf::Color(0,0,0,0));
    
    for (sf::Uint32 i=width_-1; i >= (width_ - right_edges_[row_cnt]); i--)
      image_->SetPixel(i, row_cnt, sf::Color(0,0,0,0));
    
    std::cout << row_cnt << ": " << left_edges_[row_cnt] << " " << right_edges_[row_cnt] << std::endl;
    row_cnt ++;
  }
 
}

//------------------------------------------------------------------------------
void SlpFrame::readPixelsToImage(Uint32 row, Uint32 col, Uint32 count)
{
  for (int i=col; i < (count + col); i++)
  {
    Uint8 pixel_index = readUInt8();
    image_->SetPixel(i, row, palette_->getColorAt(pixel_index));
  }
 
}


