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

#include "core/Logger.h"
#include "core/Types.h"
#include "resource/AssetManager.h"
#include "resource/Resource.h"

#include <genie/resource/Color.h>
#include <genie/resource/PalFile.h>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <genie/resource/UIFile.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <vector>

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
    const std::string uiFilename = 'x' + m_uiFileName;

    m_uiFile = AssetManager::Inst()->getUIFile(uiFilename);

    if (m_uiFile) {
        m_uiFileName = uiFilename;
    } else {
        DBG << "Failed to find" << m_uiFileName << "with x prefix, trying without";
        m_uiFile = AssetManager::Inst()->getUIFile(m_uiFileName);
    }

    if (!m_uiFile) {
        WARN << "Unable to load ui file" << m_uiFileName;
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

    if (!m_renderWindow) {
        m_backgroundSlp = AssetManager::Inst()->getSlp(m_uiFile->backgroundLarge.fileId, AssetManager::ResourceType::Interface);
        if (!m_backgroundSlp) {
            DBG << "failed to load slp file for UI screen by ID, trying name";

            std::string backgroundName;
            if (m_uiFile->backgroundLarge.filename != "none") {
                backgroundName = m_uiFile->backgroundLarge.filename;
            } else {
                backgroundName = m_uiFile->backgroundSmall.filename;
            }
            m_backgroundSlp = AssetManager::Inst()->getSlp(backgroundName + ".slp", AssetManager::ResourceType::Interface);
        }
        if (!m_backgroundSlp) {
            WARN << "failed to load slp file for UI screen";
            return false;
        }


        genie::SlpFramePtr backgroundFrame = m_backgroundSlp->getFrame(0);
        if (!backgroundFrame) {
            WARN << "Failed to get frame";
            return false;
        }

        const int width = backgroundFrame->getWidth();
        const int height = backgroundFrame->getHeight();

        m_backgroundSize = Size(width, height);

        m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "freeaoe");
        m_renderWindow->setSize(sf::Vector2u(width, height));
        m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, width, height)));

        DBG << backgroundFrame->getWidth() << backgroundFrame->getHeight();
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
