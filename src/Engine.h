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

#include "ui/TextButton.h"

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

#include "core/Logger.h"
#include "mechanics/StateManager.h"

namespace sf {
class RenderWindow;
}

struct Dialog
{
    enum Choice {
        Invalid = -1,
        Quit,
        Achievements,
        Save,
        Options,
        About,
        Cancel,
        ChoicesCount
    };

    Dialog(UiScreen *screen);

    void render(std::shared_ptr<sf::RenderWindow> &renderTarget);
    Choice handleEvent(const sf::Event &event);

    sf::Texture background;
    UiScreen *m_screen;

private:
    std::array<TextButton, ChoicesCount> m_buttons;
    Choice m_pressedButton = Invalid;
};

class Engine
{
    struct TopMenuButton {
        enum Type {
            Invalid = -1,
            GameMenu = 0,
            Diplo = 1,
            Chat = 2,
            TechTree = 3,
            Settings = 4,
            ButtonsCount
        } type;

        ScreenRect rect;
        sf::Texture texture;
        sf::Texture pressedTexture;
    };
public:

    static const sf::Clock GameClock;

    Engine();
    virtual ~Engine() = default;

    bool setup(const std::shared_ptr<genie::ScnFile> &scenario = nullptr);
    void start();

private:
    void showStartScreen();
    void loadTopButtons();
    void drawButtons();
    bool handleEvent(sf::Event event);
    void showMenu();

    std::shared_ptr<sf::RenderWindow> renderWindow_;
    std::shared_ptr<SfmlRenderTarget> renderTarget_;
    std::unique_ptr<Dialog> m_currentDialog;

    std::unique_ptr<UiScreen> m_mainScreen;

    StateManager state_manager_;

    sf::Text fps_label_;
    std::vector<TopMenuButton> m_buttons;
    TopMenuButton::Type m_pressedButton = TopMenuButton::Invalid;
};

