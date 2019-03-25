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
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

HomeScreen::HomeScreen() :
    UiScreen("xmain.sin")
{

}

bool HomeScreen::init()
{
    if (!UiScreen::init()) {
        return false;
    }

    std::shared_ptr<genie::SlpFile> slpFile = AssetManager::Inst()->getSlp("xmain.slp", AssetManager::ResourceType::Interface);
    if (!slpFile) {
        WARN << "failed to load slp file for home screen";
        return false;
    }

    const genie::PalFile &palette = AssetManager::Inst()->getPalette(m_paletteId);
    m_descriptionRect = ScreenRect(390, 506, 393, 94);
    m_description.setPosition(m_descriptionRect.topLeft());
    m_description.setCharacterSize(10);
    m_description.setFillColor(m_textFillColor);
    m_description.setOutlineColor(m_textOutlineColor);
    m_description.setOutlineThickness(1);
    m_description.setFont(SfmlRenderTarget::defaultFont());

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

    for (int i=0; i<Button::TypeCount; i++) {
        if (i == Button::About) {
            continue; // TODO: need to find where the fuck it's supposed to go
        }

        Button &b = m_buttons[i];

        int frameNum = 10 + i * 4;
        if (i == Button::Banner) {
            frameNum = 49;
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
    m_versionText.setPosition(ScreenPos(560, 10));

    m_todoText.setCharacterSize(50);
    m_todoText.setFont(SfmlRenderTarget::defaultFont());
    m_todoText.setFillColor(m_textFillColor);
    m_todoText.setOutlineColor(m_textOutlineColor);
    m_todoText.setOutlineThickness(5);
    m_todoText.setString("TODO");
    m_todoText.setPosition(ScreenPos(550, 65));

    m_textButtons[TextButton::Campaign].text.setString("Campaign (todo lookup name)");
    m_textButtons[TextButton::StandardGame].text.setString("Simple demo map");

    int y = 85;
    for (int i=0; i<TextButton::ButtonsCount; i++) {
        m_textButtons[i].rect.x = 460;
        m_textButtons[i].rect.y = y;
        m_textButtons[i].rect.height = 40;
        m_textButtons[i].rect.width = 300;

        m_textButtons[i].text.setCharacterSize(17);
        m_textButtons[i].text.setFont(SfmlRenderTarget::defaultFont());
        m_textButtons[i].text.setFillColor(m_textFillColor);
        m_textButtons[i].text.setOutlineColor(m_textOutlineColor);
        m_textButtons[i].text.setOutlineThickness(1);
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
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color(0, 0, 0, m_buttonOpacity * 255));

        const ScreenPos borderOffset(1, 1);
        const int borderWidth = 3;

        sf::RectangleShape horizontalBorder;
        horizontalBorder.setSize(Size(302, borderWidth));

        sf::RectangleShape verticalBorder;
        verticalBorder.setSize(Size(borderWidth, 42));

        for (int i=0; i<TextButton::ButtonsCount; i++) {
            TextButton &button = m_textButtons[i];

            horizontalBorder.setFillColor(m_bevelColor1);
            verticalBorder.setFillColor(m_bevelColor2);
            verticalBorder.setPosition(button.rect.topLeft() - ScreenPos(1, 1));
            m_renderWindow->draw(verticalBorder);
            horizontalBorder.setPosition(button.rect.topLeft() - ScreenPos(1, 1));
            m_renderWindow->draw(horizontalBorder);

            horizontalBorder.setFillColor(m_bevelColor2);
            horizontalBorder.setPosition(button.rect.bottomLeft() + ScreenPos(-1, 1 - borderWidth));
            m_renderWindow->draw(horizontalBorder);
            verticalBorder.setFillColor(m_bevelColor1);
            verticalBorder.setPosition(button.rect.topRight() + ScreenPos(1 - borderWidth, -1));
            m_renderWindow->draw(verticalBorder);

            rect.setSize(button.rect.size());
            rect.setPosition(button.rect.topLeft());
            m_renderWindow->draw(rect);

            ScreenPos pos = button.rect.center();
            sf::FloatRect textRect = m_buttons[i].text.getLocalBounds();
            pos.x -= textRect.width;
            pos.y -= 3 * textRect.height / 4;
            button.text.setPosition(pos);
            m_renderWindow->draw(button.text);
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
    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);
        m_hoveredButton = -1;

        for (int i=0; i<Button::TypeCount; i++) {
            if (m_buttons[i].rect.contains(mousePos)) {
                m_hoveredButton = i;
                m_description.setString(m_buttons[i].description);
                break;
            }
        }

        if (m_hoveredButton == -1) {
            m_description.setString("");
        }

        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_selectedButton == Button::Singleplayer) {
            for (int i=0; i<TextButton::ButtonsCount; i++) {
                if (m_textButtons[i].rect.contains(mousePos)) {
                    m_gameType = i;
                    return true;
                }
            }
        }
        switch (m_hoveredButton) {
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
