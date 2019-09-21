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
#include "HomeScreen.h"

#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"
#include "resource/DataManager.h"
#include "render/SfmlRenderTarget.h"
#include <genie/resource/UIFile.h>
#include <genie/resource/SlpFile.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

HomeScreen::HomeScreen() :
    UiScreen(DataManager::Inst().isHd() ? "main.sin" : "xmain.sin")
{

}

bool HomeScreen::init()
{
    if (!UiScreen::init()) {
        return false;
    }

    const bool isHd = DataManager::Inst().isHd();

    std::shared_ptr<genie::SlpFile> slpFile = AssetManager::Inst()->getSlp(isHd ? "main_32.slp" : "xmain.slp");
    if (!slpFile) {
        WARN << "failed to load slp file for home screen";
        return false;
    }

    const genie::PalFile &palette = AssetManager::Inst()->getPalette(m_paletteId);

    if (isHd) {
        m_descriptionRect = ScreenRect(675, 650, 475, 100);
    } else {
        m_descriptionRect = ScreenRect(390, 506, 393, 94);
    }
    m_description.setPosition(m_descriptionRect.topLeft());
    m_description.setOutlineColor(m_textOutlineColor);
    m_description.setFillColor(m_textFillColor);
    m_description.setOutlineThickness(1);
    m_description.setFont(SfmlRenderTarget::defaultFont());
    if (AssetManager::Inst()->missingData()) {
        m_description.setCharacterSize(19);
        m_description.setString("WARNING: Terrain graphics are missing,\ncommon reason is using data from Rise of the Rajas.\nIf using Steam, opt into beta and select 'patch43 - Patch 4.3'.\nOtherwise things look crap.");
        m_description.setFillColor(sf::Color::White);
        m_description.setOutlineColor(sf::Color(255, 128, 128));
    } else {
        m_description.setCharacterSize(10);
    }

    if (isHd) {
        // Gotten from the main-menu.json (easier to just massage the contents and copy than implementing a json parser..)
        m_buttons[Button::Singleplayer].rect = { 532,   9, 192, 258 };
        m_buttons[Button::Multiplayer].rect =  { 495, 265, 161, 188 };
        m_buttons[Button::Zone].rect =         { 500, 482, 159, 129 };
        m_buttons[Button::Tutorial].rect =     { 135,   2, 218, 254 };
        m_buttons[Button::MapEditor].rect =    { 410, 344, 123,  97 };
        m_buttons[Button::History].rect =      { 290, 198, 160, 147 };
        m_buttons[Button::Options].rect =      { 295, 439, 137, 139 };
        m_buttons[Button::Banner].rect =       { 128,   1, 585, 202 };
        m_buttons[Button::Exit].rect =         { 174, 631, 230, 137 };

        m_buttons[Button::Singleplayer].textRect = { 542,  20, 178,  38 };
        m_buttons[Button::Multiplayer].textRect =  { 502, 284, 145,  24 };
        m_buttons[Button::Zone].textRect =         { 500, 482, 159,  41 };
        m_buttons[Button::Tutorial].textRect =     { 150,  13, 188,  40 };
        m_buttons[Button::MapEditor].textRect =    { 420, 355, 107,  18 };
        m_buttons[Button::History].textRect =      { 304, 213, 128,  32 };
        m_buttons[Button::Options].textRect =      { 304, 450, 117,  24 };
        m_buttons[Button::Exit].textRect =         { 200, 704, 160,  26 };

    } else {
        // These are fun to figure out
        m_buttons[Button::Singleplayer].rect = { 309,  12, 120, 189 };
        m_buttons[Button::Multiplayer].rect =  { 263, 217,  97, 131 };
        m_buttons[Button::Zone].rect =         { 271, 367,  67,  64 };
        m_buttons[Button::Tutorial].rect =     {   0,   6, 125, 187 };
        m_buttons[Button::MapEditor].rect =    { 197, 273,  70,  67 };
        m_buttons[Button::History].rect =      { 103, 164, 102,  97 };
        m_buttons[Button::Options].rect =      { 101, 347,  95, 100 };
        m_buttons[Button::Banner].rect =       {   0,   0, 427, 170 };
        m_buttons[Button::Exit].rect =         {   5, 535, 153,  65 };

        // These are fun to figure out x2
        m_buttons[Button::Singleplayer].textRect = { 277,  21, 180,  18 };
        m_buttons[Button::Multiplayer].textRect =  { 222, 222, 180,  18 };
        m_buttons[Button::Zone].textRect =         { 213, 369, 180,  18 };
        m_buttons[Button::Tutorial].textRect =     {   0,  16, 120,  18 };
        m_buttons[Button::MapEditor].textRect =    { 142, 276, 180,  18 };
        m_buttons[Button::History].textRect =      {  64, 169, 180,  18 };
        m_buttons[Button::Options].textRect =      {  56, 351, 180,  18 };
        m_buttons[Button::Exit].textRect =         {   0, 562, 160,  18 };
    }


    for (int i=0; i<Button::TypeCount; i++) {
        if (i == Button::About) {
            continue; // TODO: need to find where the fuck it's supposed to go
        }

        Button &b = m_buttons[i];

        int frameNum = 10 + i * 4;
        if (i == Button::Banner) {
            if (isHd) {
                frameNum = 50;
            } else {
                frameNum = 49;
            }
        }

        const genie::SlpFramePtr &frame = slpFile->getFrame(frameNum);
        const genie::SlpFramePtr &selectedFrame = slpFile->getFrame(frameNum + 1);
        const genie::SlpFramePtr &hoverFrame = slpFile->getFrame(frameNum + 2);

        if (i != Button::Banner) {
            b.text.setString(LanguageManager::getString(9500 + i));
        }
        b.description = LanguageManager::getString(31000 + i);

        b.texture.loadFromImage(Resource::convertFrameToImage(frame, palette));
        b.hoverTexture.loadFromImage(Resource::convertFrameToImage(hoverFrame, palette));
        b.selectedTexture.loadFromImage(Resource::convertFrameToImage(selectedFrame, palette));

        b.offset = ScreenPos(frame->hotspot_x, frame->hotspot_y);
        b.hoverOffset = ScreenPos(hoverFrame->hotspot_x, hoverFrame->hotspot_y);
        b.selectedOffset = ScreenPos(selectedFrame->hotspot_x, selectedFrame->hotspot_y);

        b.text.setCharacterSize(15);
        b.text.setFont(SfmlRenderTarget::defaultFont());
        b.text.setFillColor(m_textFillColor);
        b.text.setOutlineColor(m_textOutlineColor);
        b.text.setOutlineThickness(1);
    }

    m_versionText.setCharacterSize(30);
    m_versionText.setFont(SfmlRenderTarget::defaultFont());
    m_versionText.setFillColor(m_textFillColor);
    m_versionText.setOutlineColor(m_textOutlineColor);
    m_versionText.setOutlineThickness(2);
    m_versionText.setString("freeaoe");
    if (isHd) {
        m_versionText.setPosition(ScreenPos(900, 15));
    } else {
        m_versionText.setPosition(ScreenPos(560, 10));
    }

    m_todoText.setCharacterSize(50);
    m_todoText.setFont(SfmlRenderTarget::defaultFont());
    m_todoText.setFillColor(m_textFillColor);
    m_todoText.setOutlineColor(m_textOutlineColor);
    m_todoText.setOutlineThickness(5);
    m_todoText.setString("TODO");
    if (isHd) {
        m_todoText.setPosition(ScreenPos(875, 160));
    } else {
        m_todoText.setPosition(ScreenPos(550, 65));
    }

    m_textButtons[GameTypeChoice::Campaign].text = "Campaign (todo lookup name)";
    m_textButtons[GameTypeChoice::StandardGame].text = "Simple demo map";

    int y = 85;
    if (isHd) {
        y += 80;
    }
    for (int i=0; i<GameTypeChoice::GameTypeCount; i++) {
        if (isHd) {
            m_textButtons[i].rect.x = 800;
        } else {
            m_textButtons[i].rect.x = 460;
        }
        m_textButtons[i].rect.y = y;
        m_textButtons[i].rect.height = 40;
        m_textButtons[i].rect.width = 300;
        y += 65;
    }

    return true;
}

HomeScreen::Button::Type HomeScreen::getSelection()
{
    if (!run()) {
        return Button::Exit;
    }

    if (m_hoveredButton != -1) {
        return Button::Type(m_hoveredButton);
    }

    if (m_selectedButton != -1) {
        return Button::Type(m_selectedButton);
    }

    return Button::Exit;
}

void HomeScreen::render()
{
    for (int i=0; i<Button::TypeCount; i++) {
        sf::Sprite sprite;
        ScreenPos pos = m_buttons[i].rect.topLeft();

        if (i == m_selectedButton) {
            sprite.setTexture(m_buttons[i].selectedTexture);
            pos -= m_buttons[i].selectedOffset;
        } else if (i == m_hoveredButton) {
            sprite.setTexture(m_buttons[i].hoverTexture);
            pos -= m_buttons[i].hoverOffset;
        } else {
            sprite.setTexture(m_buttons[i].texture);
            pos -= m_buttons[i].offset;
        }

        sprite.setPosition(pos);
        m_renderWindow->draw(sprite);

    }
    for (int i=0; i<Button::TypeCount; i++) {
        ScreenPos pos = m_buttons[i].textRect.center();
        sf::FloatRect textRect = m_buttons[i].text.getLocalBounds();
        pos.x -= textRect.width / 2;
        pos.y -= 3 * textRect.height / 4;

        m_buttons[i].text.setPosition(pos);
        m_renderWindow->draw(m_buttons[i].text);
    }

    switch (m_selectedButton) {
    case Button::Singleplayer: {
        for (int i=0; i<GameTypeChoice::GameTypeCount; i++) {
            m_textButtons[i].render(this);
        }
        break;
    }
    case -1:
        break;
    default:
        m_renderWindow->draw(m_todoText);
        break;
    }

    m_renderWindow->draw(m_versionText);
    m_renderWindow->draw(m_description);
}

bool HomeScreen::handleMouseEvent(const sf::Event &event)
{
    const bool missingData = AssetManager::Inst()->missingData();
    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);
        m_hoveredButton = -1;

        for (int i=0; i<Button::TypeCount; i++) {
            if (m_buttons[i].rect.contains(mousePos)) {
                m_hoveredButton = i;
                if (!missingData) {
                    m_description.setString(m_buttons[i].description);
                }
                break;
            }
        }

        if (m_hoveredButton == -1 && !missingData) {
            m_description.setString("");
        }

        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_selectedButton == Button::Singleplayer) {
            for (int i=0; i<GameTypeChoice::GameTypeCount; i++) {
                if (m_textButtons[i].rect.contains(mousePos)) {
                    m_gameType = i;
                    return true;
                }
            }
        }
        switch (m_hoveredButton) {
        case Button::Zone:
            util::openUrl("https://www.voobly.com/", nullptr);
            m_selectedButton = m_hoveredButton;
            return false;
        case Button::Exit:
        case Button::History:
        case Button::Tutorial:
            return true;
        default:
            break;
        }

        m_selectedButton = m_hoveredButton;
        return false;
    }

    return false;
}
