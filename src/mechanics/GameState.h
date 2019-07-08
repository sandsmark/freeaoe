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

#include "mechanics/IState.h"
#include "mechanics/Player.h"
#include "mechanics/ScenarioController.h"
#include "core/Logger.h"

#include "Map.h"

#include "Civilization.h"

class UnitManager;

namespace genie {
class ScnFile;
}

enum class GameType {
    Default,
    HighResource,
    MediumResource,
    KingOfTheHill,
    Deathmatch,
    SuddenDeath,
    Regicide,
    WonderRace
};

namespace sf {
class RenderTarget;
}
class SfmlRenderTarget;

//------------------------------------------------------------------------------
/// State where the game is processed
//
class GameState : public IState
{
public:
    static std::unordered_map<GameType, ResourceMap> defaultStartingResources;

    GameState(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    virtual ~GameState();

    void setScenario(const std::shared_ptr<genie::ScnFile> &scenario);
    void setGameType(const GameType &type) { m_gameType = type; }

    bool init() override;

    bool update(Time time) override;

    const Player::Ptr &humanPlayer() { return m_humanPlayer; }

    const std::shared_ptr<UnitManager> &unitManager() { return m_unitManager; }
    const MapPtr &map() const { return map_; }

private:
    void setupScenario();
    void setupGame(const GameType gameType);

    GameState(const GameState &other) = delete;

    std::shared_ptr<SfmlRenderTarget> renderTarget_;

    std::shared_ptr<UnitManager> m_unitManager;

    MapPtr map_;

    std::shared_ptr<genie::ScnFile> scenario_;

    genie::SlpFilePtr m_waypointFlag;

    std::vector<Civilization::Ptr> m_civilizations;

    Player::Ptr m_humanPlayer;
    std::vector<Player::Ptr> m_players;

    GameType m_gameType = GameType::Default;

    std::unique_ptr<ScenarioController> m_scenarioController;
};

