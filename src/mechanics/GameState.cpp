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
#include "UnitFactory.h"
#include <Engine.h>
#include "render/MapRenderer.h"
#include "render/SfmlRenderTarget.h"
#include "CompUnitData.h"
#include "resource/DataManager.h"
#include "render/ActionPanel.h"
#include "global/Constants.h"

#define MOUSE_MOVE_EDGE_SIZE 10
#define CAMERA_SPEED 1.

GameState::GameState(std::shared_ptr<SfmlRenderTarget> renderTarget) :
    m_cameraDeltaX(0),
    m_cameraDeltaY(0),
    m_lastUpdate(0)
{
    m_unitManager = std::make_shared<UnitManager>();
    renderTarget_ = renderTarget;

    m_actionPanel = std::make_unique<ActionPanel>(renderTarget_);
    m_actionPanel->setUnitManager(m_unitManager);
}

GameState::~GameState()
{
}

void GameState::setScenario(std::shared_ptr<genie::ScnFile> scenario)
{
    scenario_ = scenario;
}

bool GameState::init()
{
    if (!m_unitManager->init()) {
        return false;
    }

    if (!m_actionPanel->init()) {
        return false;
    }


    std::shared_ptr<genie::SlpFile> overlayFile = ResourceManager::Inst()->getUiOverlay(ResourceManager::Ui1280x1024, ResourceManager::Viking);
    if (overlayFile) {
        m_uiOverlay.loadFromImage(res::Resource::convertFrameToImage(overlayFile->getFrame()));
        DBG << "Loaded UI overlay with size" << Size(m_uiOverlay.getSize());
    } else {
        ResourceManager::UiResolution attemptedResolution = ResourceManager::Ui1280x1024;
        ResourceManager::UiCiv attemptedCiv = ResourceManager::Briton;
        do {
            attemptedCiv = ResourceManager::UiCiv(attemptedCiv + 1);
            if (attemptedCiv > ResourceManager::Korean) {
                if (attemptedResolution == ResourceManager::Ui1280x1024) {
                    attemptedResolution = ResourceManager::Ui1024x768;
                } else if (attemptedResolution == ResourceManager::Ui1024x768) {
                    attemptedResolution = ResourceManager::Ui800x600;
                } else {
                    m_uiOverlay = sf::Texture();
                    break;
                }

                attemptedCiv = ResourceManager::Briton;
            }
            overlayFile = ResourceManager::Inst()->getUiOverlay(attemptedResolution, attemptedCiv);
        } while (!overlayFile);

        if (overlayFile) {
            WARN << "Loaded fallback ui overlay res" << attemptedResolution << "for civ" << attemptedCiv;
            m_uiOverlay.loadFromImage(res::Resource::convertFrameToImage(overlayFile->getFrame()));
        } else {
            WARN << "Failed to load ui overlay";
        }
    }

    m_mouseCursor.cursorsFile = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("mcursors.shp"));
    if (m_mouseCursor.cursorsFile) {
        m_mouseCursor.texture.loadFromImage(res::Resource::convertFrameToImage(m_mouseCursor.cursorsFile->getFrame(Cursor::Normal)));
        m_mouseCursor.sprite.setTexture(m_mouseCursor.texture);
    } else {
        WARN << "Failed to get cursors";
    }

    // graphic 2962
    m_waypointFlag = ResourceManager::Inst()->getSlp(3404);
    if (!m_waypointFlag) {
        WARN << "Failed to load waypoint animation";
    }

    const std::vector<genie::Civ> &civilizations = DataManager::Inst().civilizations();
    for (int i=0; i<civilizations.size(); i++) {
        m_civilizations.push_back(std::make_shared<Civilization>(i, DataManager::Inst().datFile()));
    }
    if (m_civilizations.empty()) {
        WARN << "Failed to load any civilizations";
        return false;
    }

    //Map test
    map_ = MapPtr(new Map());

    if (scenario_) {
        DBG << "Setting up scenario:" << scenario_->scenarioInstructions;
        map_->create(scenario_->map);

        for (int playerNum = 0; playerNum < scenario_->playerUnits.size(); playerNum++) {
            Player::Ptr player = std::make_shared<Player>(playerNum, m_civilizations[0]);
            m_players.push_back(player);
            for (const genie::ScnUnit &scnunit : scenario_->playerUnits[playerNum].units) {
                MapPos unitPos(scnunit.positionX * Constants::TILE_SIZE, scnunit.positionY * Constants::TILE_SIZE, scnunit.positionZ);
                Unit::Ptr unit = UnitFactory::Inst().createUnit(scnunit.objectID, unitPos, player);
                unit->setAngle(scnunit.rotation);
                unit->renderer().current_frame_ = scnunit.initAnimationFrame % unit->renderer().graphic_->getFrameCount();
                m_unitManager->add(unit);
            }
        }
        m_humanPlayer = m_players[0];
    } else {
        m_humanPlayer = std::make_shared<Player>(0, m_civilizations.front());
        map_->setUpSample();

        m_unitManager->add(UnitFactory::Inst().createUnit(Unit::FuriousTheMonkeyBoy, MapPos(48*6, 48*10, 0), m_humanPlayer));
        m_unitManager->add(UnitFactory::Inst().createUnit(Unit::Cobra, MapPos(48*8, 48*6, 0), m_humanPlayer));

        m_unitManager->add(UnitFactory::Inst().createUnit(Unit::MaleBuilder, MapPos(48*6, 48*6, 0), m_humanPlayer));
        m_unitManager->add(UnitFactory::Inst().createUnit(280, MapPos(48*10, 48*10, 0), m_humanPlayer)); // mangonel

        m_unitManager->add(UnitFactory::Inst().createUnit(Unit::Mill, MapPos(48*15, 48*15, 0), m_humanPlayer));

        Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::TownCenter, MapPos(48*2, 48*2, 0), m_humanPlayer);

        if (unit->data.Building.FoundationTerrainID > 0) {
            int width = unit->data.Size.x;
            int height = unit->data.Size.y;
            for (int x = 0; x < width*2; x++) {
                for (int y = 0; y < height*2; y++) {
                    map_->setTileAt(3 - width + x, 3 - height + y, unit->data.Building.FoundationTerrainID);
                }
            }
        }

        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*6, 48*5, 0), m_humanPlayer);
        unit->setAngle(M_PI + M_PI_2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*6, 48*4, 0), m_humanPlayer);
        unit->setAngle(M_PI + M_PI_2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*6, 48*3, 0), m_humanPlayer);
        unit->setAngle(M_PI_2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*7, 48*3, 0), m_humanPlayer);
        unit->setAngle(M_PI);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*8, 48*3, 0), m_humanPlayer);
        unit->setAngle(M_PI);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*9, 48*3, 0), m_humanPlayer);
        unit->setAngle(M_PI_2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*10, 48*4, 0), m_humanPlayer);
        unit->setAngle(M_PI_2 / 2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*11, 48*5, 0), m_humanPlayer);
        unit->setAngle(M_PI_2 / 2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*12, 48*6, 0), m_humanPlayer);
        unit->setAngle(M_PI_2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*11, 48*7, 0), m_humanPlayer);
        unit->setAngle(M_PI * 2);
        m_unitManager->add(unit);
        unit = UnitFactory::Inst().createUnit(117, MapPos(48*10, 48*8, 0), m_humanPlayer);
        unit->setAngle(M_PI * 2);
        m_unitManager->add(unit);
        unit = UnitFactory::Inst().createUnit(117, MapPos(48*9, 48*9, 0), m_humanPlayer);
        unit->setAngle(M_PI * 2);
        m_unitManager->add(unit);

        unit = UnitFactory::Inst().createUnit(117, MapPos(48*8, 48*10, 0), m_humanPlayer);
        unit->setAngle(M_PI_2);
        m_unitManager->add(unit);
    }
    m_actionPanel->setHumanPlayer(m_humanPlayer);

    map_->updateMapData();
    mapRenderer_.setRenderTarget(renderTarget_);
    mapRenderer_.setMap(map_);

    m_unitManager->setMap(map_);

    return true;
}

void GameState::draw()
{
    mapRenderer_.display();
    m_unitManager->render(renderTarget_);

    if (m_selecting) {
        renderTarget_->draw(m_selectionRect, sf::Color::Transparent, sf::Color::White);
    }

    renderTarget_->draw(m_uiOverlay, ScreenPos(0, 0));
    m_actionPanel->draw();

    renderTarget_->renderTarget_->draw(m_mouseCursor.sprite);
}

bool GameState::update(Time time)
{
    bool updated = false;
    updated = mapRenderer_.update(time) || updated;

    updated = m_unitManager->update(time) || updated;
    updated = m_actionPanel->update(time) || updated;

    if (m_cameraDeltaX != 0 || m_cameraDeltaY != 0) {
        const int deltaTime = time - m_lastUpdate;

        ScreenPos cameraScreenPos = renderTarget_->camera()->targetPosition().toScreen();
        cameraScreenPos.x += m_cameraDeltaX * deltaTime * CAMERA_SPEED;
        cameraScreenPos.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;

        MapPos cameraMapPos = cameraScreenPos.toMap();
        if (cameraMapPos.x < 0) cameraMapPos.x = 0;
        if (cameraMapPos.y < 0) cameraMapPos.y = 0;
        if (cameraMapPos.x > map_->width()) cameraMapPos.x = map_->width();
        if (cameraMapPos.y > map_->height()) cameraMapPos.y = map_->height();
        renderTarget_->camera()->setTargetPosition(cameraMapPos);


        if (m_selecting) {
            m_selectionStart.x -= m_cameraDeltaX * deltaTime * CAMERA_SPEED;
            m_selectionStart.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;
        }

        updated = true;
    }

    if (m_selecting) {
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
        m_mouseCursor.sprite.setPosition(event.mouseMove.x, event.mouseMove.y);

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

        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);
        if (m_selecting) {
            m_selectionCurr = mousePos;
        } else {
            m_unitManager->onMouseMove(renderTarget_->camera()->absoluteMapPos(mousePos));
        }

        const genie::Task *targetAction = m_unitManager->defaultActionAt(mousePos, renderTarget_->camera());
        if (!targetAction) {
            m_mouseCursor.setCursor(Cursor::Normal);
        } else if (targetAction->ActionType == genie::Task::Combat) {
            m_mouseCursor.setCursor(Cursor::Attack);
        } else {
            m_mouseCursor.setCursor(Cursor::Action);
        }

        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        ScreenPos cameraScreenPos = renderTarget_->camera()->targetPosition().toScreen();

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

    if ((event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased)) {
        return;
    }

    const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    if (m_actionPanel->rect().contains(mousePos)) {
        m_actionPanel->handleEvent(event);
        return;
    } else {
        m_actionPanel->releaseButtons();
    }

    if (event.type == sf::Event::MouseButtonPressed) {
//        if (event.mouseButton.y < 25) {
//            // top bar
//        } else if (event.mouseButton.y > uiSize().height - 210) {
//            // bottom
//        } else {
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                m_unitManager->onLeftClick(renderTarget_->camera()->absoluteMapPos(ScreenPos(event.mouseButton.x, event.mouseButton.y)));

                m_selectionStart = ScreenPos(event.mouseButton.x, event.mouseButton.y);
                m_selectionCurr = ScreenPos(event.mouseButton.x+1, event.mouseButton.y+1);
                m_selectionRect = ScreenRect(m_selectionStart, m_selectionCurr);
                m_selecting = true;
            }
//        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left && m_selecting) {
            m_unitManager->selectUnits(m_selectionRect, renderTarget_->camera());
            m_selectionRect = ScreenRect();
            m_selecting = false;
        } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
            m_unitManager->onRightClick(renderTarget_->camera()->absoluteMapPos(ScreenPos(event.mouseButton.x, event.mouseButton.y)));
        }

    }
}

Size GameState::uiSize() const
{
    if (m_uiOverlay.getSize().x == 0 || m_uiOverlay.getSize().y == 0) {
        WARN << "We don't have a valid UI overlay";
        return Size(640, 480);
    }

    return m_uiOverlay.getSize();
}
