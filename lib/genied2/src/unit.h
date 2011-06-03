#pragma once

#include "buffer.h"
#include <string>
#include <list>
#include <vector>

#include "language.h"

class GenieUnit
{
public:
  Buffer *DataBuffer;
  LanguageDLL *LangDLL;
  std::string DisplayName;
  int Id;
  int FileOffset;
  int VersionNum;
  typedef std::vector<std::string> SearchablesType;
  SearchablesType Searchables;

  bool operator< ( GenieUnit &a )
  {
    return DisplayName < a.DisplayName || Id < a.Id;
  }

};

class GenieCiv
{
public:
  std::string Title;

  typedef std::list<GenieUnit> UnitsType;
  UnitsType Units;

};
