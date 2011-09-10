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


#include "GameServer.h"
#include <communication/TunnelToClient.h>
#include <mechanics/Unit.h>
#include <data/DataManager.h>
#include <communication/UnitStatus.h>
#include <mechanics/IAction.h>
#include <SFML/System/Clock.hpp>

GameServer::GameServer() : unit_id_counter_ (0)
{

}

GameServer::GameServer (const GameServer& other)
{

}

GameServer::~GameServer()
{

}

void GameServer::addClient (TunnelToClient* client)
{
  client_ = client;
}

void GameServer::update()
{
  static sf::Clock clock;

  if (clock.GetElapsedTime() > 150)
  {

    while (client_->commandAvailable())
    {
      client_->getCommand()->execute (this);
    }

    clock.Reset();
  }

  for (ActionArray::iterator it = actions_.begin(); it != actions_.end(); it ++)
  {
    (*it)->update();
    client_->sendData ((*it)->getUnit()->getStatus());
  }


}

//------------------------------------------------------------------------------
bool GameServer::addAction (IAction* act)
{
  actions_.push_back (act);
}

//------------------------------------------------------------------------------
Unit* GameServer::getUnit (Uint32 unit_id)
{
  return units_[unit_id];
}

//------------------------------------------------------------------------------
bool GameServer::spawnUnit (void* player, sf::Uint32 unit_id, MapPos pos) 
{
  Unit *unit = new Unit (unit_id_counter_);
  units_[unit_id_counter_] = unit;

  unit->setPos (pos);

  unit->setData (DataManager::Inst()->getUnit (unit_id));

  client_->sendData (unit->getStatus());

  unit_id_counter_ ++;

  return true;
}

