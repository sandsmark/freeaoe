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
#include "resource/ResourceManager.h"
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
    genie::UIFilePtr uiFile = ResourceManager::Inst()->getUIFile("xmain.sin");
    m_slpFile = ResourceManager::Inst()->getSlp(uiFile->backgroundLarge.fileId, ResourceManager::ResourceType::Interface);
    if (!m_slpFile) {
        WARN << "failed to load slp file for home screen";
        return false;
    }

    const genie::PalFile &palette = ResourceManager::Inst()->getPalette(uiFile->paletteFile.id);

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

    m_buttons[Button::Singleplayer].hoverFrame = 11;
    m_buttons[Button::Multiplayer].hoverFrame = 15;
    m_buttons[Button::History].hoverFrame = 31;
    m_buttons[Button::MapEditor].hoverFrame = 27;
    m_buttons[Button::Banner].hoverFrame = 50;
    m_buttons[Button::Exit].hoverFrame = 47;
//    m_buttons[Button::Exit].hoverFrame = 7;
    m_buttons[Button::Tutorial].hoverFrame = 23;
    m_buttons[Button::Options].hoverFrame = 35;
    m_buttons[Button::Zone].hoverFrame = 19;

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
        b.texture.loadFromImage(Resource::convertFrameToImage(frame, palette));
        b.hoverTexture.loadFromImage(Resource::convertFrameToImage(hoverFrame, palette));
        b.offset = ScreenPos(frame->hotspot_x, frame->hotspot_y);
        b.hoverOffset = ScreenPos(hoverFrame->hotspot_x, hoverFrame->hotspot_y);

        b.text.setCharacterSize(15);
        b.text.setFont(SfmlRenderTarget::defaultFont());
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
            m_renderWindow->close();
            continue;
        }

        if (handleMouseEvent(event)) {
            m_renderWindow->close();
            continue;
        }

        m_renderWindow->clear(sf::Color::Black);
        render();
        m_renderWindow->display();
    }

    if (m_currentButton == -1) {
        return Button::Exit;
    }

    return Button::Type(m_currentButton);
}

void HomeScreen::render()
{
    sf::Sprite sprite;
    sprite.setTexture(m_background);
    m_renderWindow->draw(sprite);

    for (int i=0; i<Button::TypeCount; i++) {
        sf::Sprite sprite;
        ScreenPos pos = m_buttons[i].rect.topLeft();

        if (i == m_currentButton) {
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
}

bool HomeScreen::handleMouseEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        ScreenPos mousePos(event.mouseMove.x, event.mouseMove.y);
        m_currentButton = -1;
        for (int i=0; i<Button::TypeCount; i++) {
            if (m_buttons[i].rect.contains(mousePos)) {
                m_currentButton = i;
                break;
            }
        }

        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        return m_currentButton != -1;
    }

    return false;
}
