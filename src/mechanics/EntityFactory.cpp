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

EntityFactory &EntityFactory::Inst()
{
    static EntityFactory inst;
    return inst;
}

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

std::shared_ptr<Entity> EntityFactory::createUnit(int ID, const MapPos &position)
{
    const genie::Unit &gunit = DataManager::Inst().getUnit(ID);

    EntityPtr entity = std::make_shared<Unit>(gunit, 0);
    entity->position = position;

    if (gunit.Type >= genie::Unit::BuildingType) {
        for (const genie::unit::BuildingAnnex &annexData : gunit.Building.Annexes) {
            if (annexData.UnitID < 0) {
                continue;
            }

            Entity::Annex annex;
            annex.offset = MapPos(annexData.Misplacement.first * -48, annexData.Misplacement.second * -48);
            annex.entity = createUnit(annexData.UnitID, position);
            entity->annexes.push_back(annex);
        }

        if (!entity->annexes.empty()) {
            std::reverse(entity->annexes.begin(), entity->annexes.end());
        }
    }

    //std::cout << gunit.Name << std::endl;

//    int width = gunit->getData().CollisionSize.x * Map::TILE_SIZE;
//    int height = gunit->getData().CollisionSize.y * Map::TILE_SIZE;
//    MapRect unitRect(position.x, position.y, width, height);
//    mo->setRect(unitRect);

//    ActionPtr act(new act::MoveOnMap(entity, MapPos(48 * 4, 48 * 2, 0)));

//    entity->current_action_ = act;

    /*  entity->addAttribute(attr::id::NAME,
    shared_ptr< attr::String > (new attr::String(gunit.Name)) 
  );
  
  entity->addAttribute(attr::id::MAP_3D_POS, 
    shared_ptr< attr::Map3DPos > (new attr::Map3DPos()) 
  );
  
  
  if (gunit.getType() >= genie::UT_Bird && 
      gunit.getType() <= genie::UT_Creatable)
    entity->addAttribute(attr::id::MOVABLE, 
      shared_ptr< attr::Movable > (new attr::Movable()) 
    );
  
  
  if (gunit.SelectionShape == 0)
    entity->addAttribute(attr::id::LOGICAL_SHAPE, 
      shared_ptr< attr::LogicalShape> (new attr::LogicalShape(
        attr::Rectangle(gunit.SizeRadius.first * cnst::TILE_SIZE, gunit.SizeRadius.second * cnst::TILE_SIZE)))
    );
  else
    entity->addAttribute(attr::id::LOGICAL_SHAPE, 
      shared_ptr< attr::LogicalShape> (new attr::LogicalShape(
        attr::Circle(gunit.SizeRadius.first * cnst::TILE_SIZE)))
    );*/

    return entity;
}
