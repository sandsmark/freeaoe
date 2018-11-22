/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

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

#include <memory>
#include <array>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>


#include "UiScreen.h"

namespace sf {
class RenderWindow;
class Event;
}

namespace genie {
class SlpFile;
}

class HomeScreen : public UiScreen
{
public:
    struct Button {
        enum Type {
            Singleplayer,
            Multiplayer,
            Zone,
            Tutorial,
            MapEditor,
            History,
            Options,
            About,
            Banner,
            Exit,
            TypeCount
        };

        ScreenRect rect;


        int frame = 0;

        std::string description;

        sf::Texture texture;
        sf::Texture hoverTexture;
        sf::Texture selectedTexture;

        ScreenPos offset;
        ScreenPos hoverOffset;
        ScreenPos selectedOffset;

        sf::Text text;
        ScreenRect textRect;
    };

    HomeScreen();

    bool init();

    Button::Type getSelection();

private:
    void render();
    bool handleMouseEvent(const sf::Event &event);

    std::array<Button, Button::TypeCount> m_buttons;

    ScreenRect m_descriptionRect;
    sf::Text m_description;

    int m_hoveredButton = -1;
};
