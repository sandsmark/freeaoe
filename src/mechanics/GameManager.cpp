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


#include "GameManager.h"

#include <mechanics/Unit.h>
#include <render/RenderGame.h>
#include "ICommand.h"

GameManager::GameManager() : unit_id_counter_(0), game_renderer_(0)
{

}

GameManager::GameManager(const GameManager& other)
{

}

GameManager::~GameManager()
{

}

Unit* GameManager::createUnit()
{
  Unit *unit = new Unit(unit_id_counter_ ++);
  units_[unit_id_counter_] = unit;
  
  if (game_renderer_)
    game_renderer_->addUnit(unit);
  
  return unit;
}

void GameManager::setGameRenderer(RenderGame* game_renderer)
{
  game_renderer_ = game_renderer;
}

void GameManager::queueCommand(ICommand* cmd)
{
  // TODO: queue it!
  cmd->execute(this);
}

void GameManager::update()
{

}

