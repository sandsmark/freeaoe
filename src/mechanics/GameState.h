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
#include "mechanics/Player.h"
#include "global/Logger.h"
#include "Map.h"
#include "render/SfmlRenderTarget.h"
#include "render/MapRenderer.h"
#include "UnitManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Civilization.h"

#include "genie/script/ScnFile.h"

class GameClient;
class GameServer;
class ActionPanel;

namespace sf {
class RenderTarget;
}

struct Cursor {
    enum Type {
        Normal = 0,
        Busy,
        Target,
        Action,
        Attack,
        TargetPos,
        WhatsThis,
        Build,
        Axe,
        Protect,
        Horn,
        MoveTo,
        Disabled,
        Garrison,
        Garrison2,
        Disembark,
        Embark,
        TargetCircle,
        Flag
    };

    void setCursor(const Type type) {
        if (type == currentType) {
            return;
        }
        texture.loadFromImage(res::Resource::convertFrameToImage(cursorsFile->getFrame(type)));
        sprite.setTexture(texture);
        currentType = type;
    }

    sf::Texture texture;
    sf::Sprite sprite;
    genie::SlpFilePtr cursorsFile;

    Type currentType = Normal;
};

//------------------------------------------------------------------------------
/// State where the game is processed
//
class GameState : public IState
{
public:
    GameState(std::shared_ptr<SfmlRenderTarget> renderTarget);
    virtual ~GameState();

    void setScenario(std::shared_ptr<genie::ScnFile> scenario);

    bool init() override;

    void draw() override;
    bool update(Time time) override;
    void handleEvent(sf::Event event) override;
    void setBuildableIcons();

    Size uiSize() const;

    const std::shared_ptr<UnitManager> &unitManager() { return m_unitManager; }

private:
    GameState(const GameState &other) = delete;

    std::shared_ptr<SfmlRenderTarget> renderTarget_;

    std::shared_ptr<UnitManager> m_unitManager;
    std::unique_ptr<ActionPanel> m_actionPanel;
    /*
  GameServer *game_server_;
  GameClient *game_client_;
  */

    MapPtr map_;
    MapRenderer mapRenderer_;

    std::shared_ptr<genie::ScnFile> scenario_;

    float m_cameraDeltaX;
    float m_cameraDeltaY;
    Time m_lastUpdate;


    ScreenPos m_selectionStart;
    ScreenPos m_selectionCurr;
    ScreenRect m_selectionRect;
    bool m_selecting = false;

    sf::Texture m_uiOverlay;
    sf::Texture m_buttonBackground;


    genie::SlpFilePtr m_waypointFlag;

    int m_interfacePage = 0;

    std::vector<Civilization::Ptr> m_civilizations;

    Player::Ptr m_humanPlayer;
    std::vector<Player::Ptr> m_players;

    Cursor m_mouseCursor;
};

#endif // GAMESTATE_H
