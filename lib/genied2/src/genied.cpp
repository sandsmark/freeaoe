#include "genied.h"
#include "structs.h"

#include "zlib/zlib.h"

#include <sstream>
#include <assert.h>
#include <vector>
#include <time.h>

#include <cstdio>

const int MAX_GENIESIZE = 8*1024*1024;

using namespace std;

template <class T>
inline std::string to_string (const T& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}


std::string WStringToString(const std::wstring& s)
{
  std::string temp(s.length(), ' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

GenieFile::GenieFile()
{
  DataBuffer = NULL;
  LangDLL = NULL;
}

GenieFile::~GenieFile()
{
  delete DataBuffer;
  delete LangDLL;

  for ( CivsType::iterator c = Civs.begin(); c != Civs.end(); ++c )
  {
    ( *c )->Units.clear();
    delete *c;
  }
}



void GenieFile::LoadGenie ( const char* filename )
{
  DataBuffer = new Buffer ( MAX_GENIESIZE );

  Decompress ( filename );
}

void GenieFile::SaveGenie ( const char* filename )
{
  Recompress ( filename );
}

#define CHECK_ERROR(e, s) \
        if (e != Z_OK) { \
                std::ostringstream m; \
                m << "Error in " << s << ": " << e; \
                fclose(fh); \
                throw m.str(); \
        }

void GenieFile::Decompress ( const char* filename )
{
  FILE *fh = fopen ( filename, "rb" );
  if ( ! fh )
    throw "Error opening .dat file";

  int err;
  z_stream d_stream;

  d_stream.zalloc = ( alloc_func ) 0;
  d_stream.zfree = ( free_func ) 0;
  d_stream.opaque = ( voidpf ) 0;

  const int inputBufferSize = 65536;
  char inputBuffer[inputBufferSize];

  d_stream.avail_in = 0;
  d_stream.next_out = ( Bytef* ) DataBuffer->rawData;
  d_stream.avail_out = DataBuffer->rawBufferSize;

  err = inflateInit2 ( &d_stream, -MAX_WBITS );
  CHECK_ERROR ( err, "inflateInit" );

  while ( 1 )
  {
    if ( d_stream.avail_in == 0 )
    {
      d_stream.next_in = ( Bytef* ) inputBuffer;
      d_stream.avail_in = fread ( inputBuffer, 1, inputBufferSize, fh );
    }
    if ( d_stream.avail_in == 0 ) break;

    err = inflate ( &d_stream, Z_SYNC_FLUSH );
    if ( err == Z_STREAM_END ) break;
    CHECK_ERROR ( err, "inflate" );
  }

  DataBuffer->rawBufferSize = d_stream.total_out;
  inflateEnd ( &d_stream );

  fclose ( fh );
}


void GenieFile::Recompress ( const char* filename )
{
  FILE *fh = fopen ( filename, "wb" );
  if ( ! fh )
    throw "Error opening .dat file";

  int err;
  z_stream d_stream;

  d_stream.zalloc = ( alloc_func ) 0;
  d_stream.zfree = ( free_func ) 0;
  d_stream.opaque = ( voidpf ) 0;

  const int outputBufferSize = 4096;
  char outputBuffer[outputBufferSize];

  d_stream.next_in = ( Bytef* ) DataBuffer->rawData;
  d_stream.avail_in = DataBuffer->rawBufferSize;
  d_stream.next_out = ( Bytef* ) outputBuffer;
  d_stream.avail_out = outputBufferSize;

  err = deflateInit2 ( &d_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY );
  CHECK_ERROR ( err, "deflateInit" );

  int flush_type = Z_NO_FLUSH;
  while ( 1 )
  {
    if ( d_stream.avail_in == 0 )
      flush_type = Z_FINISH;

    err = deflate ( &d_stream, flush_type );

    int count = outputBufferSize - d_stream.avail_out;
    assert ( count );
    if ( count )
      fwrite ( outputBuffer, 1, count, fh );
    if ( err == Z_STREAM_END ) break;
    CHECK_ERROR ( err, "deflate" );

    d_stream.avail_out = outputBufferSize;
    d_stream.next_out = ( Bytef* ) outputBuffer;
  }

  deflateEnd ( &d_stream );

  fclose ( fh );
}




void GenieFile::Dump ( const char* filename )
{
  assert ( DataBuffer );
  FILE *fh = fopen ( filename, "wb" );
  assert ( fh );
  fwrite ( DataBuffer->rawData, 1, DataBuffer->rawBufferSize, fh );
  fclose ( fh );
}


bool GenieFile::LoadLanguage ( const char* filename )
{
  if ( ! LangDLL )
    LangDLL = new LanguageDLL;

  return LangDLL->Open ( std::string(filename) );
}


// Automatically do sizeof type rubbish
//#define DataBuffer->read(i) DataBuffer->read(&##i, sizeof(i))

// and allocate it too
//#define brdm(i, t) i = new t; DataBuffer->read(i, sizeof(t))
// and handle multiple small types
//#define brdl(i, s, t) i = new t[s]; DataBuffer->read(i, s*sizeof(t))


void GenieFile::ReadUnitsData ( void ProgressCallback ( float, void* ) = NULL, void* CallbackData = NULL )
{
  // Some assumptions
  assert ( sizeof ( char )  == 1 );
  assert ( sizeof ( short ) == 2 );
  assert ( sizeof ( int )   == 4 );
  assert ( sizeof ( float ) == 4 );

  char version[8];
  DataBuffer->seek ( 0 );
  DataBuffer->read ( version, 8 );

  if ( strcmp ( version, "VER 5.7" ) == 0 ) // AOK X-pack format (no support for non X-pack yet)
    VersionNum = 57;
  else if ( strcmp ( version, "VER 5.9" ) == 0 ) // SWGB + SWGB X-pack format
    VersionNum = 59;
  else
    throw "Invalid version number.";

  // Try to work out where the civ section starts
  int offset = DataBuffer->find ( "NATURE" );
  if ( offset < 0 )
  {
    offset = DataBuffer->find ( "Gaia" );
    if ( offset < 0 )
      throw "Can't find NATURE/Gaia!";
  }

  DataBuffer->seek ( offset-3 );

  short CivCount;
  DataBuffer->read ( &CivCount, 2 );


  Civs.clear();

  for ( int CivNum = 0; CivNum < CivCount; ++CivNum )
  {
    if ( ProgressCallback != NULL )
      ProgressCallback ( ( float ) CivNum / ( float ) CivCount, CallbackData );

    GenieCiv *Civ = new GenieCiv;
    Civ->Units.clear();

    genie_civ *c = new genie_civ;
    DataBuffer->read ( &c->one, sizeof(c->one) );
    DataBuffer->read ( &c->name1, sizeof(c->name1) );
    DataBuffer->read ( &c->unknown01, sizeof(c->unknown01) );
    DataBuffer->read ( &c->unknown04_length, sizeof(c->unknown04_length) );
    DataBuffer->read ( &c->unknown02, sizeof(c->unknown02) );
    if ( VersionNum == 59 )
    {
      DataBuffer->read ( &c->name2, sizeof(c->name2) );
      DataBuffer->read ( &c->unknown03, sizeof(c->unknown03) );
    }
    
    c->unknown04 = new float[c->unknown04_length];
    DataBuffer->read(c->unknown04, c->unknown04_length * sizeof(float));
    //brdl ( c->unknown04, c->unknown04_length, float );
    DataBuffer->read ( &c->graphicsset, sizeof(c->graphicsset) );
    DataBuffer->read ( &c->unit_count, sizeof(c->unit_count) );

    if ( VersionNum == 59 )
      Civ->Title = c->name2;
    else
      Civ->Title = c->name1;

    bool *UnitExists = new bool[c->unit_count];
    for ( int UnitNum = 0; UnitNum < c->unit_count; ++UnitNum )
    {
      int temp;
      DataBuffer->read ( &temp, sizeof(temp) );
      UnitExists[UnitNum] = temp ? true : false;
    }


    for ( int UnitNum = 0; UnitNum < c->unit_count; ++UnitNum )
    {
      if ( ! UnitExists[UnitNum] )
        continue;

      int offset = DataBuffer->tell();

      genie_unit *u = new genie_unit;

      u->Read ( DataBuffer, VersionNum );

      assert ( u->head.id == UnitNum );

      GenieUnit unit;
      unit.DataBuffer = DataBuffer;
      unit.LangDLL = LangDLL;
      unit.Id = u->head.id;
      unit.VersionNum = VersionNum;
//                      unit.Title = GenerateName(unit.Id, u->head.language, u->name1);
      unit.FileOffset = offset;

      unit.Searchables.reserve ( 4 );
      unit.Searchables.push_back ( to_string( unit.Id ) );

      // Try to get the language name first
      wstring LangName = LangDLL->GetString ( u->head.language ).c_str();
      if ( LangName.length() )
      {
        // Clobber any non-ASCII, else the regexes complain
        /*wxString LangNameFiltered = wxString::FromAscii ( LangName.ToAscii() );
        int len = LangNameFiltered.Length();
        wxChar *buf = LangNameFiltered.GetWriteBuf ( len );
        for ( int i = 0; i < len; ++i )
          buf[i] &= 0x7F;
        LangNameFiltered.UngetWriteBuf(); */
        unit.Searchables.push_back ( WStringToString( LangName ) );//LangNameFiltered );
      }

      //wxString Name1 = wxString::FromAscii ( u->name1 );
      string Name1( u->name1 );
      unit.Searchables.push_back ( Name1 );

      string Name2;
      if ( VersionNum == 59 )
      {
        //Name2 = wxString::FromAscii ( u->name2 );
        Name2 = string( u->name2 );
        unit.Searchables.push_back ( Name2 );
      }

      string DisplayName = WStringToString(LangName);
      if ( DisplayName.empty() ) //TODO .empty?? was !DisplayName
        DisplayName = Name2;
      if ( DisplayName.empty() )
        DisplayName = Name1;

      unit.DisplayName = DisplayName + " [" + to_string( unit.Id ) + "]";
      //wxString::Format ( wxT ( "%s [%i]" ), DisplayName, unit.Id );

      Civ->Units.push_back ( unit );

      delete u;
    }
    delete[] UnitExists;

    delete c;

    Civ->Units.sort();

    Civs.push_back ( Civ );
  }

}

/*
std::wstring GenieFile::GenerateName(int id, int lang, const char* name)
{
        std::wostringstream Name;
        std::wstring LangText = LangDLL->GetString(lang);
        if (LangText.length() == 0)
                Name << name << " (" << id << ")";
        else
                Name << LangText << " (" << id << ")";
        return Name.str();
}
*/
