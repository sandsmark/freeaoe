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

#include "UiScreen.h"

class HistoryScreen : public UiScreen
{
    static const int s_numListEntries = 16;
    static const int s_numVisibleTextLines = 11;
    static const int s_textWidth = 420;
    static const int s_textSize = 16;

    struct TextLine {
        bool italic = false;
        bool bold = false;
        std::string text;
    };

    enum UiElements {
        LargeScrollbar,
        UpButton,
        ActiveUpButton,
        DownButton,
        ActiveDownButton,
        SmallScrollbar,
        ScrollPosition,

        UpButton2,
        ActiveUpButton2,
        DownButton2,
        ActiveDownButton2,
        ScrollPosition2,

        UiElementsCount
    };

    struct UiElement {
        sf::Texture texture;
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
    void loadFile(const std::string &filePath);

    void updateVisibleText();
    void updateVisibleTitles();

    std::vector<std::string> m_titles;
    std::vector<std::string> m_sourceFiles;

//    Button m_largeScrollbar;
//    Button m_smallScrollbar;

//    Button m_scrollIndicator;

//    Button m_upButton;
//    Button m_downButton;
//    Button m_upButtonPressed;
//    Button m_downButtonPressed;

    std::array<UiElement, UiElementsCount> m_uiElements;

    std::array<sf::Text, s_numListEntries> m_visibleTitles;
    std::array<sf::Text, s_numVisibleTextLines> m_visibleText;

    std::vector<TextLine> m_textLines;

    int m_textScrollOffset = 0;
    int m_titleScrollOffset = 0;
};
