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

#include <memory>
#include <array>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "global/Types.h"

namespace sf {
class RenderWindow;
class Event;
}

namespace genie {
class SlpFile;
}

class UiScreen
{
public:
    UiScreen() = delete;

    virtual bool init();

protected:
    bool run();

    UiScreen(const char *uiFile);
    virtual void render() = 0;
    virtual bool handleMouseEvent(const sf::Event &event) = 0;

    sf::Color m_textFillColor;
    sf::Color m_textOutlineColor;
    int m_paletteId = 0;
    std::unique_ptr<sf::RenderWindow> m_renderWindow;

private:
    sf::Texture m_background;
    const char *m_uiFile;
};
