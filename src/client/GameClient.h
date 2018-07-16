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

#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <map>
#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <global/Logger.h>

struct Unit;
class RenderGame;
class TunnelToServer;
class GameClient
{

public:
    GameClient();
    virtual ~GameClient();

    void setServer(TunnelToServer *server);

    void setGameRenderer(RenderGame *game_renderer);

    void update();

    void selectUnit(Unit *unit);
    void moveSelectedTo(sf::Vector2f pos);

    void test();

private:
    GameClient(const GameClient &other);

    TunnelToServer *server_;

    RenderGame *game_renderer_;

    typedef std::map<sf::Uint32, Unit *> UnitMap;
    UnitMap units_;

    Unit *selected_unit_;
};

#endif // GAMECLIENT_H
