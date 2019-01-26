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
#include <SFML/Window/Event.hpp>
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

        int frameNum = -1;
        int hlFramenum = -1;
        switch(i) {
        case TitlesScrollbar:
            element.rect.x = 217;
            element.rect.y = 30;
            frameNum = LargeScrollbarTexture;
            break;
        case TitlesPositionIndicator:
            element.rect.x = 210;
            element.rect.y = 40;
            frameNum = ScrollPositionTexture;
            break;
        case TitlesUpButton:
            element.rect.x = 212;
            element.rect.y = 25;
            hlFramenum = ActiveUpButtonTexture;
            frameNum = UpButtonTexture;
            break;
        case TitlesDownButton:
            element.rect.x = 212;
            element.rect.y = 369;
            hlFramenum = ActiveDownButtonTexture;
            frameNum = DownButtonTexture;
            break;

        case TextScrolllbar:
            element.rect.x = 735;
            element.rect.y = 286;
            frameNum = SmallScrollbarTexture;
            break;
        case TextPositionIndicator:
            element.rect.x = 728;
            element.rect.y = 286;
            frameNum = ScrollPositionTexture;
            break;
        case TextUpButton:
            element.rect.x = 730;
            element.rect.y = 271;
            frameNum = UpButtonTexture;
            hlFramenum = ActiveUpButtonTexture;
            break;

        case TextDownButton:
            element.rect.x = 730;
            element.rect.y = 510;
            frameNum = DownButtonTexture;
            hlFramenum = ActiveDownButtonTexture;
            break;
        default:
            frameNum = 0;
            break;
        }

        if (hlFramenum != -1) {
            element.hlTexture.loadFromImage(Resource::convertFrameToImage(slpFile->getFrame(hlFramenum), palette));
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
        m_visibleTitles[i].text.setFont(font);
        m_visibleTitles[i].text.setCharacterSize(s_textSize);
        m_visibleTitles[i].text.setPosition(17, posY);
        m_visibleTitles[i].text.setFillColor(sf::Color::Black);
        m_visibleTitles[i].text.setOutlineThickness(1.5);
        m_visibleTitles[i].text.setOutlineColor(sf::Color::Transparent);
        m_visibleTitles[i].rect = ScreenRect(17, posY, 195, font.getLineSpacing(s_textSize));
        posY += font.getLineSpacing(s_textSize);
    }

    posY = 275;
    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_visibleText[i].setFont(font);
        m_visibleText[i].setCharacterSize(s_textSize);
        m_visibleText[i].setPosition(317, posY);
        m_visibleText[i].setFillColor(sf::Color::Black);
        posY += font.getLineSpacing(s_textSize);
    }

    loadFile(m_sourceFiles[0]);

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
        if (i == m_currentUiElement && m_uiElements[i].hlTexture.getSize().x > 0) {
            sprite.setTexture(m_uiElements[i].hlTexture);
        } else {
            sprite.setTexture(m_uiElements[i].texture);
        }
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
        m_renderWindow->draw(m_visibleTitles[i].text);
    }
}

bool HistoryScreen::handleMouseEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        if (m_pressedUiElement == TitlesPositionIndicator) {
            const int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height/2;
            m_titleScrollOffset = (m_titles.size() - s_numListEntries) * (event.mouseMove.y - m_uiElements[TitlesUpButton].rect.bottom()) / maxY;
            m_titleScrollOffset = std::min(m_titleScrollOffset, int(m_titles.size()) - s_numListEntries);
            m_titleScrollOffset = std::max(m_titleScrollOffset, 0);
            updateVisibleTitles();
            return false;
        }
        if (m_pressedUiElement == TextPositionIndicator) {
            const int maxY = m_uiElements[TextDownButton].rect.y - m_uiElements[TextUpButton].rect.bottom() - m_uiElements[TextPositionIndicator].rect.height/2;
            m_textScrollOffset = (m_textLines.size() - s_numListEntries) * (event.mouseMove.y - m_uiElements[TextUpButton].rect.bottom()) / maxY;
            m_textScrollOffset = std::min(m_textScrollOffset, int(m_textLines.size()) - s_numVisibleTextLines);
            m_textScrollOffset = std::max(m_textScrollOffset, 0);
            updateVisibleText();
            return false;
        }
        m_currentUiElement = InvalidUiElement;
        for (int i=UiElementsCount-1; i>=0; i--) {
            if (m_uiElements[i].rect.contains(ScreenPos(event.mouseMove.x, event.mouseMove.y)) && m_uiElements[i].hlTexture.getSize().x > 0) {
                m_currentUiElement = UiElements(i);
                return false;
            }
        }
        return false;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        m_pressedUiElement = InvalidUiElement;

        for (int i=0; i<s_numListEntries; i++) {
            const int index = i + m_titleScrollOffset;
            if (m_visibleTitles[i].rect.contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
                m_currentEntry = index;
                loadFile(m_sourceFiles[index]);
                updateVisibleTitles();
                return false;
            }
        }

        for (int i=UiElementsCount-1; i>=0; i--) {
            if (!m_uiElements[i].rect.contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
                continue;
            }

            switch (i) {
            case TitlesUpButton:
                if (m_titleScrollOffset > 0) {
                    m_titleScrollOffset--;
                    updateVisibleTitles();
                }

                break;
            case TitlesDownButton:
                if (m_titleScrollOffset < int(m_titles.size()) - s_numListEntries) {
                    m_titleScrollOffset++;
                    updateVisibleTitles();
                }

                break;
            case TitlesScrollbar: {
                const int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height/2;
                m_titleScrollOffset = (m_titles.size() - s_numListEntries) * (event.mouseButton.y - m_uiElements[TitlesUpButton].rect.bottom()) / maxY;
                updateVisibleTitles();
                m_pressedUiElement = TitlesPositionIndicator;
                break;
            }
            case TextUpButton:
                if (m_textScrollOffset > 0) {
                    m_textScrollOffset--;
                    updateVisibleText();
                }
                break;
            case TextDownButton:
                if (m_textScrollOffset < int(m_textLines.size()) - s_numVisibleTextLines) {
                    m_textScrollOffset++;
                    updateVisibleText();
                }
                break;
            case TextScrolllbar: {
                const int maxY = m_uiElements[TextDownButton].rect.y - m_uiElements[TextUpButton].rect.bottom() - m_uiElements[TextPositionIndicator].rect.height/2;
                m_textScrollOffset = (m_textLines.size() - s_numListEntries) * (event.mouseButton.y - m_uiElements[TextUpButton].rect.bottom()) / maxY;
                updateVisibleText();
                m_pressedUiElement = TextPositionIndicator;
                break;
            }
            default:
                continue;
            }


            return false;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        m_pressedUiElement = InvalidUiElement;
    }
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

    updateVisibleText();
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

    int maxY = m_uiElements[TextDownButton].rect.y - m_uiElements[TextUpButton].rect.bottom() - m_uiElements[TextPositionIndicator].rect.height;
    m_uiElements[TextPositionIndicator].rect.y = m_uiElements[TextUpButton].rect.bottom() + maxY * m_textScrollOffset / (m_textLines.size() - s_numVisibleTextLines);
}

void HistoryScreen::updateVisibleTitles()
{
    for (int i=0; i<s_numListEntries; i++) {
        const int index = i + m_titleScrollOffset;

        if (index == m_currentEntry) {
            m_visibleTitles[i].text.setOutlineColor(sf::Color::Yellow);
        } else {
            m_visibleTitles[i].text.setOutlineColor(sf::Color::Transparent);
        }

        if (index >= m_titles.size()) {
            m_visibleTitles[i].text.setString("");
            continue;
        }
        m_visibleTitles[i].text.setString(m_titles[index]);
    }
    int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height;
    m_uiElements[TitlesPositionIndicator].rect.y = m_uiElements[TitlesUpButton].rect.bottom() + maxY * m_titleScrollOffset / (m_titles.size() - s_numListEntries);
}

