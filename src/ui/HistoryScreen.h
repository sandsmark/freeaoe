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

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <string>
#include <vector>

#include "UiScreen.h"
#include "core/Types.h"

namespace sf {
class Event;
}  // namespace sf

class HistoryScreen : public UiScreen
{
    static const int s_numListEntries = 17;
    static const int s_numVisibleTextLines = 12;
    static const int s_textWidth = 400; //height = 236
    static const int s_titlesTextSize = 13;
    static const int s_buttonTextSize = 14;
    static const int s_mainTextSize = 13;

    struct TextLine {
        bool italic = false;
        bool bold = false;
        float width = 0.f;
        std::string text;
    };

    struct ClickableText {
        sf::Text text;
        ScreenRect rect;
    };

    struct HistoryEntry {
        sf::Texture illustration;
        sf::Texture secondaryIllustration;
        std::string title;
        std::string filename;
    };

    enum UiElementTextures {
        LargeScrollbarTexture,
        UpButtonTexture,
        ActiveUpButtonTexture,
        DownButtonTexture,
        ActiveDownButtonTexture,
        SmallScrollbarTexture,
        ScrollPositionTexture,

        UiElementTextureCount
    };
    enum UiElements {
        InvalidUiElement = -1,

        TitlesScrollbar,
        TitlesUpButton,
        TitlesDownButton,
        TitlesPositionIndicator,

        TextScrolllbar,
        TextUpButton,
        TextDownButton,
        TextPositionIndicator,

        MainScreenButton,

        UiElementsCount
    };

    struct UiElement {
        sf::Texture texture;
        sf::Texture hoverTexture;
        sf::Texture pressTexture;
        ScreenRect rect;
    };

public:
    HistoryScreen();

    void display();
    bool init(const std::string &filesDir);

private:
    using UiScreen::init;

    void render() override;
    bool handleMouseEvent(const sf::Event &event) override;
    void handleKeyEvent(const sf::Event &event) override;
    void loadFile(const std::string &filePath);

    void updateVisibleText();
    void updateVisibleTitles();

    std::vector<HistoryEntry> m_historyEntries;

    std::array<UiElement, UiElementsCount> m_uiElements;

    std::array<ClickableText, s_numListEntries> m_visibleTitles;
    std::array<sf::Text, s_numVisibleTextLines> m_visibleText;

    std::vector<TextLine> m_textLines;

    UiElements m_currentUiElement = InvalidUiElement;
    UiElements m_pressedUiElement = InvalidUiElement;

    ScreenRect m_homeButtonRect;
    ScreenRect m_textRect;

    int m_textScrollOffset = 0;
    int m_titleScrollOffset = 0;
    int m_currentEntry = 0;

    sf::Text m_mainScreenText;
    sf::Text m_titleText;
};
