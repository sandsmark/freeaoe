#pragma once

#include <string>
#include <list>

class LanguageDLL
{
public:
  LanguageDLL();
  ~LanguageDLL();

  // Adds a library with high priority.
  // Returns true on failure.
  bool Open ( const std::string filename );

  std::wstring GetString ( int id );

private:
  //typedef std::list<HMODULE> LibrariesType;
  //LibrariesType Libraries;

};
