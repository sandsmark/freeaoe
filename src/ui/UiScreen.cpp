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
#include "UiScreen.h"
#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"
#include "render/SfmlRenderTarget.h"
#include <genie/resource/UIFile.h>
#include <genie/resource/PalFile.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

UiScreen::UiScreen(const char *uiFile) :
    m_uiFileName(uiFile)
{

}

static sf::Color convertColor(const genie::Color &color)
{
    return sf::Color(color.r, color.g, color.b);
}

bool UiScreen::init()
{
    m_uiFile = AssetManager::Inst()->getUIFile(m_uiFileName);
    if (!m_uiFile) {
        WARN << "Unable to load ui file";
        return false;
    }

    m_buttonOpacity = m_uiFile->shadePercent / 100.;

    m_textFillColor = sf::Color(m_uiFile->textColor1.r, m_uiFile->textColor1.g, m_uiFile->textColor1.b);
    m_textOutlineColor = sf::Color(m_uiFile->textColor2.r, m_uiFile->textColor2.g, m_uiFile->textColor2.b);

//    m_bevelColor1 = sf::Color(m_uiFile->bevelColor1.r, m_uiFile->bevelColor1.g, m_uiFile->bevelColor1.b);
//    m_bevelColor2 = sf::Color(m_uiFile->bevelColor2.r, m_uiFile->bevelColor2.g, m_uiFile->bevelColor2.b);

    m_paletteId = m_uiFile->paletteFile.id;
    const genie::PalFile &palette = AssetManager::Inst()->getPalette(m_paletteId);
    const std::vector<genie::Color> &colors = palette.getColors();

    m_bevelColor1a = convertColor(colors[m_uiFile->bevelColor1.r]);
    m_bevelColor1b = convertColor(colors[m_uiFile->bevelColor1.g]);
    m_bevelColor1c = convertColor(colors[m_uiFile->bevelColor1.b]);

    m_bevelColor2a = convertColor(colors[m_uiFile->bevelColor2.r]);
    m_bevelColor2b = convertColor(colors[m_uiFile->bevelColor2.g]);
    m_bevelColor2c = convertColor(colors[m_uiFile->bevelColor2.b]);

    m_pressOffset = m_uiFile->backgroundPosition;

    genie::Color color = palette.getColors().at(m_uiFile->bevelColor1.r);


    if (!m_renderWindow) {
        std::shared_ptr<genie::SlpFile> slpFile = AssetManager::Inst()->getSlp(m_uiFile->backgroundLarge.fileId, AssetManager::ResourceType::Interface);
        if (!slpFile) {
            WARN << "failed to load slp file for home screen";
            return false;
        }


        genie::SlpFramePtr backgroundFrame = slpFile->getFrame(0);
        if (!backgroundFrame) {
            WARN << "Failed to get frame";
            return false;
        }

        const int width = backgroundFrame->getWidth();
        const int height = backgroundFrame->getHeight();
        m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "freeaoe");
        m_renderWindow->setSize(sf::Vector2u(width, height));
        m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));

        m_background.loadFromImage(Resource::convertFrameToImage(backgroundFrame, palette));
    }


    return true;
}

void UiScreen::setRenderWindow(const std::shared_ptr<sf::RenderWindow> &renderWindow)
{
    m_renderWindow = renderWindow;
}

bool UiScreen::run()
{
    sf::Sprite sprite;
    sprite.setTexture(m_background);

    while (m_renderWindow->isOpen()) {
        // Process events
        sf::Event event;
        if (!m_renderWindow->waitEvent(event)) {
            WARN << "failed to get event";
            break;
        }

        if (event.type == sf::Event::Closed) {
            return false;
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

        if (event.type == sf::Event::KeyPressed) {
            handleKeyEvent(event);
        }

        if (handleMouseEvent(event)) {
            m_renderWindow->close();
            continue;
        }

        m_renderWindow->clear(sf::Color::Black);
        m_renderWindow->draw(sprite);
        render();
        m_renderWindow->display();
    }

    return true;
}
