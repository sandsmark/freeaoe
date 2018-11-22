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

#include "UnitFactory.h"
#include "resource/DataManager.h"
#include "core/Constants.h"
#include "actions/ActionMove.h"
#include "Farm.h"
#include "Civilization.h"

#include <genie/dat/Unit.h>


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

Unit::Ptr UnitFactory::createUnit(int ID, const MapPos &position, const Player::Ptr &owner, const MapPtr &map)
{
    const genie::Unit &gunit = DataManager::Inst().getUnit(ID);

    Unit::Ptr unit;
    if (ID == Unit::Farm) {
        unit = std::make_shared<Farm>(gunit, owner, owner->civ, map);
    } else {
        unit = std::make_shared<Unit>(gunit, owner, owner->civ, map);
    }

    unit->setPosition(position);

    for (const genie::Unit::ResourceStorage &res : gunit.ResourceStorages) {
        if (res.Type == -1) {
            continue;
        }

        unit->resources[genie::ResourceType(res.Type)] = res.Amount;

    }

    if (gunit.Class == genie::Unit::Farm) {
        unit->resources[genie::ResourceType::FoodStorage] = owner->civ->startingResource(genie::ResourceType::FarmFoodAmount);

    }

    if (gunit.Type >= genie::Unit::BuildingType) {
        unit->snapPositionToGrid();

        if (gunit.Building.StackUnitID >= 0) {
            Unit::Annex annex;
            annex.unit = createUnit(gunit.Building.StackUnitID, position, owner, map);
            unit->annexes.push_back(annex);
        }

        for (const genie::unit::BuildingAnnex &annexData : gunit.Building.Annexes) {
            if (annexData.UnitID < 0) {
                continue;
            }

            Unit::Annex annex;
            annex.offset = MapPos(annexData.Misplacement.first * -48, annexData.Misplacement.second * -48);
            annex.unit = createUnit(annexData.UnitID, position + annex.offset, owner, map);
            unit->annexes.push_back(annex);
        }

        if (!unit->annexes.empty()) {
            std::reverse(unit->annexes.begin(), unit->annexes.end());
        }
    }

    return unit;
}
