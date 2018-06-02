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

#include "EntityFactory.h"
#include <genie/dat/Unit.h>
#include <resource/DataManager.h>
#include <global/Constants.h>
#include "CompMapObject.h"
#include "CompUnitData.h"
#include "ActionMove.h"

using std::shared_ptr;

UnitFactory &UnitFactory::Inst()
{
    static UnitFactory inst;
    return inst;
}

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

Unit::Ptr UnitFactory::createUnit(int ID, const MapPos &position, int playerId, Civilization::Ptr civ)
{
    std::cout << "Creating  " << ID << std::endl;
    const genie::Unit &gunit = DataManager::Inst().getUnit(ID);

    Unit::Ptr unit = std::make_shared<Unit>(gunit, playerId, civ);
    unit->position = position;

    if (gunit.Type >= genie::Unit::BuildingType) {
        if (gunit.Building.StackUnitID >= 0) {
            Unit::Annex annex;
            annex.unit = createUnit(gunit.Building.StackUnitID, position, playerId, civ);
            unit->annexes.push_back(annex);
        }

        for (const genie::unit::BuildingAnnex &annexData : gunit.Building.Annexes) {
            if (annexData.UnitID < 0) {
                continue;
            }

            Unit::Annex annex;
            annex.offset = MapPos(annexData.Misplacement.first * -48, annexData.Misplacement.second * -48);
            annex.unit = createUnit(annexData.UnitID, position, playerId, civ);
            unit->annexes.push_back(annex);
        }

        if (!unit->annexes.empty()) {
            std::reverse(unit->annexes.begin(), unit->annexes.end());
        }
    }

    return unit;
}
