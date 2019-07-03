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
#include "ui/Dialog.h"

namespace sf {
class RenderWindow;
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
    void drawUi();
    bool handleEvent(sf::Event event);
    void showMenu();
    void updateUi(const Player::Ptr &humanPlayer);

    std::shared_ptr<sf::RenderWindow> renderWindow_;
    std::shared_ptr<SfmlRenderTarget> renderTarget_;
    std::unique_ptr<Dialog> m_currentDialog;

    std::unique_ptr<UiScreen> m_mainScreen;

    StateManager state_manager_;

    sf::Text fps_label_;
    std::vector<TopMenuButton> m_buttons;
    TopMenuButton::Type m_pressedButton = TopMenuButton::Invalid;

    Label m_woodLabel;
    Label m_foodLabel;
    Label m_goldLabel;
    Label m_stoneLabel;
    Label m_populationLabel;

    Cursor m_mouseCursor;
};

