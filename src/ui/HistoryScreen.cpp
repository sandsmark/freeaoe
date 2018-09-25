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
#include "HistoryScreen.h"
#include "resource/LanguageManager.h"
#include "render/SfmlRenderTarget.h"
#include <SFML/Graphics/Sprite.hpp>
#include "core/Utility.h"

#include <fstream>

HistoryScreen::HistoryScreen() :
    UiScreen("scr_hist.sin")
{
}

bool HistoryScreen::init(const std::string &filesDir)
{
    if (!std::filesystem::exists(filesDir)) {
        WARN << filesDir << "does not exist";
        return false;
    }
    if (!UiScreen::init()) {
        return false;
    }

    std::shared_ptr<genie::SlpFile> slpFile = AssetManager::Inst()->getSlp("btn_hist.slp", AssetManager::ResourceType::Interface);
    if (!slpFile) {
        WARN << "failed to load buttons";
        return false;
    }

    if (slpFile->getFrameCount() < 7) {
        WARN << "not enough frames in button SLP" << slpFile->getFrameCount();
        return false;
    }

    const genie::PalFile &palette = AssetManager::Inst()->getPalette(m_paletteId);

    for (int i=0; i<UiElementsCount; i++) {
        UiElement &element = m_uiElements[i];

        int frameNum = i;
        switch(i) {
        case LargeScrollbar:
            element.rect.x = 218;
            element.rect.y = 29;
            break;
        case UpButton:
            element.rect.x = 218;
            element.rect.y = 29;
            break;
        case ActiveUpButton:
            element.rect.x = 218;
            element.rect.y = 29;
            break;
        case DownButton:
            element.rect.x = 218;
            element.rect.y = 350;
            break;
        case ActiveDownButton:
            element.rect.x = 218;
            element.rect.y = 350;
            break;
        case SmallScrollbar:
            element.rect.x = 684;
            element.rect.y = 300;
            break;
        case ScrollPosition:
            element.rect.x = 218;
            element.rect.y = 50;
            break;
        case UpButton2:
            element.rect.x = 218;
            element.rect.y = 29;
            frameNum = UpButton;
            break;
        case ActiveUpButton2:
            element.rect.x = 218;
            element.rect.y = 29;
            frameNum = ActiveUpButton;
            break;
        case DownButton2:
            element.rect.x = 218;
            element.rect.y = 29;
            frameNum = DownButton;
            break;
        case ActiveDownButton2:
            element.rect.x = 218;
            element.rect.y = 29;
            frameNum = ActiveDownButton;
            break;

        default:
            frameNum = 0;
            break;
        }

        const genie::SlpFramePtr &frame = slpFile->getFrame(frameNum);
        element.texture.loadFromImage(Resource::convertFrameToImage(frame, palette));
        element.rect.width = frame->getWidth();
        element.rect.height = frame->getHeight();
    }

    int numEntries = std::stoi(LanguageManager::getString(20310));

    for (int i=0; i<numEntries; i++) {
        m_titles.push_back(LanguageManager::getString(20310 + 1 + i));
    }

    for (int i=0; i<numEntries; i++) {
        std::string compareFilename = util::toLowercase(LanguageManager::getString(20410 + 1 + i));

        std::string filePath;
        for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(filesDir)) {
            std::string candidate = util::toLowercase(entry.path().filename().string());
            if (candidate == compareFilename) {
                filePath = entry.path().string();
                break;
            }
        }

        if (filePath.empty()) {
            WARN << "failed to find" << compareFilename;
        }

        m_sourceFiles.push_back(filePath);
    }

    const sf::Font &font = SfmlRenderTarget::defaultFont();

    float posY = 22;
    for (int i=0; i<s_numListEntries; i++) {
        m_visibleTitles[i].setFont(font);
        m_visibleTitles[i].setCharacterSize(s_textSize);
        m_visibleTitles[i].setPosition(17, posY);
        m_visibleTitles[i].setFillColor(sf::Color::Black);
        posY += font.getLineSpacing(s_textSize);
    }

    posY = 280;
    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_visibleText[i].setFont(font);
        m_visibleText[i].setCharacterSize(s_textSize);
        m_visibleText[i].setPosition(317, posY);
        m_visibleText[i].setFillColor(sf::Color::Black);
        posY += font.getLineSpacing(s_textSize);
    }

    loadFile(m_sourceFiles[0]);

    updateVisibleText();
    updateVisibleTitles();

    return true;
}

void HistoryScreen::display()
{
    run();
}


void HistoryScreen::render()
{
    for (int i=0; i<UiElementsCount; i++) {
        sf::Sprite sprite;
        sprite.setTexture(m_uiElements[i].texture);
        sprite.setPosition(m_uiElements[i].rect.topLeft());
        m_renderWindow->draw(sprite);
    }
//    sf::Sprite sprite;
//    sprite.setTexture(m_largeScrollbar.texture);
//    sprite.setPosition(218, 29);
//    m_renderWindow->draw(sprite);

    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_renderWindow->draw(m_visibleText[i]);
    }
    for (int i=0; i<s_numListEntries; i++) {
        m_renderWindow->draw(m_visibleTitles[i]);
    }
}

bool HistoryScreen::handleMouseEvent(const sf::Event &event)
{
    return false;
}

void HistoryScreen::loadFile(const std::string &filePath)
{
    m_textLines.clear();

    std::ifstream file(filePath, std::ios_base::binary);
    if (!file.is_open()) {
        WARN << "failed to open" << filePath;
        return;
    }

    TextLine currentLine;

    float currentWidth = 0.f;
    const sf::Font &font = SfmlRenderTarget::defaultFont();

    while (!file.eof()) {
        char character = file.get();

        if (character == '\r') {
            continue;
        }

        if (character == '\n') {
            m_textLines.push_back(std::move(currentLine));
            currentWidth = 0;
            continue;
        }
        // fixme bold
        const float width = font.getGlyph(character, s_textSize, false).advance;
        if (currentWidth + width > s_textWidth) {
            m_textLines.push_back(std::move(currentLine));
            currentWidth = 0;
        } else {
            currentWidth += width;
        }

        currentLine.text += character;
    }

    if (!currentLine.text.empty()) {
        m_textLines.push_back(std::move(currentLine));
    }

    // FIXME: I'm lazy, parse good, different styling in a single line
    for (TextLine &line : m_textLines) {
        if (line.text.empty()) {
            continue;
        }
        if (line.text[0] != '<') {
            continue;
        }
        if (util::stringStartsWith(util::toLowercase(line.text), "<b>")) {
            line.bold = true;
        } else if (util::stringStartsWith(util::toLowercase(line.text), "<i>")) {
            line.italic = true;
        }
        line.text = util::stringReplace(line.text, "<b>", "");
        line.text = util::stringReplace(line.text, "<i>", "");
        line.text = util::stringReplace(line.text, "<B>", "");
        line.text = util::stringReplace(line.text, "<I>", "");
    }
}

void HistoryScreen::updateVisibleText()
{
    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_visibleText[i].setStyle(sf::Text::Regular);

        const int index = i + m_textScrollOffset;
        if (index >= m_textLines.size()) {
            m_visibleText[i].setString("");
            continue;
        }

        m_visibleText[i].setString(m_textLines[index].text);

        if (m_textLines[index].bold) {
            m_visibleText[i].setStyle(m_visibleText[i].getStyle() | sf::Text::Bold);
        }

        if (m_textLines[index].italic) {
            m_visibleText[i].setStyle(m_visibleText[i].getStyle() | sf::Text::Italic);
        }
    }
}

void HistoryScreen::updateVisibleTitles()
{
    for (int i=0; i<s_numListEntries; i++) {
        const int index = i + m_titleScrollOffset;
        if (index >= m_titles.size()) {
            m_visibleTitles[i].setString("");
            continue;
        }
        m_visibleTitles[i].setString(m_titles[index]);
    }
}

