#include "language.h"

/*
// Magic to make Unicode work on Win98:
HMODULE LoadUnicowsProc(void);
extern "C" extern FARPROC _PfnLoadUnicows = (FARPROC) &LoadUnicowsProc;

HMODULE LoadUnicowsProc(void)
{
	return(LoadLibraryA("unicows.dll")); // Cows? Hmm...
}


LanguageDLL::LanguageDLL()
{
}

bool LanguageDLL::Open(const TCHAR* filename) 
{
	HMODULE Library = LoadLibrary(filename);
	if (! Library)
		return true;

	Libraries.push_front(Library);
	return false;
}

std::wstring LanguageDLL::GetString(int id)
{
	const int bufferSize = 1024;
	WCHAR buffer[bufferSize];

	for (LibrariesType::iterator i = Libraries.begin(); i != Libraries.end(); ++i)
		if (LoadStringW(*i, id, buffer, bufferSize/sizeof(TCHAR)))
			return buffer;

	return std::wstring(); // empty string

}

LanguageDLL::~LanguageDLL()
{
	for (LibrariesType::iterator i = Libraries.begin(); i != Libraries.end(); ++i)
		FreeLibrary(*i);
}
*/

LanguageDLL::LanguageDLL()
{
  
}

LanguageDLL::~LanguageDLL()
{
  
}

bool LanguageDLL::Open ( const std::string filename )
{
  
}


std::wstring LanguageDLL::GetString(int id)
{
  return std::wstring(L"Lorem ipsum");
}

