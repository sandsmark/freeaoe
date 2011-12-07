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


#include "GameClient.h"
#include <communication/TunnelToServer.h>
#include <communication/commands/CommandSpawn.h>
#include <communication/UnitStatus.h>
#include <mechanics/Unit.h>
#include <resource/DataManager.h>
#include <render/RenderGame.h>

#include <iostream>
#include <communication/commands/CommandMove.h>

Logger& GameClient::log = Logger::getLogger("freeaoe.client.GameClient");

GameClient::GameClient() : game_renderer_(0), selected_unit_(0)
{

}

GameClient::GameClient(const GameClient& other)
{

}

GameClient::~GameClient()
{

}

void GameClient::setServer(TunnelToServer* server)
{
  server_ = server;
}

void GameClient::setGameRenderer(RenderGame* game_renderer)
{
  game_renderer_ = game_renderer;
}

void GameClient::update()
{ 
  while (server_->dataAvailable())
  {
    UnitStatus data = server_->getData();
    
    if (units_.find(data.getID()) != units_.end())
    {
      Unit *unit = units_[data.getID()];
      
      unit->setPos(data.getPos());
    }
    else
    {
      Unit *unit = new Unit(data.getID());
      unit->setData(DataManager::Inst().getUnit(data.getDataID()));
      unit->setPos(data.getPos());
    
      units_[data.getID()] = unit;
    
      if (game_renderer_)
        game_renderer_->addUnit(unit);
    }
  }
}

void GameClient::selectUnit(Unit* unit)
{
  selected_unit_ = unit;
}

void GameClient::moveSelectedTo(sf::Vector2f pos)
{
  if (!selected_unit_)
    log.warn("No unit selected to move");
  else
    server_->sendCommand(new CommandMove(selected_unit_->getID(), pos));
}


void GameClient::test()
{
  server_->sendCommand(new CommandSpawn(0, 234, MapPos(175, 230)));
  server_->sendCommand(new CommandSpawn(0, 281, MapPos(190, 360)));
  server_->sendCommand(new CommandSpawn(0, 281, MapPos(300, 250)));
  
 // server_->sendCommand(new CommandMove(2, 500,300));
}
