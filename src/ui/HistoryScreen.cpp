/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

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
#include "HistoryScreen.h"
#include "resource/LanguageManager.h"

HistoryScreen::HistoryScreen()
{
    int numEntries = std::stoi(LanguageManager::getString(20310));
    std::vector<std::string> titles;

    for (int i=0; i<numEntries; i++) {
        titles.push_back(LanguageManager::getString(20310 + 1 + i));
    }

    std::vector<std::string> sourceFiles;


    for (int i=0; i<numEntries; i++) {
        sourceFiles.push_back(LanguageManager::getString(20410 + 1 + i));
    }
}
