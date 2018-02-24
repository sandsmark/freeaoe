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

#include "CompUnitData.h"
#include <resource/DataManager.h>
#include "resource/LanguageManager.h"

namespace comp {

UnitData::UnitData()
{
}

UnitData::~UnitData()
{
}

bool UnitData::update(Time /*time*/)
{
    return false;
}

void UnitData::setUnit(unsigned int unit_id)
{
    data_ = DataManager::Inst().getUnit(unit_id);

    if (m_readableName.empty()) {
        m_readableName = data_.Name;
    }
    if (m_readableName.empty()) {
        m_readableName = data_.Name2;
    }
}

const genie::Unit &UnitData::getData(void) const
{
    return data_;
}

std::string UnitData::readableName()
{
    return m_readableName;
}

}
