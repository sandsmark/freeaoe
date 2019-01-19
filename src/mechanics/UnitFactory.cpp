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
#include "Building.h"
#include "UnitManager.h"

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

Unit::Ptr UnitFactory::createUnit(const int ID, const MapPos &position, const Player::Ptr &owner, UnitManager &unitManager)
{
    const genie::Unit &gunit = owner->civ->unitData(ID);

    Unit::Ptr unit;
    if (ID == Unit::Farm) {
        unit = std::make_shared<Farm>(gunit, owner, unitManager);
    } else if (gunit.Type == genie::Unit::BuildingType) {
        unit = std::make_shared<Building>(gunit, owner, unitManager);
    } else {
        unit = std::make_shared<Unit>(gunit, owner, unitManager);
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
            const genie::Unit &stackData = owner->civ->unitData(gunit.Building.StackUnitID);

            Unit::Annex annex;
            annex.unit = std::make_shared<Unit>(stackData, owner, unitManager);
            annex.unit->setPosition(position + annex.offset);
            unit->annexes.push_back(annex);
        }

        for (const genie::unit::BuildingAnnex &annexData : gunit.Building.Annexes) {
            if (annexData.UnitID < 0) {
                continue;
            }
            const genie::Unit &gunit = owner->civ->unitData(annexData.UnitID);

            Unit::Annex annex;
            annex.offset = MapPos(annexData.Misplacement.first * -48, annexData.Misplacement.second * -48);
            annex.unit = std::make_shared<Unit>(gunit, owner, unitManager);
            annex.unit->setPosition(position + annex.offset);
            unit->annexes.push_back(annex);
        }

        if (!unit->annexes.empty()) {
            std::reverse(unit->annexes.begin(), unit->annexes.end());
        }
    }

    unitManager.add(unit);

    return unit;
}
