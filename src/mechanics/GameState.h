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
#include "mechanics/ScenarioController.h"
#include "core/Logger.h"

#include "Map.h"

#include "Civilization.h"

class UnitManager;

namespace genie {
class ScnFile;
class SlpFile;
}

struct Player;
using PlayerPtr = std::shared_ptr<Player>;

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
    enum class Result {
        Won,
        Lost,
        Running // meh names
    } result = Result::Running;

    static std::unordered_map<GameType, ResourceMap> defaultStartingResources;

    GameState(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    virtual ~GameState();

    void setScenario(const std::shared_ptr<genie::ScnFile> &scenario);
    void setGameType(const GameType &type) { m_gameType = type; }

    bool init() override;

    bool update(Time time) override;

    const PlayerPtr &humanPlayer() { return m_humanPlayer; }

    PlayerPtr player(int id);

    const std::shared_ptr<UnitManager> &unitManager() { return m_unitManager; }
    const MapPtr &map() const { return map_; }

    void moveCameraTo(const MapPos &newTarget);

    void onPlayerWin(int playerId);
    const std::unique_ptr<ScenarioController> &scenarioController() const { return m_scenarioController; }

private:
    void setupScenario();
    void setupGame(const GameType gameType);

    GameState(const GameState &other) = delete;

    std::shared_ptr<SfmlRenderTarget> renderTarget_;

    std::shared_ptr<UnitManager> m_unitManager;

    MapPtr map_;

    std::shared_ptr<genie::ScnFile> scenario_;

    std::shared_ptr<genie::SlpFile> m_waypointFlag;

    PlayerPtr m_humanPlayer;
    std::vector<PlayerPtr> m_players;

    GameType m_gameType = GameType::Default;

    std::unique_ptr<ScenarioController> m_scenarioController;
};

