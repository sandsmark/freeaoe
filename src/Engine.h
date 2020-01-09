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

#include "core/Types.h"
#include "mechanics/StateManager.h"
#include "render/MapRenderer.h"
#include "ui/ActionPanel.h"
#include "ui/Dialog.h"
#include "ui/IconButton.h"
#include "ui/Minimap.h"
#include "ui/NumberLabel.h"
#include "ui/UiScreen.h"
#include "ui/UnitInfoPanel.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <memory>
#include <string>
#include <vector>

class GameState;
class SfmlRenderTarget;
namespace genie {
class ScnFile;
}  // namespace genie

namespace genie {
class ScnFile;
}

namespace sf {
class Clock;
class Event;
class RenderWindow;
}

struct MouseCursor;

class Engine
{
public:
    static const int s_numMessagesLines = 15;

    static const sf::Clock GameClock;

    Engine();
    virtual ~Engine();

    bool setup(const std::shared_ptr<genie::ScnFile> &scenario = nullptr);
    void start();

    void addMessage(const std::string &message);

private:
    void showStartScreen();
    void loadTopButtons();
    void loadUiOverlay();
    void drawUi();
    bool updateCamera(const std::shared_ptr<GameState> &state);
	bool handleEvent(const sf::Event &event, const std::shared_ptr<GameState> &state);
	bool handleKeyEvent(const sf::Event &event, const std::shared_ptr<GameState> &state);
	bool handleMouseMove(const sf::Event &event, const std::shared_ptr<GameState> &state);
	bool handleMousePress(const sf::Event &event, const std::shared_ptr<GameState> &state);
	bool handleMouseRelease(const sf::Event &event, const std::shared_ptr<GameState> &state);
    void showMenu();
    bool updateUi(const std::shared_ptr<GameState> &state);

    std::shared_ptr<sf::RenderWindow> renderWindow_;
    std::shared_ptr<SfmlRenderTarget> renderTarget_;
    std::unique_ptr<Dialog> m_currentDialog;

    std::unique_ptr<UiScreen> m_mainScreen;

    StateManager state_manager_;

    sf::Text m_resultOverlay;

    sf::Text fps_label_;
    std::vector<std::unique_ptr<IconButton>> m_buttons;

    std::unique_ptr<NumberLabel> m_woodLabel;
    std::unique_ptr<NumberLabel> m_foodLabel;
    std::unique_ptr<NumberLabel> m_goldLabel;
    std::unique_ptr<NumberLabel> m_stoneLabel;
    std::unique_ptr<NumberLabel> m_populationLabel;

    std::unique_ptr<MouseCursor> m_mouseCursor;

    float m_cameraDeltaX = 0.f;
    float m_cameraDeltaY = 0.f;

    Time m_lastUpdate = 0u;

    std::unique_ptr<Minimap> m_minimap;
    std::unique_ptr<ActionPanel> m_actionPanel;
    std::unique_ptr<UnitInfoPanel> m_unitInfoPanel;
    std::unique_ptr<MapRenderer> m_mapRenderer;

    std::array<sf::Text, s_numMessagesLines> m_visibleText;

    Drawable::Image::Ptr m_uiOverlay;

    ScreenPos m_selectionStart;
    ScreenPos m_selectionCurr;
    ScreenRect m_selectionRect;
    bool m_selecting = false;
};

