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

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <genie/util/Utility.h>
#include <memory>

#include "audio/AudioPlayer.h"
#include "TextButton.h"
#include "core/Logger.h"
#include "core/Utility.h"
#include "global/Config.h"
#include "render/SfmlRenderTarget.h"
#include "resource/AssetManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"
#include "resource/Resource.h"

namespace genie {
class PalFile;
}  // namespace genie

HomeScreen::~HomeScreen()
{
    AudioPlayer::instance().stopStream("open.mp3");
    AudioPlayer::instance().stopStream("open.mid"); // I'm lazy, sue me
}

HomeScreen::HomeScreen() :
    UiScreen("main.sin")
{

}

bool HomeScreen::init()
{
    if (!UiScreen::init()) {
        return false;
    }

    if (!AudioPlayer::instance().playStream("open.mp3")) {
        AudioPlayer::instance().playMidi("open.mid");
    }

    const bool isHd = DataManager::Inst().isHd();

    if (!m_backgroundSlp) {
        WARN << "failed to load slp file for home screen";
        return false;
    }

    const genie::PalFile &palette = AssetManager::Inst()->getPalette(m_paletteId);
    DBG << "palette:" << m_paletteId;

    if (isHd) {
        m_descriptionRect = ScreenRect(675, 650, 475, 100);
    } else if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
        m_descriptionRect = ScreenRect(410, 510, 375, 80);
    } else {
        m_descriptionRect = ScreenRect(390, 506, 393, 94);
    }
    m_description.setPosition(m_descriptionRect.topLeft());
    m_description.setOutlineColor(m_textOutlineColor);
    m_description.setFillColor(m_textFillColor);
    m_description.setOutlineThickness(1);
    m_description.setFont(SfmlRenderTarget::uiFont());
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

        for (int i=0; i<Button::TypeCount; i++) {
            if (i == Button::Banner) {
                m_buttons[i].frame = 50;
            } else {
                m_buttons[i].frame = 10 + i * 4;
            }
        }
    } else if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
        // TODO: these are a bit off, but I can' be bothered to try to match exactly
        m_buttons[Button::Singleplayer].rect = { 278,  210, 138, 80 };
        m_buttons[Button::Singleplayer].textRect = { 250,  300, 180,  18 };

        m_buttons[Button::Multiplayer].rect =  { 217, 356, 177, 147 };
        m_buttons[Button::Multiplayer].textRect =  { 194, 400, 180,  18 };

        m_buttons[Button::Zone].rect =         { 70, 84,  185,  90 };
        m_buttons[Button::Zone].textRect =         { 20, 110, 50,  18 };

        m_buttons[Button::Tutorial].rect =     {   316, 71, 100, 124 };
        m_buttons[Button::Tutorial].textRect =     {   265,  60, 120,  18 };

        m_buttons[Button::MapEditor].rect =    { 150, 515,  214,  74 };
        m_buttons[Button::MapEditor].textRect =    { 200, 550, 180,  18 };

        m_buttons[Button::History].rect =      { 58, 196, 174,  153 };
        m_buttons[Button::History].textRect =      {  30, 250, 180,  18 };

        m_buttons[Button::Options].rect =      { 0, 355,  141, 169 };
        m_buttons[Button::Options].textRect =      {  0, 470, 100,  18 };

        m_buttons[Button::Banner].rect =       {   0,   0, 141, 61 };

        m_buttons[Button::Exit].rect =         {   5, 535, 93,  50 };
        m_buttons[Button::Exit].textRect =         {   0, 562, 90,  18 };

        // Frame order don't make sense
        m_buttons[Button::Singleplayer].frame = 34;
        m_buttons[Button::Multiplayer].frame = 14;
        m_buttons[Button::Zone].frame = 18;
        m_buttons[Button::Tutorial].frame = 22;
        m_buttons[Button::MapEditor].frame = 26;
        m_buttons[Button::History].frame = 30;
        m_buttons[Button::Options].frame = 10;
        m_buttons[Button::Banner].frame = 49;
        m_buttons[Button::Exit].frame = 46;
    } else if (DataManager::Inst().gameVersion() < genie::GV_TC) {
        // These are fun to figure out.
        // Aka. found by trial and error (extract image, try to count pixels in
        // your favorite image viewer, discover that they're wrong, and adjust
        // and try again until you rip your hair out).
        m_buttons[Button::Singleplayer].rect = { 306,  7, 120, 189 };
        m_buttons[Button::Multiplayer].rect =  { 258, 214,  97, 131 };
        m_buttons[Button::Zone].rect =         { 268, 364,  67,  64 };
        m_buttons[Button::Tutorial].rect =     {   0,   4, 125, 187 };
        m_buttons[Button::MapEditor].rect =    { 194, 271,  70,  67 };
        m_buttons[Button::History].rect =      { 100, 161, 102,  97 };
        m_buttons[Button::Options].rect =      { 97, 344,  95, 100 };
        m_buttons[Button::Banner].rect =       {   0,   0, 427, 170 };
        m_buttons[Button::Exit].rect =         {   0, 533, 153,  65 };

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
            if (i == Button::Banner) {
                m_buttons[i].frame = 49;
            } else {
                m_buttons[i].frame = 10 + i * 4;
            }
        }
    } else {
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
            if (i == Button::Banner) {
                m_buttons[i].frame = 49;
            } else {
                m_buttons[i].frame = 10 + i * 4;
            }
        }
    }

    // Indicate which aren't implemented yet
    //m_buttons[Button::MapEditor].text.setStyle(sf::Text::StrikeThrough);
    m_buttons[Button::Multiplayer].text.setStyle(sf::Text::StrikeThrough);
    m_buttons[Button::Options].text.setStyle(sf::Text::StrikeThrough);


    for (int i=0; i<Button::TypeCount; i++) {
        if (i == Button::About) {
            continue; // TODO: need to find where the fuck it's supposed to go
        }

        Button &b = m_buttons[i];
        int frameNum = b.frame;
        if (frameNum == -1) {
            continue;
        }

        if (frameNum + 3 > m_backgroundSlp->getFrameCount()) {
            WARN << "Invalid frame index" << frameNum << "for" << i << "max is" << m_backgroundSlp->getFrameCount();
            continue;
        }

        const genie::SlpFramePtr &frame = m_backgroundSlp->getFrame(frameNum);
        const genie::SlpFramePtr &selectedFrame = m_backgroundSlp->getFrame(frameNum + 1);
        const genie::SlpFramePtr &hoverFrame = m_backgroundSlp->getFrame(frameNum + 2);

        if (i == Button::Banner) {
            b.text.setString(LanguageManager::getString(9500 + 9));
        } else {
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
        b.text.setFont(SfmlRenderTarget::uiFont());
        b.text.setFillColor(m_textFillColor);
        b.text.setOutlineColor(m_textOutlineColor);
        b.text.setOutlineThickness(1);
    }

    m_versionText.setCharacterSize(30);
    m_versionText.setFont(SfmlRenderTarget::uiFont());
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
    m_todoText.setFont(SfmlRenderTarget::uiFont());
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
        if (m_buttons[i].frame == -1) {
            continue;
        }
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
        if (m_buttons[i].frame == -1) {
            continue;
        }
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
        case Button::MapEditor:
            return true;
        default:
            break;
        }

        m_selectedButton = m_hoveredButton;
        return false;
    }

    return false;
}
