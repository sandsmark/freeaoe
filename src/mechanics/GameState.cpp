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

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Mouse.hpp>
#include <communication/commands/CommandSpawn.h>
#include <server/GameServer.h>
#include <client/GameClient.h>
#include <communication/tunnels/LocalTunnelToServer.h>
#include <communication/tunnels/LocalTunnelToClient.h>

#include <iostream>
#include <render/GraphicRender.h>
#include "EntityFactory.h"
#include <Engine.h>
#include "render/MapRenderer.h"
#include "render/SfmlRenderTarget.h"

GameState::GameState(IRenderTargetPtr renderTarget)
{
    renderTarget_ = renderTarget;
}

GameState::GameState(const GameState &other)
{
}

GameState::~GameState()
{
}

void GameState::setScenario(std::shared_ptr<genie::ScnFile> scenario)
{
    scenario_ = scenario;
}

void GameState::init()
{
    IState::init();

    entity_form_manager_.setRenderTarget(renderTarget_);

    //TODO: Test

    EntityPtr unit = EntityFactory::Inst().createUnit(531);

    //   entity_manager_.add(unit);
    //   entity_form_manager_.createForms(unit);

    //Map test
    map_ = MapPtr(new Map());

    if (scenario_.get())
        map_->create(scenario_->map);
    else
        map_->setUpSample();

    camera_ = CameraPtr(new Camera());

    mapRenderer_.setRenderTarget(renderTarget_);
    mapRenderer_.setMap(map_);
    mapRenderer_.setCamera(camera_);

    /*
  EntityForm form;
  
  comp::GraphicPtr g = comp::Graphic::create(881);
  
  form.addComponent(comp::GRAPHIC, g);
 
  entity_form_manager_.add(form);
  
  */
    //-------------

    /*    game_server_ = new GameServer();
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
    */
}

void GameState::draw()
{
    //map_->draw(render_target_);
    //std::cout << map_form_->getComponent<comp::MapRender>(comp::MAP_RENDER).get() << std::endl;

    mapRenderer_.display();
    entity_form_manager_.display();
}

void GameState::update()
{
    mapRenderer_.update(Engine::GameClock.getElapsedTime().asMilliseconds());

    entity_manager_.update(Engine::GameClock.getElapsedTime().asMilliseconds());
    entity_form_manager_.update(Engine::GameClock.getElapsedTime().asMilliseconds());

    //game_server_->update();
    //game_client_->update();
}

void GameState::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        ScreenPos p;
        p.x = event.mouseButton.x;
        p.y = event.mouseButton.y;

        MapPos m = MapRenderer::screenToMapPos(p);
        MapPos absM = mapRenderer_.getMapPosition(p);

        std::cout << "Screenpos: (" << p.x << ", " << p.y << ")" << std::endl;
        std::cout << "Mappos   : (" << m.x << ", " << m.y << ")" << std::endl;
        std::cout << "Abs mpos : (" << absM.x << ", " << absM.y << ", " << absM.z << ")" << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;

        camera_->setTargetPosition(absM);
    }
}
