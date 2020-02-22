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

#include "UnitFactory.h"
#include <Engine.h>
#include "render/SfmlRenderTarget.h"
#include "resource/DataManager.h"
#include "resource/AssetManager.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "core/Types.h"
#include "debug/ISampleGame.h"
#include "debug/SampleGameFactory.h"
#include "debug/ISampleGame.h"
#include "global/EventManager.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Player.h"
#include "mechanics/Map.h"

#include "resource/LanguageManager.h"
#include "render/Camera.h"

#include <genie/resource/Color.h>
#include "genie/script/ScnFile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <render/GraphicRender.h>

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

GameState::GameState(const std::shared_ptr<SfmlRenderTarget> &renderTarget)
{
    m_unitManager = std::make_shared<UnitManager>();
    renderTarget_ = renderTarget;
    m_scenarioController = std::make_unique<ScenarioController>(this);
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

    // graphic 2962
    m_waypointFlag = AssetManager::Inst()->getSlp(3404);
    if (!m_waypointFlag) {
        WARN << "Failed to load waypoint animation";
    }

    map_ = std::make_shared<Map>();
    m_unitManager->setMap(map_);

    if (scenario_) {
        setupScenario();
    } else {
        setupGame(GameType::Default);
    }

    m_unitManager->setHumanPlayer(m_humanPlayer);

    map_->updateMapData();

    return true;
}

bool GameState::update(Time time)
{
    bool updated = false;

    updated = m_unitManager->update(time) || updated;
    if (m_scenarioController) {
        updated = m_scenarioController->update(time) || updated;
    }

    //game_server_->update();
    //game_client_->update();

    return updated;
}

Player::Ptr GameState::player(int id)
{
    if (id < 0 || id >= m_players.size()) {
        WARN << "asked for invalid player id" << id << m_players.size();
        return nullptr;
    }
    return m_players[id];
}

void GameState::moveCameraTo(const MapPos &newTarget)
{
    renderTarget_->camera()->setTargetPosition(newTarget);
}

void GameState::onPlayerWin(int playerId)
{
    DBG << "TODO: winner winner chicken dinner" << playerId;
    if (playerId == m_humanPlayer->playerId) {
        result = Result::Won;
    } else {
        result = Result::Lost;
    }
}

void GameState::onResourceBought(const genie::ResourceType type)
{
    m_tradingPrices[type] += 2;

    EventManager::tradingPriceChanged(type, m_tradingPrices[type]);
}

void GameState::onResourceSold(const genie::ResourceType type)
{
    m_tradingPrices[type] -= 2;

    EventManager::tradingPriceChanged(type, m_tradingPrices[type]);
}

void GameState::setTradingPrice(const genie::ResourceType type, const int newPrice)
{
    m_tradingPrices[type] = newPrice;
    EventManager::tradingPriceChanged(type, m_tradingPrices[type]);
}

void GameState::setupScenario()
{
    TIME_THIS;
    DBG << "Setting up scenario:" << scenario_->scenarioInstructions;
    map_->create(scenario_->map);

    const genie::ScnMainPlayerData &playersData = scenario_->playerData;

    int humanPlayerId = 1;
    for (size_t playerNum = 0; playerNum < scenario_->enabledPlayerCount + 1; playerNum++) { // +1 for gaia
        Player::Ptr player;

        int realPlayerNum = 0;

        // player 0 is gaia, but the layout in the scn files is extremely confusing, so some data is at index 8
        if (playerNum == UnitManager::GaiaID) {
            realPlayerNum = 8;

            player = std::make_shared<Player>(playerNum, UnitManager::GaiaID);
            player->civilization.setGaiaOverrideCiv(playersData.resourcesPlusPlayerInfo[realPlayerNum].civilizationID);
            player->name = "Gaia";
            player->playerColor = -1;
        } else {
            realPlayerNum = playerNum - 1;

            player = std::make_shared<Player>(playerNum, playersData.resourcesPlusPlayerInfo[realPlayerNum].civilizationID);
            player->name = playersData.playerNames[realPlayerNum];
            player->playerColor = scenario_->players[realPlayerNum].playerColor;
        }

        const genie::ScnPlayerResources &resources = scenario_->playerResources[playerNum];
        player->setAvailableResource(genie::ResourceType::GoldStorage,  resources.gold);
        player->setAvailableResource(genie::ResourceType::FoodStorage,  resources.food);
        player->setAvailableResource(genie::ResourceType::WoodStorage,  resources.wood);
        player->setAvailableResource(genie::ResourceType::StoneStorage, resources.stone);
        player->setAvailableResource(genie::ResourceType::OreStorage,   resources.ore);
        player->setAvailableResource(genie::ResourceType::TradeGoods,   resources.goods);
        player->setAvailableResource(genie::ResourceType::CurrentPopulation, resources.popLimit);

        if (playersData.resourcesPlusPlayerInfo[realPlayerNum].isHuman) {
            if (m_humanPlayer) {
                WARN << "multiple human players defined" << m_humanPlayer->playerId << realPlayerNum;
            }
            m_humanPlayer = player;
            humanPlayerId = playerNum;
        }

        m_players.push_back(player);

        for (const genie::ScnUnit &scnunit : scenario_->playerUnits[playerNum].units) {
            MapPos unitPos((scnunit.positionY) * Constants::TILE_SIZE, (scnunit.positionX) * Constants::TILE_SIZE, scnunit.positionZ * DataManager::Inst().terrainBlock().ElevHeight);
            Unit::Ptr unit = UnitFactory::Inst().createUnit(scnunit.objectID, player, *m_unitManager);
            unit->spawnId = scnunit.spawnID;
            m_unitManager->add(unit, unitPos);

            unit->setAngle(scnunit.rotation - M_PI_2/2.);

            if (unit->renderer().frameCount()) {
                unit->renderer().setCurrentFrame(scnunit.initAnimationFrame % unit->renderer().frameCount());
            } else {
//                WARN << "invalid graphics";
            }
        }
    }

    MapPos cameraPos;
    if (scenario_->playerData.player1CameraX >= 0 &&  scenario_->playerData.player1CameraX >= 0) {
        cameraPos = MapPos(scenario_->playerData.player1CameraX * Constants::TILE_SIZE, scenario_->playerData.player1CameraY * Constants::TILE_SIZE);
    } else {
        cameraPos = MapPos (scenario_->players[humanPlayerId].initCameraX * Constants::TILE_SIZE, map_->height() - scenario_->players[humanPlayerId].initCameraY * Constants::TILE_SIZE);
    }
    renderTarget_->camera()->setTargetPosition(cameraPos);

    if (!m_humanPlayer) {
        WARN << "no human player defined, setting to 1. player";
        m_humanPlayer = m_players[1];
    }

    m_scenarioController->setScenario(scenario_);
}

void GameState::setupGame(const GameType /*gameType*/)
{
   SampleGamePtr sampleGameSetup = SampleGameFactory::Inst().createGameSetup(map_, m_unitManager);

   sampleGameSetup->setupMap();
   sampleGameSetup->setupActors(defaultStartingResources[m_gameType]);

    m_humanPlayer = sampleGameSetup->getHumanPlayer();

    m_players.push_back(sampleGameSetup->getGaiaPlayer());
    m_players.push_back(m_humanPlayer);
    m_players.push_back(sampleGameSetup->getEnemyPlayer());

    MapPos cameraPos(map_->width() / 2, map_->height()  / 2);
    renderTarget_->camera()->setTargetPosition(cameraPos);
}
