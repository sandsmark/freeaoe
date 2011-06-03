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

