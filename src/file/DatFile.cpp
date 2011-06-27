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


#include "DatFile.h"

#include <assert.h>
#include <iostream> 
#include <vector>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>

using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::vector;

Logger& DatFile::log = Logger::getLogger("freeaoe.DatFile");

//------------------------------------------------------------------------------
DatFile::DatFile()
{
  buf_stream_ = 0;
}

//------------------------------------------------------------------------------
DatFile::~DatFile()
{
  delete buf_stream_;
}

//------------------------------------------------------------------------------
void DatFile::open(std::string filename)
{
  ifstream file(filename.c_str(), ios_base::in | ios_base::binary);
  
  if (buf_stream_)
    delete buf_stream_;
  
  buf_stream_ = decompress(file);

  ofstream fo("raw.dat", ios_base::binary);
  fo << buf_stream_->rdbuf();
  fo.close();
}

//------------------------------------------------------------------------------
DatFile::v_stream* DatFile::decompress(std::ifstream& file)
{ 
  using namespace boost::iostreams;
  
  try
  {
    filtering_streambuf<input> in;
    
    zlib_params para;
    para.window_bits = -15;     //Dunno why, but works (taken from genied2)
    
    in.push(zlib_decompressor(para));
    in.push(file);
    
    vector<char> buf;
    
    back_insert_device< std::vector<char> > b_ins(buf); 
    
    copy(in, b_ins);
    
    return new v_stream(buf);
  }
  catch ( const zlib_error &z_err)
  {
    log.fatal("Zlib decompression failed with error code %d", z_err.error());
  }
  
  return 0;
}

