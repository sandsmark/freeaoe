#include <string>
#include <list>

#include "unit.h"
#include "language.h"
#include "buffer.h"

class GenieFile
{

public:
  GenieFile();
  ~GenieFile();

  void LoadGenie ( const char* filename );
  void SaveGenie ( const char* filename );

  bool LoadLanguage ( const char* filename );

  void Dump ( const char* filename );

  void ReadUnitsData ( void ProgressCallback ( float, void* ), void* CallbackData );

  typedef std::list<GenieCiv*> CivsType;
  CivsType Civs;
  int VersionNum;

private:

  LanguageDLL *LangDLL;

  Buffer *DataBuffer;

  void Decompress ( const char* filename );
  void Recompress ( const char* filename );

  //std::wstring GenieFile::GenerateName(int id, int lang, const char* name);

};
