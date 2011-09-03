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


#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>

#include <SFML/Config.hpp>

class RenderGame;
class ICommand;
class Unit;
class GameManager
{

public:
  GameManager();
  virtual ~GameManager();
  
  /// Note: Manager will free command (Todo: auto_ptr)
  /// Queues a command and executes it on the next update call
  //
  void queueCommand(ICommand *cmd);
  
  void update();
  
  //----------------------------------------------------------------------------
  /// Creates a new unit, adds it to the map of existing ones and returns a
  /// pointer to it.
  //
  Unit *createUnit();
  
  void setGameRenderer(RenderGame *game_renderer);

private:
  GameManager(const GameManager& other);
  
  sf::Uint32 unit_id_counter_;
  
  typedef std::map<sf::Uint32, Unit *> UnitMap;
  UnitMap units_;
  
  RenderGame *game_renderer_;
};

#endif // GAMEMANAGER_H
