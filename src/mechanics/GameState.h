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
#include "core/Logger.h"

#include "Map.h"
#include "render/SfmlRenderTarget.h"
#include "render/MapRenderer.h"
#include "UnitManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Civilization.h"

#include "genie/script/ScnFile.h"

class GameClient;
class GameServer;
class ActionPanel;
class UnitInfoPanel;
class Minimap;

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

struct Label {
    Label(const int right, const int top) :
        m_right(right),
        m_top(top)
    {
        text.setFont(SfmlRenderTarget::defaultFont());
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(16);
    }

    void setValue(const int value) {
        if (value == m_value) {
            return;
        }
        m_value = value;
        updateText();
    }

    void setMaxValue(const int maxValue) {
        if (maxValue == m_maxValue) {
            return;
        }
        m_maxValue = maxValue;
        updateText();
    }

    sf::Text text;

private:
    void updatePosition() {
        text.setPosition(sf::Vector2f(m_right - text.getLocalBounds().width, m_top));
    }

    void updateText() {
        std::string string = std::to_string(m_value);
        if (m_maxValue) {
            string += '/';
            string += std::to_string(m_maxValue);
        }
        text.setString(string);
        updatePosition();
    }

    int m_maxValue = 0;
    int m_value = 0;

    const int m_right = 0;
    const int m_top = 0;
};

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
        texture.loadFromImage(Resource::convertFrameToImage(cursorsFile->getFrame(type)));
        sprite.setTexture(texture, true);
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
    static std::unordered_map<GameType, ResourceMap> defaultStartingResources;

    GameState(const std::shared_ptr<SfmlRenderTarget> &renderTarget);
    virtual ~GameState();

    void setScenario(const std::shared_ptr<genie::ScnFile> &scenario);
    void setGameType(const GameType &type) { m_gameType = type; }

    bool init() override;

    void draw() override;
    bool update(Time time) override;
    bool handleEvent(sf::Event event) override;
    void setBuildableIcons();

    Size uiSize() const;

    const std::shared_ptr<UnitManager> &unitManager() { return m_unitManager; }

    const Cursor &cursor() const { return m_mouseCursor; }

private:
    void setupScenario();
    void setupGame(const GameType gameType);

    GameState(const GameState &other) = delete;

    std::shared_ptr<SfmlRenderTarget> renderTarget_;

    std::shared_ptr<UnitManager> m_unitManager;
    std::unique_ptr<ActionPanel> m_actionPanel;
    std::unique_ptr<UnitInfoPanel> m_unitInfoPanel;
    std::unique_ptr<Minimap> m_minimap;

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

    Label m_woodLabel;
    Label m_foodLabel;
    Label m_goldLabel;
    Label m_stoneLabel;
    Label m_populationLabel;
    GameType m_gameType = GameType::Default;
};

