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

#include <zlib.h>
#include <assert.h>
#include <iostream> 

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>

Logger& DatFile::log = Logger::getLogger("freeaoe.DatFile");

DatFile::DatFile()
{

}

void DatFile::open(std::string filename)
{
  /*std::fstream file_buf;
  file_buf.open(filename.c_str(), std::ios::binary);
  
  decompress(file_buf);
  
  log.info("Writing testfile");
  std::fstream file;
  file.open("raw.dat", std::ios::out);
  file << file_buf_.str();
  file.close();*/
  using namespace std;

  std::cout << filename << std::endl;
  ifstream file(filename.c_str(), ios_base::in | ios_base::binary);
  using namespace boost::iostreams;
  using namespace std;
  
  filtering_streambuf<input> in;
  
  in.push(zlib_decompressor());
  in.push(file);
  
  /*ofstream file_out;
  file_out.open("raw.dat", ios_base::binary);
  
  */
  boost::iostreams::copy(in, cout); //file_out);
  
  //file_out.close();*/
 
}

void DatFile::decompress(std::fstream& file)
{ 
  int ret;
  unsigned have;
  z_stream strm;
  char in[ZLIB_CHUNK];
  char out[ZLIB_CHUNK];
  
  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit(&strm);
  
  if (ret != Z_OK)
  {
    log.error("Decompressing dat file [%s] failed with error code %d",
              "unknown", ret);
  }     
  
  /* decompress until deflate stream ends or end of file */
  do {
    strm.avail_in = file.readsome(in, ZLIB_CHUNK);//fread(in, 1, CHUNK, source);
    if ( file.bad() )
    {
      (void)inflateEnd(&strm);
      log.error("file bad");
      return ;//Z_ERRNO;
    }
    if (strm.avail_in == 0)
    {
      log.error("break?");
      break;
    }
    strm.next_in = reinterpret_cast<unsigned char *>(in);

    /* run inflate() on input until output buffer not full */
    do {
      strm.avail_out = ZLIB_CHUNK;
      strm.next_out = reinterpret_cast<unsigned char*>(out);
      ret = inflate(&strm, Z_NO_FLUSH);
      assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
      switch (ret) {
      case Z_NEED_DICT:
        ret = Z_DATA_ERROR;     /* and fall through */
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
        (void)inflateEnd(&strm);
        log.error("something wrong");
        return; // ret;
      }
      have = ZLIB_CHUNK - strm.avail_out;
      
      
      /*if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
        (void)inflateEnd(&strm);
        return Z_ERRNO;
      }*/
      std::cout << have << std::endl;
      file_buf_.write(out, have);
    
    } while (strm.avail_out == 0);

  /* done when inflate() says it's done */
  } while (ret != Z_STREAM_END);

  /* clean up and return */
  (void)inflateEnd(&strm);
  return ;//ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


DatFile::DatFile(const DatFile& other)
{

}

DatFile::~DatFile()
{

}

DatFile& DatFile::operator=(const DatFile& other)
{
    return *this;
}

