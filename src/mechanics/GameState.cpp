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
#include "resource/DataManager.h"

#define MOUSE_MOVE_EDGE_SIZE 10
#define CAMERA_SPEED 1.

Logger& GameState::log = Logger::getLogger("freeaoe.GameState");

GameState::GameState(std::shared_ptr<SfmlRenderTarget> renderTarget) :
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

    std::shared_ptr<genie::SlpFile> overlayFile = ResourceManager::Inst()->getUiOverlay(ResourceManager::Ui1280x1024, ResourceManager::Viking);
    if (overlayFile) {
        m_uiOverlay.loadFromImage(res::Resource::convertFrameToImage(overlayFile->getFrame()));
        log.info("Loaded UI overlay with size %dx%d", m_uiOverlay.getSize().x, m_uiOverlay.getSize().y);
    } else {
        m_uiOverlay = sf::Texture();
        log.error("Failed to load ui overlay");
    }

    m_cursors = ResourceManager::Inst()->getSlp(51000);
    if (m_cursors) {
        m_cursorTexture.loadFromImage(res::Resource::convertFrameToImage(m_cursors->getFrame(0)));
        m_cursor.setTexture(m_cursorTexture);
    } else {
        log.error("Failed to get cursors");
    }

    const std::vector<genie::Civ> &civilizations = DataManager::Inst().civilizations();
    for (int i=0; i<civilizations.size(); i++) {
        m_civilizations.push_back(std::make_shared<Civilization>(i, DataManager::Inst().datFile()));
    }

    m_unitIconsSlp = ResourceManager::Inst()->getSlp(50730);
    if (!m_unitIconsSlp) {
        std::cerr << "Failed to load icons" << std::endl;
    }

    m_buildingIconsSlp = ResourceManager::Inst()->getSlp(50705);
    if (!m_buildingIconsSlp) {
        std::cerr << "Failed to load icons" << std::endl;
    }


    //Map test
    map_ = MapPtr(new Map());

    if (scenario_.get()) {
        std::cout << "Setting up scenario: " << scenario_->scenarioInstructions << std::endl;
        map_->create(scenario_->map);

        for (genie::ScnPlayerUnits &units : scenario_->playerUnits) {
            for (const genie::ScnUnit &scnunit : units.units) {
                EntityPtr unit = EntityFactory::Inst().createUnit(scnunit.objectID, MapPos(scnunit.positionX * Map::TILE_SIZE, scnunit.positionY * Map::TILE_SIZE, scnunit.positionZ));
                entity_manager_.add(unit);
            }
        }

        EntityPtr unit = EntityFactory::Inst().createUnit(293, MapPos(48*3, 48*3, 0));
        entity_manager_.add(unit);
    } else {
        map_->setUpSample();

        EntityPtr unit = EntityFactory::Inst().createUnit(293, MapPos(48*3, 48*3, 0));
        entity_manager_.add(unit);

        unit = EntityFactory::Inst().createUnit(109, MapPos(48*3, 48*3, 0));

        if (unit->data.Building.FoundationTerrainID > 0) {
            int width = unit->data.CollisionSize.x;
            int height = unit->data.CollisionSize.y;
            for (int x = 0; x < width*2; x++) {
                for (int y = 0; y < height*2; y++) {
                    map_->setTileAt(3 - width + x, 3 - height + y, unit->data.Building.FoundationTerrainID);
                }
            }
        }

        entity_manager_.add(unit);
    }

    map_->updateMapData();
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
    entity_manager_.render(renderTarget_);

    if (m_selectionRect) {
        renderTarget_->draw(m_selectionRect, sf::Color::Transparent, sf::Color::White);
    }

    renderTarget_->draw(m_uiOverlay, ScreenPos(0, 0));

    for (const Button &button : m_currentIcons) {
        ScreenPos position;
        position.x = button.pos % 5;
        position.x = (position.x + 1) * 40;
        position.y = button.pos / 5;
        position.y *= 40;
        position.y += m_uiOverlay.getSize().y  - 40 * 4;
        renderTarget_->draw(button.tex, position);
    }

    renderTarget_->renderTarget_->draw(m_cursor);
}

bool GameState::update(Time time)
{
    bool updated = false;
    updated = mapRenderer_.update(time) || updated;

    updated = entity_manager_.update(time) || updated;

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


        if (m_selectionRect) {
            m_selectionStart.x -= m_cameraDeltaX * deltaTime * CAMERA_SPEED;
            m_selectionStart.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;
        }

        updated = true;
    }

    if (m_selectionRect) {
        ScreenRect selectionRect(m_selectionStart, m_selectionCurr);
        if (selectionRect != m_selectionRect) {
            m_selectionRect = selectionRect;
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
        m_cursor.setPosition(event.mouseMove.x, event.mouseMove.y);

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

        if (m_selectionRect) {
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
            cameraScreenPos.y -= 20;
            break;

        case sf::Keyboard::Up:
            cameraScreenPos.y += 20;
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
        m_selectionStart = ScreenPos(event.mouseButton.x, event.mouseButton.y);
        m_selectionCurr = ScreenPos(event.mouseButton.x+1, event.mouseButton.y+1);
        m_selectionRect = ScreenRect(m_selectionStart, m_selectionCurr);
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            MapRect mapSelectionRect = renderTarget_->absoluteMapRect(m_selectionRect);
            entity_manager_.selectEntities(mapSelectionRect);
            m_selectionRect = ScreenRect();

            if (!entity_manager_.selected().empty()) {
                EntityPtr entity = *entity_manager_.selected().begin();
                m_currentIcons.clear();
                for (const genie::Unit *creatable : m_civilizations[0]->creatableUnits(entity->data.ID)) {
                    if (creatable->IconID >= m_unitIconsSlp->getFrameCount()) {
                        std::cerr << "invalid icon id: " << creatable->IconID << std::endl;
                    }

                    Button button;
                    if (entity->data.InterfaceKind == genie::Unit::CiviliansInterface) {
                        button.tex.loadFromImage(res::Resource::convertFrameToImage(m_buildingIconsSlp->getFrame(creatable->IconID)));
                    } else {
                        button.tex.loadFromImage(res::Resource::convertFrameToImage(m_unitIconsSlp->getFrame(creatable->IconID)));
                    }
                    button.pos = std::max(creatable->Creatable.ButtonID - 1, 0);

                    m_currentIcons.push_back(button);

                }
            }
        }

        if (event.mouseButton.button == sf::Mouse::Button::Right) {
            entity_manager_.onRightClick(renderTarget_->absoluteMapPos(ScreenPos(event.mouseButton.x, event.mouseButton.y)));
        }
    }
}

Size GameState::uiSize() const
{
    if (m_uiOverlay.getSize().x == 0 || m_uiOverlay.getSize().y == 0) {
        log.error("We don't have a valid UI overlay");
        return Size(640, 480);
    }
    return m_uiOverlay.getSize();
}
