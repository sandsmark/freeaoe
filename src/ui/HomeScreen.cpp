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
#include "render/SfmlRenderTarget.h"
#include <genie/resource/UIFile.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

HomeScreen::HomeScreen()
{

}

bool HomeScreen::init()
{
    genie::UIFilePtr uiFile = AssetManager::Inst()->getUIFile("xmain.sin");
    m_slpFile = AssetManager::Inst()->getSlp(uiFile->backgroundLarge.fileId, AssetManager::ResourceType::Interface);
    if (!m_slpFile) {
        WARN << "failed to load slp file for home screen";
        return false;
    }

    const genie::PalFile &palette = AssetManager::Inst()->getPalette(uiFile->paletteFile.id);

    genie::SlpFramePtr backgroundFrame = m_slpFile->getFrame(0);
    if (!backgroundFrame) {
        WARN << "Failed to get frame";
        return false;
    }

    const int width = backgroundFrame->getWidth();
    const int height = backgroundFrame->getHeight();

    m_renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "freeaoe");
    m_renderWindow->setSize(sf::Vector2u(width, height));
    m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));

    m_background.loadFromImage(Resource::convertFrameToImage(backgroundFrame, palette));

    DBG << uiFile->stateColor1.r << uiFile->stateColor1.g << uiFile->stateColor1.b;
    sf::Color textFillColor(uiFile->textColor1.r, uiFile->textColor1.g, uiFile->textColor1.b);
    sf::Color textOutlineColor(uiFile->textColor2.r, uiFile->textColor2.g, uiFile->textColor2.b);

    m_descriptionRect = ScreenRect(390, 506, 393, 94);
    m_description.setPosition(m_descriptionRect.topLeft());
    m_description.setCharacterSize(10);
    m_description.setFillColor(textFillColor);
    m_description.setOutlineColor(textOutlineColor);
    m_description.setOutlineThickness(1);
    m_description.setFont(SfmlRenderTarget::defaultFont());

    // These are fun to figure out
    m_buttons[Button::Singleplayer].rect = ScreenRect(309, 12, 120, 189);
    m_buttons[Button::Multiplayer].rect = ScreenRect(263, 217, 97, 131);
    m_buttons[Button::History].rect = ScreenRect(103, 164, 102, 97);
    m_buttons[Button::MapEditor].rect = ScreenRect(197, 273, 70, 67);
    m_buttons[Button::Banner].rect = ScreenRect(0, 0, 427, 170);
    m_buttons[Button::Exit].rect = ScreenRect(5, 535, 153, 65);
    m_buttons[Button::Tutorial].rect = ScreenRect(0, 6, 125, 187);
    m_buttons[Button::Options].rect = ScreenRect(101, 347, 95, 100);
    m_buttons[Button::Zone].rect = ScreenRect(271, 367, 67, 64);

    // These are fun to figure out
    m_buttons[Button::Singleplayer].textRect = ScreenRect(277, 21, 180, 18);
    m_buttons[Button::Multiplayer].textRect = ScreenRect(222, 222, 180, 18);
    m_buttons[Button::History].textRect = ScreenRect(64, 169, 180, 18);
    m_buttons[Button::MapEditor].textRect = ScreenRect(142, 276, 180, 18);
    m_buttons[Button::Exit].textRect = ScreenRect(0, 562, 160, 18);
    m_buttons[Button::Tutorial].textRect = ScreenRect(0, 16, 120, 18);
    m_buttons[Button::Options].textRect = ScreenRect(56, 351, 180, 18);
    m_buttons[Button::Zone].textRect = ScreenRect(213, 369, 180, 18);

    m_buttons[Button::Singleplayer].text.setString(LanguageManager::getString(9500));
    m_buttons[Button::Multiplayer].text.setString(LanguageManager::getString(9501));
    m_buttons[Button::History].text.setString(LanguageManager::getString(9505));
    m_buttons[Button::MapEditor].text.setString(LanguageManager::getString(9504));
    m_buttons[Button::Exit].text.setString(LanguageManager::getString(9509));
    m_buttons[Button::Tutorial].text.setString(LanguageManager::getString(9503));
    m_buttons[Button::Options].text.setString(LanguageManager::getString(9506));
    m_buttons[Button::Zone].text.setString(LanguageManager::getString(9502));

    m_buttons[Button::Singleplayer].description = LanguageManager::getString(31000);
    m_buttons[Button::Multiplayer].description = LanguageManager::getString(31001);
    m_buttons[Button::History].description = LanguageManager::getString(31005);
    m_buttons[Button::MapEditor].description = LanguageManager::getString(31004);
    m_buttons[Button::Banner].description = LanguageManager::getString(31008);
    m_buttons[Button::Exit].description = LanguageManager::getString(31009);
    m_buttons[Button::Tutorial].description = LanguageManager::getString(31003);
    m_buttons[Button::Options].description = LanguageManager::getString(31006);
    m_buttons[Button::Zone].description = LanguageManager::getString(31002);

    // Less fun
    m_buttons[Button::Singleplayer].frame = 10;
    m_buttons[Button::Multiplayer].frame = 14;
    m_buttons[Button::History].frame = 30;
    m_buttons[Button::MapEditor].frame = 26;
    m_buttons[Button::Banner].frame = 49;
    m_buttons[Button::Exit].frame = 46;
    m_buttons[Button::Tutorial].frame = 22;
    m_buttons[Button::Options].frame = 34;
    m_buttons[Button::Zone].frame = 18;

    m_buttons[Button::Singleplayer].hoverFrame = 12;
    m_buttons[Button::Multiplayer].hoverFrame = 16;
    m_buttons[Button::History].hoverFrame = 32;
    m_buttons[Button::MapEditor].hoverFrame = 28;
    m_buttons[Button::Banner].hoverFrame = 51;
    m_buttons[Button::Exit].hoverFrame = 48;
    m_buttons[Button::Tutorial].hoverFrame = 24;
    m_buttons[Button::Options].hoverFrame = 36;
    m_buttons[Button::Zone].hoverFrame = 20;

    m_buttons[Button::Singleplayer].selectedFrame = 11;
    m_buttons[Button::Multiplayer].selectedFrame = 15;
    m_buttons[Button::History].selectedFrame = 31;
    m_buttons[Button::MapEditor].selectedFrame = 27;
    m_buttons[Button::Banner].selectedFrame = 50;
    m_buttons[Button::Exit].selectedFrame = 47;
    m_buttons[Button::Tutorial].selectedFrame = 23;
    m_buttons[Button::Options].selectedFrame = 35;
    m_buttons[Button::Zone].selectedFrame = 19;

    // meh ok
    m_buttons[Button::Singleplayer].frame = 10;
    m_buttons[Button::Multiplayer].frame = 14;
    m_buttons[Button::History].frame = 30;
    m_buttons[Button::MapEditor].frame = 26;
    m_buttons[Button::Banner].frame = 49;
    m_buttons[Button::Exit].frame = 46;
    m_buttons[Button::Tutorial].frame = 22;
    m_buttons[Button::Options].frame = 34;
    m_buttons[Button::Zone].frame = 18;

    for (int i=0; i<Button::TypeCount; i++) {
        Button &b = m_buttons[i];
        const genie::SlpFramePtr &frame = m_slpFile->getFrame(b.frame);
        const genie::SlpFramePtr &hoverFrame = m_slpFile->getFrame(b.hoverFrame);
        const genie::SlpFramePtr &selectedFrame = m_slpFile->getFrame(b.selectedFrame);

        b.texture.loadFromImage(Resource::convertFrameToImage(frame, palette));
        b.hoverTexture.loadFromImage(Resource::convertFrameToImage(hoverFrame, palette));
        b.selectedTexture.loadFromImage(Resource::convertFrameToImage(selectedFrame, palette));

        b.offset = ScreenPos(frame->hotspot_x, frame->hotspot_y);
        b.hoverOffset = ScreenPos(hoverFrame->hotspot_x, hoverFrame->hotspot_y);
        b.selectedOffset = ScreenPos(selectedFrame->hotspot_x, selectedFrame->hotspot_y);

        b.text.setCharacterSize(15);
        b.text.setFont(SfmlRenderTarget::defaultFont());
        b.text.setFillColor(textFillColor);
        b.text.setOutlineColor(textOutlineColor);
        b.text.setOutlineThickness(1);
    }

    return true;
}

HomeScreen::Button::Type HomeScreen::getSelection()
{
    while (m_renderWindow->isOpen()) {
        // Process events
        sf::Event event;
        if (!m_renderWindow->waitEvent(event)) {
            WARN << "failed to get event";
            break;
        }

        if (event.type == sf::Event::Closed) {
            return Button::Exit;
        }

        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
            sf::Vector2f mappedPos = m_renderWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            event.mouseButton.x = mappedPos.x;
            event.mouseButton.y = mappedPos.y;
        }

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mappedPos = m_renderWindow->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            event.mouseMove.x = mappedPos.x;
            event.mouseMove.y = mappedPos.y;
        }

        if (handleMouseEvent(event)) {
            m_renderWindow->close();
            continue;
        }

        m_renderWindow->clear(sf::Color::Black);
        render();
        m_renderWindow->display();
    }

    if (m_hoveredButton != -1) {
        return Button::Type(m_hoveredButton);

    }

    return Button::Exit;
}

void HomeScreen::render()
{
    sf::Sprite sprite;
    sprite.setTexture(m_background);
    m_renderWindow->draw(sprite);

    for (int i=0; i<Button::TypeCount; i++) {
        sf::Sprite sprite;
        ScreenPos pos = m_buttons[i].rect.topLeft();

        if (i == m_hoveredButton) {
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

        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        return m_hoveredButton != -1;
    }

    return false;
}
