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
#include <communication/UnitData.h>
#include <mechanics/Unit.h>
#include <data/DataManager.h>
#include <render/RenderGame.h>

#include <iostream>

GameClient::GameClient() : game_renderer_(0)
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
    UnitData *data = server_->getData();
    
    Unit *unit = new Unit(data->id_);
    unit->setData(DataManager::Inst()->getUnit(data->data_id_));
    unit->setPos(data->x_pos_, data->y_pos_);
    
    units_[data->id_] = unit;
    
    if (game_renderer_)
      game_renderer_->addUnit(unit);
  }
}


void GameClient::test()
{
  server_->sendCommand(new CommandSpawn(0, 234, 100, 200));
  server_->sendCommand(new CommandSpawn(0, 281, 90, 210));
}
