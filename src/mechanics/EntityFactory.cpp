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

EntityFactory& EntityFactory::Inst()
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

std::shared_ptr< Entity > EntityFactory::createUnit(int ID)
{
  //genie::Unit gunit = DataManager::Inst().getUnit(ID);
  
  EntityPtr entity(new Entity());
  
  //std::cout << gunit.Name << std::endl;
  
  comp::MapObjectPtr mo(new comp::MapObject());
  mo->setPos(MapPos(500,100,0));
  
  entity->addComponent(comp::MAP_OBJECT, mo);
  
  comp::UnitDataPtr gunit(new comp::UnitData());
  gunit->setUnit(ID);
  
  entity->addComponent(comp::UNIT_DATA, gunit);
  
  ActionPtr act(new act::MoveOnMap(entity, MapPos(300,20,0)));
  
  entity->current_action_ = act;
  
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


