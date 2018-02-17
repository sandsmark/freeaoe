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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "mechanics/IState.h"
#include "global/Logger.h"
#include "Map.h"
#include "render/SfmlRenderTarget.h"
#include "render/UnitRenderer.h"
#include "render/MapRenderer.h"
#include "EntityManager.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include "Civilization.h"

#include "genie/script/ScnFile.h"

class GameClient;
class GameServer;

namespace sf {
class RenderTarget;
}

//------------------------------------------------------------------------------
/// State where the game is processed
//
class GameState : public IState
{
    struct Button {
        sf::Texture tex;
        int pos = 0;
    };

public:
    GameState(IRenderTargetPtr renderTarget);
    virtual ~GameState();

    void setScenario(std::shared_ptr<genie::ScnFile> scenario);

    void init() override;

    void draw() override;
    bool update(Time time) override;
    void handleEvent(sf::Event event) override;
    void setBuildableIcons();

    Size uiSize() const;

private:
    static Logger &log;

    GameState(const GameState &other);

    IRenderTargetPtr renderTarget_;

    EntityManager entity_manager_;
    UnitRenderer entity_form_manager_;
    /*
  GameServer *game_server_;
  GameClient *game_client_;
  */

    MapPtr map_;
    MapRenderer mapRenderer_;
    genie::SlpFilePtr m_unitIconsSlp;
    genie::SlpFilePtr m_buildingIconsSlp;
    std::vector<Button> m_currentIcons;

    std::shared_ptr<genie::ScnFile> scenario_;

    float m_cameraDeltaX;
    float m_cameraDeltaY;
    Time m_lastUpdate;


    ScreenPos m_selectionStart;
    ScreenPos m_selectionCurr;
    ScreenRect m_selectionRect;

    sf::Texture m_uiOverlay;

    std::vector<std::shared_ptr<Civilization>> m_civilizations;
};

#endif // GAMESTATE_H
