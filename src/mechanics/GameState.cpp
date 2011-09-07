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


#include "GameState.h"

#include "render/RenderGame.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <communication/commands/CommandSpawn.h>
#include <server/GameServer.h>
#include <client/GameClient.h>
#include <communication/tunnels/LocalTunnelToServer.h>
#include <communication/tunnels/LocalTunnelToClient.h>


void GameState::init()
{
    IState::init();
    
    
    game_renderer_ = new RenderGame(render_target_);
    game_server_ = new GameServer();
    game_client_ = new GameClient();
    
    game_client_->setGameRenderer(game_renderer_);
    
    // Creating local connection
    LocalTunnelToServer *tToServ = new LocalTunnelToServer();
    LocalTunnelToClient *tToClient = new LocalTunnelToClient();
    
    tToServ->setServer(tToClient);
    tToClient->setClient(tToServ);
    
    game_server_->addClient(tToClient);
    game_client_->setServer(tToServ);
    
    //Test
    game_client_->test();
}


void GameState::draw()
{ 
  game_renderer_->draw();
}

void GameState::update()
{
  game_server_->update();
  game_client_->update();
}

void GameState::handleEvent(sf::Event event)
{

}

GameState::GameState(sf::RenderTarget *render_target) 
            : render_target_(render_target)
{

}

GameState::GameState(const GameState& other)
{

}

GameState::~GameState()
{
  delete game_renderer_;
}

