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

#pragma once

#include <SFML/Config.hpp>
#include <map>
#include <vector>
#include <global/Types.h>

class IAction;

struct Unit;

class TunnelToClient;

class GameServer
{

public:
    GameServer (const GameServer &) = delete;
    GameServer &operator=(const GameServer&) = delete;

    GameServer();
    virtual ~GameServer();

    void addClient(TunnelToClient *client);

    void update(void);

    Unit *createUnit(void);

    Unit *getUnit(sf::Uint32 unit_id);

    //----------------------------------------------------------------------------
    ///
    /// @param unit_id Id of the unit in dat file.
    //
    bool spawnUnit(void *player, sf::Uint32 unit_id, MapPos pos);

    bool addAction(IAction *act);

private:
    sf::Uint32 unit_id_counter_;

    typedef std::map<sf::Uint32, Unit *> UnitMap;
    UnitMap units_;

    typedef std::vector<IAction *> ActionArray;
    ActionArray actions_;

    TunnelToClient *client_;
};

