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
#include "resource/DataManager.h"
#include "ui/ActionPanel.h"
#include "ui/UnitInfoPanel.h"
#include "ui/Minimap.h"
#include "core/Constants.h"
#include "debug/SampleGameFactory.h"

#include "resource/LanguageManager.h"

#define MOUSE_MOVE_EDGE_SIZE 10
#define CAMERA_SPEED 1.

std::unordered_map<GameType, ResourceMap> GameState::defaultStartingResources = {
    {
        GameType::Default, {
            { genie::ResourceType::FoodStorage, 500 },
            { genie::ResourceType::WoodStorage, 500 },
            { genie::ResourceType::StoneStorage, 500 },
            { genie::ResourceType::GoldStorage, 500 },
        }
    },
    {
        GameType::HighResource, {
            { genie::ResourceType::FoodStorage, 1000 },
            { genie::ResourceType::WoodStorage, 1000 },
            { genie::ResourceType::StoneStorage, 800 },
            { genie::ResourceType::GoldStorage, 700 },
        }
    },
    {
        GameType::MediumResource, {
            { genie::ResourceType::FoodStorage, 500 },
            { genie::ResourceType::WoodStorage, 500 },
            { genie::ResourceType::StoneStorage, 400 },
            { genie::ResourceType::GoldStorage, 300 },
        }
    },
    {
        GameType::KingOfTheHill, {
            { genie::ResourceType::FoodStorage, 200 },
            { genie::ResourceType::WoodStorage, 200 },
            { genie::ResourceType::StoneStorage, 200 },
            { genie::ResourceType::GoldStorage, 100 },
        }
    },
    {
        GameType::Deathmatch, {
            { genie::ResourceType::FoodStorage, 20000 },
            { genie::ResourceType::WoodStorage, 20000 },
            { genie::ResourceType::StoneStorage, 5000 },
            { genie::ResourceType::GoldStorage, 10000 },
        }
    },
    {
        GameType::Regicide, {
            { genie::ResourceType::FoodStorage, 500 },
            { genie::ResourceType::WoodStorage, 500 },
            { genie::ResourceType::StoneStorage, 150 },
            { genie::ResourceType::GoldStorage, 0 },
        }
    },
};

GameState::GameState(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_cameraDeltaX(0),
    m_cameraDeltaY(0),
    m_lastUpdate(0),
    m_woodLabel(75, 5),
    m_foodLabel(153, 5),
    m_goldLabel(230, 5),
    m_stoneLabel(307, 5),
    m_populationLabel(384, 5)
{
    m_unitManager = std::make_shared<UnitManager>();
    renderTarget_ = renderTarget;

    m_actionPanel = std::make_unique<ActionPanel>(renderTarget_);
    m_minimap = std::make_unique<Minimap>(renderTarget_);
    m_minimap->setUnitManager(m_unitManager);
    m_actionPanel->setUnitManager(m_unitManager);
    m_unitInfoPanel = std::make_unique<UnitInfoPanel>(renderTarget_);
    m_unitInfoPanel->setUnitManager(m_unitManager);
}

GameState::~GameState()
{
}

void GameState::setScenario(const std::shared_ptr<genie::ScnFile> &scenario)
{
    scenario_ = scenario;
}

bool GameState::init()
{
    TIME_THIS;
    if (!m_unitManager->init()) {
        return false;
    }

    if (!m_actionPanel->init()) {
        return false;
    }

    if (!m_unitInfoPanel->init()) {
        return false;
    }
    if (!m_minimap->init()) {
        WARN << "failed to init minimap";
        return false;
    }

    std::shared_ptr<genie::SlpFile> overlayFile = AssetManager::Inst()->getUiOverlay(AssetManager::Ui1280x1024, AssetManager::Viking);
    if (overlayFile) {
        m_uiOverlay.loadFromImage(Resource::convertFrameToImage(overlayFile->getFrame()));
        DBG << "Loaded UI overlay with size" << Size(m_uiOverlay.getSize());
    } else {
        AssetManager::UiResolution attemptedResolution = AssetManager::Ui1280x1024;
        AssetManager::UiCiv attemptedCiv = AssetManager::Briton;
        do {
            attemptedCiv = AssetManager::UiCiv(attemptedCiv + 1);
            if (attemptedCiv > AssetManager::Korean) {
                if (attemptedResolution == AssetManager::Ui1280x1024) {
                    attemptedResolution = AssetManager::Ui1024x768;
                } else if (attemptedResolution == AssetManager::Ui1024x768) {
                    attemptedResolution = AssetManager::Ui800x600;
                } else {
                    m_uiOverlay = sf::Texture();
                    break;
                }

                attemptedCiv = AssetManager::Briton;
            }
            overlayFile = AssetManager::Inst()->getUiOverlay(attemptedResolution, attemptedCiv);
        } while (!overlayFile);

        if (overlayFile) {
            WARN << "Loaded fallback ui overlay res" << attemptedResolution << "for civ" << attemptedCiv;
            m_uiOverlay.loadFromImage(Resource::convertFrameToImage(overlayFile->getFrame()));
        } else {
            WARN << "Failed to load ui overlay";
        }
    }

    m_mouseCursor.cursorsFile = AssetManager::Inst()->getSlp(AssetManager::filenameID("mcursors.shp"));
    if (m_mouseCursor.cursorsFile) {
        m_mouseCursor.texture.loadFromImage(Resource::convertFrameToImage(m_mouseCursor.cursorsFile->getFrame(Cursor::Normal)));
        m_mouseCursor.sprite.setTexture(m_mouseCursor.texture);
    } else {
        WARN << "Failed to get cursors";
    }

    // graphic 2962
    m_waypointFlag = AssetManager::Inst()->getSlp(3404);
    if (!m_waypointFlag) {
        WARN << "Failed to load waypoint animation";
    }

    const std::vector<genie::Civ> &civilizations = DataManager::Inst().civilizations();
    for (size_t i=0; i<civilizations.size(); i++) {
        m_civilizations.push_back(std::make_shared<Civilization>(i));
    }
    if (m_civilizations.empty()) {
        WARN << "Failed to load any civilizations";
        return false;
    }

    map_ = std::make_shared<Map>();
    m_unitManager->setMap(map_);
    m_minimap->setMap(map_);

    if (scenario_) {
        setupScenario();
    } else {
        setupGame(GameType::Default);
    }

    m_actionPanel->setHumanPlayer(m_humanPlayer);
    m_unitManager->setHumanPlayer(m_humanPlayer);

    map_->updateMapData();
    mapRenderer_.setRenderTarget(renderTarget_);
    mapRenderer_.setMap(map_);


    m_woodLabel.setValue(12345);
    m_foodLabel.setValue(12345);
    m_goldLabel.setValue(12345);
    m_stoneLabel.setValue(12345);
    m_populationLabel.setValue(125);
    m_populationLabel.setMaxValue(125);

    return true;
}

void GameState::draw()
{
    mapRenderer_.display();

    std::vector<std::weak_ptr<Entity>> visibleEntities;
    visibleEntities = map_->entitiesBetween(mapRenderer_.firstVisibleColumn(),
                                            mapRenderer_.firstVisibleRow(),
                                            mapRenderer_.lastVisibleColumn(),
                                            mapRenderer_.lastVisibleRow());

    m_unitManager->render(renderTarget_, visibleEntities);

    if (m_selecting) {
        renderTarget_->draw(m_selectionRect, sf::Color::Transparent, sf::Color::White);
    }

    renderTarget_->draw(m_uiOverlay, ScreenPos(0, 0));
    m_actionPanel->draw();
    m_unitInfoPanel->draw();
    m_minimap->draw();

    renderTarget_->draw(m_woodLabel.text);
    renderTarget_->draw(m_foodLabel.text);
    renderTarget_->draw(m_goldLabel.text);
    renderTarget_->draw(m_stoneLabel.text);
    renderTarget_->draw(m_populationLabel.text);
}

bool GameState::update(Time time)
{
    bool updated = false;
    updated = mapRenderer_.update(time) || updated;

    updated = m_unitManager->update(time) || updated;
    updated = m_actionPanel->update(time) || updated;
    updated = m_unitInfoPanel->update(time) || updated;
    updated = m_minimap->update(time) || updated;

    m_woodLabel.setValue(m_humanPlayer->resourcesAvailable[genie::ResourceType::WoodStorage]);
    m_foodLabel.setValue(m_humanPlayer->resourcesAvailable[genie::ResourceType::FoodStorage]);
    m_goldLabel.setValue(m_humanPlayer->resourcesAvailable[genie::ResourceType::GoldStorage]);
    m_stoneLabel.setValue(m_humanPlayer->resourcesAvailable[genie::ResourceType::StoneStorage]);

    m_populationLabel.setValue(m_humanPlayer->resourcesUsed[genie::ResourceType::PopulationHeadroom]);
    m_populationLabel.setMaxValue(m_humanPlayer->resourcesAvailable[genie::ResourceType::PopulationHeadroom]);

    if (m_cameraDeltaX != 0 || m_cameraDeltaY != 0) {
        const int deltaTime = time - m_lastUpdate;

        ScreenPos cameraScreenPos = renderTarget_->camera()->targetPosition().toScreen();
        cameraScreenPos.x += m_cameraDeltaX * deltaTime * CAMERA_SPEED;
        cameraScreenPos.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;

        MapPos cameraMapPos = cameraScreenPos.toMap();
        if (cameraMapPos.x < 0) { cameraMapPos.x = 0; }
        if (cameraMapPos.y < 0) { cameraMapPos.y = 0; }
        if (cameraMapPos.x > map_->width()) { cameraMapPos.x = map_->width(); }
        if (cameraMapPos.y > map_->height()) { cameraMapPos.y = map_->height(); }
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

bool GameState::handleEvent(sf::Event event)
{
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
            return false;
        }

        MapPos cameraMapPos = cameraScreenPos.toMap();
        if (cameraMapPos.x < 0) { cameraMapPos.x = 0; }
        if (cameraMapPos.y < 0) { cameraMapPos.y = 0; }
        if (cameraMapPos.x > map_->width()) { cameraMapPos.x = map_->width(); }
        if (cameraMapPos.y > map_->height()) { cameraMapPos.y = map_->height(); }
        renderTarget_->camera()->setTargetPosition(cameraMapPos);

        return true;
    }

    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased && event.type != sf::Event::MouseMoved) {
        return false;
    }

    const ScreenPos mousePos = event.type == sf::Event::MouseMoved ?
                ScreenPos(event.mouseMove.x, event.mouseMove.y)
                    :
                ScreenPos(event.mouseButton.x, event.mouseButton.y);

    m_mouseCursor.sprite.setPosition(mousePos);
    if (m_minimap->rect().contains(mousePos)) {
        if (m_minimap->handleEvent(event)) {
            return true;
        }
    } else {
        m_minimap->mouseExited();
    }

    if (event.type == sf::Event::MouseMoved) {

        if (event.mouseMove.x < MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaX = -1;
        } else if (event.mouseMove.x > renderTarget_->getSize().width - MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaX = 1;
        } else {
            m_cameraDeltaX = 0;
        }

        if (event.mouseMove.y < MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaY = 1;
        } else if (event.mouseMove.y > renderTarget_->getSize().height - MOUSE_MOVE_EDGE_SIZE) {
            m_cameraDeltaY = -1;
        } else {
            m_cameraDeltaY = 0;
        }

        if (mousePos.y < 800) {
            if (m_selecting) {
                m_selectionCurr = mousePos;
            } else {
                m_unitManager->onMouseMove(renderTarget_->camera()->absoluteMapPos(mousePos));
            }

            if (m_unitManager->state() == UnitManager::State::SelectingAttackTarget) {
                m_mouseCursor.setCursor(Cursor::Attack);
            } else {
                const Task targetAction = m_unitManager->defaultActionAt(mousePos, renderTarget_->camera());
                if (!targetAction.data) {
                    m_mouseCursor.setCursor(Cursor::Normal);
                } else if (targetAction.data->ActionType == genie::Task::Combat) {
                    m_mouseCursor.setCursor(Cursor::Attack);
                } else {
                    m_mouseCursor.setCursor(Cursor::Action);
                }
            }

        }
    }

    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return false;
    }

    if (m_actionPanel->rect().contains(mousePos)) {
        return m_actionPanel->handleEvent(event);
    }
    if (m_unitInfoPanel->rect().contains(mousePos)) {
        return m_unitInfoPanel->handleEvent(event);
    }

    m_actionPanel->releaseButtons();

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            if (m_unitManager->onLeftClick(ScreenPos(event.mouseButton.x, event.mouseButton.y), renderTarget_->camera())) {
                return true;
            }

            m_selectionStart = ScreenPos(event.mouseButton.x, event.mouseButton.y);
            m_selectionCurr = ScreenPos(event.mouseButton.x+1, event.mouseButton.y+1);
            m_selectionRect = ScreenRect(m_selectionStart, m_selectionCurr);
            m_selecting = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left && m_selecting) {
            m_unitManager->selectUnits(m_selectionRect, renderTarget_->camera());
            m_selectionRect = ScreenRect();
            m_selecting = false;
        } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
            m_unitManager->onRightClick(ScreenPos(event.mouseButton.x, event.mouseButton.y), renderTarget_->camera());
        }
    }

    return false;
}

Size GameState::uiSize() const
{
    if (m_uiOverlay.getSize().x == 0 || m_uiOverlay.getSize().y == 0) {
        WARN << "We don't have a valid UI overlay";
        return Size(640, 480);
    }

    return m_uiOverlay.getSize();
}

void GameState::setupScenario()
{
    TIME_THIS;
    DBG << "Setting up scenario:" << scenario_->scenarioInstructions;
    map_->create(scenario_->map);

    const genie::ScnMainPlayerData &playerData = scenario_->playerData;
    for (size_t playerNum = 0; playerNum < scenario_->enabledPlayerCount; playerNum++) {
        Player::Ptr player;

        // player 0 is gaia
        if (playerNum != UnitManager::GaiaID) {
            player = std::make_shared<Player>(playerNum, m_civilizations[playerData.resourcesPlusPlayerInfo[playerNum-1].civilizationID]);
            player->name = playerData.playerNames[playerNum - 1];
        } else {
            player = std::make_shared<Player>(playerNum, m_civilizations[UnitManager::GaiaID]); // gaia
        }

        const genie::ScnPlayerResources &resources = scenario_->playerResources[playerNum];
        player->resourcesAvailable[genie::ResourceType::GoldStorage] = resources.gold;
        player->resourcesAvailable[genie::ResourceType::FoodStorage] = resources.food;
        player->resourcesAvailable[genie::ResourceType::WoodStorage] = resources.wood;
        player->resourcesAvailable[genie::ResourceType::StoneStorage] = resources.stone;
        player->resourcesAvailable[genie::ResourceType::OreStorage] = resources.ore;
        player->resourcesAvailable[genie::ResourceType::TradeGoods] = resources.goods;
        player->resourcesAvailable[genie::ResourceType::PopulationHeadroom] = scenario_->playerResources[playerNum].popLimit;

        m_players.push_back(player);
        for (const genie::ScnUnit &scnunit : scenario_->playerUnits[playerNum].units) {
            MapPos unitPos((scnunit.positionY) * Constants::TILE_SIZE, (scnunit.positionX) * Constants::TILE_SIZE, scnunit.positionZ * DataManager::Inst().terrainBlock().ElevHeight);
            Unit::Ptr unit = UnitFactory::Inst().createUnit(scnunit.objectID, unitPos, player, *m_unitManager);
            m_unitManager->add(unit);

            unit->setAngle(scnunit.rotation - M_PI_2/2.);

            if (unit->renderer().frameCount()) {
                unit->renderer().setCurrentFrame(scnunit.initAnimationFrame % unit->renderer().frameCount());
            } else {
//                WARN << "invalid graphics";
            }
        }
    }
    MapPos cameraPos(scenario_->players[1].initCameraX * Constants::TILE_SIZE, map_->height() - scenario_->players[1].initCameraY * Constants::TILE_SIZE);
    renderTarget_->camera()->setTargetPosition(cameraPos);
    m_humanPlayer = m_players[1];
}

void GameState::setupGame(const GameType /*gameType*/)
{
   SampleGamePtr sampleGameSetup = SampleGameFactory::Inst().createGameSetup(map_, m_unitManager);

   sampleGameSetup->setupMap();
   sampleGameSetup->setupActors(m_civilizations, defaultStartingResources[m_gameType]);

    m_humanPlayer = sampleGameSetup->getHumanPlayer();
    m_players.push_back(m_humanPlayer);
    m_players.push_back(sampleGameSetup->getEnemyPlayer());

    MapPos cameraPos(map_->width() / 2, map_->height()  / 2);
    renderTarget_->camera()->setTargetPosition(cameraPos);
}
