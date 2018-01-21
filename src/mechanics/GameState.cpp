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

#include <genie/resource/Color.h>

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
#include "CompUnitData.h"

#define MOUSE_MOVE_EDGE_SIZE 100
#define CAMERA_SPEED 1.

GameState::GameState(IRenderTargetPtr renderTarget) :
    m_cameraDeltaX(0),
    m_cameraDeltaY(0),
    m_lastUpdate(0)
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


    //Map test
    map_ = MapPtr(new Map());

    if (scenario_.get()) {
        std::cout << "Setting up scenario: " << scenario_->scenarioInstructions << std::endl;
        map_->create(scenario_->map);

        for (genie::ScnPlayerUnits &units : scenario_->playerUnits) {
            for (const genie::ScnUnit &scnunit : units.units) {
                EntityPtr unit = EntityFactory::Inst().createUnit(scnunit.objectID, MapPos(scnunit.positionX * Map::TILE_SIZE, scnunit.positionY * Map::TILE_SIZE, scnunit.positionZ));
                entity_manager_.add(unit);
                entity_form_manager_.createForms(unit);
            }
        }

        EntityPtr unit = EntityFactory::Inst().createUnit(293, MapPos(48*3, 48*3, 0));
        entity_manager_.add(unit);
        entity_form_manager_.createForms(unit);
    } else {
        map_->setUpSample();


        EntityPtr unit = EntityFactory::Inst().createUnit(109, MapPos(48*3, 48*3, 0));
        comp::UnitDataPtr gunit = unit->getComponent<comp::UnitData>(comp::UNIT_DATA);

        if (gunit->getData().Building.FoundationTerrainID > 0) {
            int width = gunit->getData().CollisionSize.x;
            int height = gunit->getData().CollisionSize.y;
            for (int x = 0; x < width*2; x++) {
                for (int y = 0; y < height*2; y++) {
                    map_->setTileAt(3 - width + x, 3 - height + y, gunit->getData().Building.FoundationTerrainID);
                }
            }
        }
        entity_manager_.add(unit);
        entity_form_manager_.createForms(unit);
    }

    mapRenderer_.setRenderTarget(renderTarget_);
    mapRenderer_.setMap(map_);

    entity_manager_.setMap(map_);

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

    if (m_selectionShape) {
        renderTarget_->draw(*m_selectionShape);
    }
}

bool GameState::update(Time time)
{
    bool updated = false;
    updated = mapRenderer_.update(time) || updated;

    updated = entity_manager_.update(time) || updated;
    updated = entity_form_manager_.update(time) || updated;

    if (m_cameraDeltaX != 0 || m_cameraDeltaY != 0) {
        const int deltaTime = time - m_lastUpdate;

        ScreenPos cameraScreenPos = renderTarget_->camera()->getTargetPosition().toScreen();
        cameraScreenPos.x += m_cameraDeltaX * deltaTime * CAMERA_SPEED;
        cameraScreenPos.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;

        MapPos cameraMapPos = cameraScreenPos.toMap();
        if (cameraMapPos.x < 0) cameraMapPos.x = 0;
        if (cameraMapPos.y < 0) cameraMapPos.y = 0;
        if (cameraMapPos.x > map_->width()) cameraMapPos.x = map_->width();
        if (cameraMapPos.y > map_->height()) cameraMapPos.y = map_->height();
        renderTarget_->camera()->setTargetPosition(cameraMapPos);


        if (m_selectionShape) {
            m_selectionStart.x -= m_cameraDeltaX * deltaTime * CAMERA_SPEED;
            m_selectionStart.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;
        }

        updated = true;
    }

    if (m_selectionShape) {
        ScreenRect selectionRect(m_selectionStart, m_selectionCurr);
        if (selectionRect.topLeft() != m_selectionShape->getPosition()) {
            m_selectionShape->setPosition(selectionRect.topLeft());
            updated = true;
        }

        sf::Vector2f size(selectionRect.width, selectionRect.height);
        if (size != m_selectionShape->getSize()) {
            m_selectionShape->setSize(size);
            updated = true;
        }
    }

    m_lastUpdate = time;

    //game_server_->update();
    //game_client_->update();

    return updated;
}

void GameState::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::MouseMoved) {
        if (event.mouseMove.x < MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaX = -1;
        } else if (event.mouseMove.x > renderTarget_->getSize().x - MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaX = 1;
        } else {
            m_cameraDeltaX = 0;
        }

        if (event.mouseMove.y < MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaY = 1;
        } else if (event.mouseMove.y > renderTarget_->getSize().y - MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaY = -1;
        } else {
            m_cameraDeltaY = 0;
        }

        if (m_selectionShape) {
            m_selectionCurr = ScreenPos(event.mouseMove.x, event.mouseMove.y);
        }

        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        ScreenPos cameraScreenPos = renderTarget_->camera()->getTargetPosition().toScreen();


        switch(event.key.code) {
        case sf::Keyboard::Left:
            cameraScreenPos.x -= 20;
            break;

        case sf::Keyboard::Right:
            cameraScreenPos.x += 20;
            break;

        case sf::Keyboard::Down:
            cameraScreenPos.y += 20;
            break;

        case sf::Keyboard::Up:
            cameraScreenPos.y -= 20;
            break;

        default:
            return;
        }

        MapPos cameraMapPos = cameraScreenPos.toMap();
        if (cameraMapPos.x < 0) cameraMapPos.x = 0;
        if (cameraMapPos.y < 0) cameraMapPos.y = 0;
        if (cameraMapPos.x > map_->width()) cameraMapPos.x = map_->width();
        if (cameraMapPos.y > map_->height()) cameraMapPos.y = map_->height();
        renderTarget_->camera()->setTargetPosition(cameraMapPos);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        m_selectionShape = std::make_shared<sf::RectangleShape>();
        m_selectionShape->setFillColor(sf::Color::Transparent);
        m_selectionShape->setOutlineColor(sf::Color::White);
        m_selectionShape->setOutlineThickness(1);

        m_selectionStart = ScreenPos(event.mouseButton.x, event.mouseButton.y);
        m_selectionCurr = ScreenPos(event.mouseButton.x, event.mouseButton.y);
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        ScreenPos p;
        p.x = event.mouseButton.x;
        p.y = event.mouseButton.y;

        MapPos m = p.toMap();
        MapPos absM = mapRenderer_.getMapPosition(p);

        ScreenPos absPos = renderTarget_->absoluteScreenPos(absM);

        ScreenPos screenCenter;
        screenCenter.x = renderTarget_->getSize().x / 2.0;
        screenCenter.y = renderTarget_->getSize().y / 2.0;
        MapPos cameraOffset = renderTarget_->camera()->getTargetPosition() - screenCenter.toMap();

        std::cout << "Screenpos: (" << p.x << ", " << p.y << ")" << std::endl;
        std::cout << "Mappos   : (" << m.x << ", " << m.y << ")" << std::endl;
        std::cout << "Abs mpos : (" << absM.x << ", " << absM.y << ", " << absM.z << ")" << std::endl;
        std::cout << "Abs spos : (" << absPos.x << ", " << absPos.y << ")" << std::endl;
        std::cout << "Camera offset: (" << cameraOffset.x << ", " << cameraOffset.y << ")" << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;

        if (m_selectionShape) {
            ScreenRect selectionRect(m_selectionStart, m_selectionCurr);
            MapRect mapSelectionRect = renderTarget_->absoluteMapRect(selectionRect);
            entity_manager_.selectEntities(mapSelectionRect);

            m_selectionShape.reset();
        }

        if (event.mouseButton.button == sf::Mouse::Button::Right) {
            entity_manager_.onRightClick(renderTarget_->absoluteMapPos(ScreenPos(event.mouseButton.x, event.mouseButton.y)));
        }
    }
}
