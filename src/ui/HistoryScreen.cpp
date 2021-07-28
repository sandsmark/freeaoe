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

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <memory>
#include <unordered_set>
#include <utility>

#include "core/Logger.h"
#include "core/Utility.h"
#include "render/SfmlRenderTarget.h"
#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"
#include "resource/Resource.h"
#include "resource/DataManager.h"

HistoryScreen::HistoryScreen() :
    UiScreen("scr_hist.sin")
{
}

bool HistoryScreen::init(const std::string &filesDir)
{
    if (filesDir.empty()) {
        WARN << "No history dir passed";
        return false;
    }
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
        case MainScreenButton:
            continue;
        default:
            frameNum = 0;
            break;
        }

        if (hlFramenum != -1) {
            element.hoverTexture.loadFromImage(Resource::convertFrameToImage(slpFile->getFrame(hlFramenum), palette));
        }

        const genie::SlpFramePtr &frame = slpFile->getFrame(frameNum);
        element.texture.loadFromImage(Resource::convertFrameToImage(frame, palette));
        element.rect.width = frame->getWidth();
        element.rect.height = frame->getHeight();
    }
    SlpFilePtr aokSlp = AssetManager::Inst()->getSlp("hist_pic.sin", AssetManager::ResourceType::Interface);
    DBG << "aok hist pic frames:" << aokSlp->getFrameCount();

    SlpFilePtr aocSlp = AssetManager::Inst()->getSlp("hist_picx.sin", AssetManager::ResourceType::Interface);
    DBG << "aoc hist pic frames:" << aocSlp->getFrameCount();

    int numEntries = std::stoi(LanguageManager::getString(20310));
    DBG << "entries" << numEntries;

    // For some reason there's duplicates, with blank illustrations, so we need to skip these
    std::unordered_set<std::string> addedItems;
    int addedIndex = 0;
    for (int i=0; i<numEntries; i++) {
        std::string title = LanguageManager::getString(20310 + 1 + i);
        if (util::trimString(title).empty()) {
            DBG << "Skipping empty" << i;
            continue;
        } else if (addedItems.count(title)) {
            DBG << "Duplicate" << title << i;
            continue;
        }

        size_t primaryIllustrationIndex = 0;
        size_t secondaryIllustrationIndex = 0;
        size_t illustrationSource = 1;

        if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
            primaryIllustrationIndex = addedIndex;
            secondaryIllustrationIndex = addedIndex + 51;
        } else {
            primaryIllustrationIndex = i;
            secondaryIllustrationIndex = i + 51;
        }

        // Based on info from http://aok.heavengames.com/blacksmith/showfile.php?fileid=11916
        // Can't really get it to make sense (seems to get off by one somewhere),
        // but I don't have any better idea either.
        // Might be because of how the strings .txt file overriding works, though I tried different
        // things there as well.
        if (DataManager::Inst().isHd()) {
            std::vector<std::string> illustrationInfo = util::stringSplit(LanguageManager::getString(20810 + 1 + i), ',');
            if (illustrationInfo.size() != 3) {
                WARN << "Invalid illustration info for" << title << LanguageManager::getString(20810 + 1 + i) << (20810 + 1 + i);
                addedIndex++;
                continue;
            }

            DBG << "from file:" << illustrationInfo[0] << illustrationInfo[1] << illustrationInfo[2];
            DBG << "Actual" << primaryIllustrationIndex << secondaryIllustrationIndex;
            try {
                illustrationSource = std::stoi(util::trimString(illustrationInfo[0]));
                primaryIllustrationIndex = std::stoi(util::trimString(illustrationInfo[1]));
                secondaryIllustrationIndex = std::stoi(util::trimString(illustrationInfo[2]));
            } catch (const std::out_of_range &e) {
                WARN << "exceptions are dumb" << e.what();
                continue;
            }
        }

        SlpFilePtr slpSource;
        switch(illustrationSource) {
        case 1:
            slpSource = aokSlp;
            break;
        case 2:
            slpSource = aocSlp;
            break;
        default:
            WARN << "Invalid source slp for illustrations" << illustrationSource;
            continue;
        }
        if (primaryIllustrationIndex >= slpSource->getFrameCount()) {
            WARN << primaryIllustrationIndex << "out of range for" << slpSource->getFrameCount();
            continue;
        }
        if (secondaryIllustrationIndex >= slpSource->getFrameCount()) {
            WARN << "secondary" << secondaryIllustrationIndex << "is out of range for" << slpSource->getFrameCount();
            continue;
        }


        HistoryEntry entry;
        entry.title = title;

        entry.illustration.loadFromImage(Resource::convertFrameToImage(slpSource->getFrame(primaryIllustrationIndex), palette));
        entry.secondaryIllustration.loadFromImage(Resource::convertFrameToImage(slpSource->getFrame(secondaryIllustrationIndex), palette));

        std::string compareFilename = util::toLowercase(LanguageManager::getString(20410 + 1 + i));
        if (!util::trimString(compareFilename).empty()) {

            std::string filePath;
            for (const std::filesystem::directory_entry &candidateEntry : std::filesystem::directory_iterator(filesDir)) {
                std::string candidate = util::toLowercase(candidateEntry.path().filename().string());
                if (candidate.find("utf8") != std::string::npos) {
                    //                candidate = util::stringReplace(candidate, "-utf8", "");
                }
                if (candidate == compareFilename) {
                    filePath = candidateEntry.path().string();
                    break;
                }
            }

            if (filePath.empty()) {
                WARN << "failed to find" << compareFilename;
            } else {
                addedIndex++;
            }
            entry.filename = filePath;
        }

        m_historyEntries.push_back(entry);
        addedItems.insert(title);

        addedIndex++;
    }
    DBG << "Latest added index" << addedIndex;

    slpFile = AssetManager::Inst()->getSlp(50768, AssetManager::ResourceType::Interface);
    if (!slpFile) {
        WARN << "Failed to load button bg";
        return false;
    }

    const sf::Font &stylishFont = DataManager::Inst().gameVersion() >= genie::GV_SWGB ?
            SfmlRenderTarget::plainFont() :
            SfmlRenderTarget::stylishFont();

    m_titleText.setPosition(390, 25);
    m_titleText.setCharacterSize(20);
    m_titleText.setFont(stylishFont);
    m_titleText.setFillColor(sf::Color::Black);

    float posY = 30;
    for (int i=0; i<s_numListEntries; i++) {
        m_visibleTitles[i].text.setCharacterSize(s_titlesTextSize);
        m_visibleTitles[i].text.setPosition(17, posY);
        m_visibleTitles[i].rect = ScreenRect(17, posY, 195, stylishFont.getLineSpacing(s_titlesTextSize));

        if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
            m_visibleTitles[i].text.setFont(stylishFont);
            m_visibleTitles[i].text.setOutlineThickness(0.5);
            m_visibleTitles[i].text.setFillColor(m_textFillColor);
            m_visibleTitles[i].text.setOutlineColor(m_textOutlineColor);
            m_visibleTitles[i].text.setStyle(m_visibleTitles[i].text.getStyle() | sf::Text::Bold);
            posY += stylishFont.getLineSpacing(s_titlesTextSize);
        } else {
            m_visibleTitles[i].text.setFont(stylishFont);
            m_visibleTitles[i].text.setOutlineThickness(1.5);
            m_visibleTitles[i].text.setFillColor(sf::Color::Black);
            m_visibleTitles[i].text.setOutlineColor(sf::Color::Transparent);
            posY += stylishFont.getLineSpacing(s_titlesTextSize) * 1.2;
        }

    }

    m_textRect.x = 317;
    m_textRect.y = 280;
    m_textRect.width = s_textWidth;
    m_textRect.height = 255;

    const sf::Font &font = SfmlRenderTarget::plainFont();
    posY = m_textRect.y;
    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_visibleText[i].setFont(font);
        m_visibleText[i].setCharacterSize(s_mainTextSize);
        m_visibleText[i].setPosition(m_textRect.x, posY);
        if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
            m_visibleText[i].setFillColor(m_textFillColor);
        } else {
            m_visibleText[i].setFillColor(sf::Color::Black);
        }
        posY += font.getLineSpacing(s_mainTextSize);
    }

    // Main screen button
    if (DataManager::Inst().gameVersion() >= genie::GV_SWGB) {
        m_uiElements[MainScreenButton].rect = ScreenRect(m_textRect.center().x - 90,  m_textRect.bottom() + 10, 200, 40);

        m_mainScreenText.setFont(SfmlRenderTarget::plainFont());
        m_mainScreenText.setStyle(m_mainScreenText.getStyle() | sf::Text::Bold);
    } else {
        const genie::PalFile &buttonPalette = AssetManager::Inst()->getPalette(50531);
        genie::SlpFramePtr buttonBg = slpFile->getFrame(0);
        m_uiElements[MainScreenButton].texture.loadFromImage(Resource::convertFrameToImage(buttonBg, buttonPalette));
        m_uiElements[MainScreenButton].pressTexture.loadFromImage(Resource::convertFrameToImage(slpFile->getFrame(1), buttonPalette));
        ScreenRect buttonRect(m_textRect.center().x - buttonBg->getWidth() / 2.f,  m_textRect.bottom(), buttonBg->getWidth(), buttonBg->getHeight());
        m_uiElements[MainScreenButton].rect = buttonRect;

        m_mainScreenText.setFont(SfmlRenderTarget::stylishFont());
    }

    m_mainScreenText.setString("Main Menu");
    m_mainScreenText.setCharacterSize(s_buttonTextSize);
    m_mainScreenText.setFillColor(m_textFillColor);
    m_mainScreenText.setOutlineColor(m_textOutlineColor);
    m_mainScreenText.setOutlineThickness(1);

    loadFile(m_historyEntries[0].filename);

    updateVisibleTitles();

    return true;
}

void HistoryScreen::display()
{
    run();
}


void HistoryScreen::render()
{
    if (m_currentEntry >= 0) {
        sf::Sprite sprite;
        const sf::Texture &illustration = m_historyEntries[m_currentEntry].illustration;
        sprite.setPosition(529 - illustration.getSize().x/2.f, 73);
        sprite.setTexture(illustration);
        m_renderWindow->draw(sprite);

        sf::Sprite secondarySprite;
        secondarySprite.setPosition(14, 407);
        secondarySprite.setTexture(m_historyEntries[m_currentEntry].secondaryIllustration);
        m_renderWindow->draw(secondarySprite);
    }
    m_renderWindow->draw(m_titleText);

    for (int i=0; i<UiElementsCount; i++) {
        sf::Sprite buttonSprite;
        if (i == m_pressedUiElement && m_uiElements[i].pressTexture.getSize().x > 0) {
            buttonSprite.setTexture(m_uiElements[i].pressTexture);
        } else if (i == m_currentUiElement && m_uiElements[i].hoverTexture.getSize().x > 0) {
            buttonSprite.setTexture(m_uiElements[i].hoverTexture);
        } else {
            buttonSprite.setTexture(m_uiElements[i].texture);
        }
        buttonSprite.setPosition(m_uiElements[i].rect.topLeft());
        m_renderWindow->draw(buttonSprite);
    }

    for (int i=0; i<s_numVisibleTextLines; i++) {
        m_renderWindow->draw(m_visibleText[i]);
    }
    for (int i=0; i<s_numListEntries; i++) {
        m_renderWindow->draw(m_visibleTitles[i].text);
    }

    int textX = m_uiElements[MainScreenButton].rect.center().x - m_mainScreenText.getLocalBounds().width / 2;
    int textY = m_uiElements[MainScreenButton].rect.center().y - m_mainScreenText.getLocalBounds().height / 2;
    if (m_pressedUiElement == MainScreenButton) {
        textX += 2;
        textY -= 2;
    }
    m_mainScreenText.setPosition(textX, textY);
    m_renderWindow->draw(m_mainScreenText);
}

bool HistoryScreen::handleMouseEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseMoved) {
        if (m_pressedUiElement == TitlesPositionIndicator) {
            const int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height/2;
            m_titleScrollOffset = (m_historyEntries.size() - s_numListEntries) * (event.mouseMove.y - m_uiElements[TitlesUpButton].rect.bottom()) / maxY;
            m_titleScrollOffset = std::min(m_titleScrollOffset, int(m_historyEntries.size()) - s_numListEntries);
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
            if (m_uiElements[i].rect.contains(ScreenPos(event.mouseMove.x, event.mouseMove.y)) && m_uiElements[i].hoverTexture.getSize().x > 0) {
                m_currentUiElement = UiElements(i);
                return false;
            }
        }
        return false;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        m_pressedUiElement = InvalidUiElement;

        for (int i=0; i<s_numListEntries; i++) {
            if (m_visibleTitles[i].rect.contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
                const int index = i + m_titleScrollOffset;
                if (m_historyEntries[index].title.empty()) {
                    return false;
                }
                m_currentEntry = index;
                loadFile(m_historyEntries[index].filename);
                updateVisibleTitles();
                return false;
            }
        }

        for (int i=UiElementsCount-1; i>=0; i--) {
            if (!m_uiElements[i].rect.contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
                continue;
            }

            m_pressedUiElement = UiElements(i);

            switch (i) {
            case TitlesUpButton:
                if (m_titleScrollOffset > 0) {
                    m_titleScrollOffset--;
                    updateVisibleTitles();
                }

                break;
            case TitlesDownButton:
                if (m_titleScrollOffset < int(m_historyEntries.size()) - s_numListEntries) {
                    m_titleScrollOffset++;
                    updateVisibleTitles();
                }

                break;
            case TitlesScrollbar: {
                const int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height/2;
                m_titleScrollOffset = (m_historyEntries.size() - s_numListEntries) * (event.mouseButton.y - m_uiElements[TitlesUpButton].rect.bottom()) / maxY;
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
        if (m_pressedUiElement == MainScreenButton && m_uiElements[m_pressedUiElement].rect.contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
            return true;
        }

        m_pressedUiElement = InvalidUiElement;
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.x > 22 && event.mouseWheelScroll.x < 220 && event.mouseWheelScroll.y > 25 && event.mouseWheelScroll.y < 375) {
            if (event.mouseWheelScroll.delta < 0) {
                if (m_titleScrollOffset < int(m_historyEntries.size()) - s_numListEntries) {
                    m_titleScrollOffset++;
                    updateVisibleTitles();
                }
            } else {
                if (m_titleScrollOffset > 0) {
                    m_titleScrollOffset--;
                    updateVisibleTitles();
                }
            }
        }
        if (m_textRect.contains(ScreenPos(event.mouseWheelScroll.x, event.mouseWheelScroll.y))) {
            if (event.mouseWheelScroll.delta < 0) {
                if (m_textScrollOffset < int(m_textLines.size()) - s_numVisibleTextLines) {
                    m_textScrollOffset++;
                    updateVisibleText();
                }
            } else {
                if (m_textScrollOffset > 0) {
                    m_textScrollOffset--;
                    updateVisibleText();
                }
            }
        }

    }
    return false;
}

void HistoryScreen::handleKeyEvent(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up) {
        if (m_textScrollOffset > 0) {
            m_textScrollOffset--;
            updateVisibleText();
        }
    } else if (event.key.code == sf::Keyboard::Down) {
        if (m_textScrollOffset < int(m_textLines.size()) - s_numVisibleTextLines) {
            m_textScrollOffset++;
            updateVisibleText();
        }
    }

}

void HistoryScreen::loadFile(const std::string &filePath)
{
    m_textLines.clear();

    std::ifstream file(filePath, std::ios_base::binary);
    if (!file.is_open()) {
        WARN << "failed to open" << filePath;
        return;
    }
    m_titleText.setString(m_historyEntries[m_currentEntry].title);

    m_textScrollOffset = 0;

    TextLine currentLine;

    const sf::Font &font = SfmlRenderTarget::uiFont();

    std::string currentWord;
    float currentWordWidth= 0.f;
    const float spaceWidth = font.getGlyph(' ', s_mainTextSize, false).advance;
    while (!file.eof()) {
        char character = file.get();

        if (character == '\r') {
            continue;
        }

        if (character != ' ' && character != '\n') {
            currentWord += character;
            currentWordWidth += font.getGlyph(character, s_mainTextSize, false).advance;
            continue;
        }

        if (character == '\n') {
            if (currentLine.width + currentWordWidth > s_textWidth) {
                m_textLines.push_back(std::move(currentLine));
                currentLine = TextLine();
            }

            currentLine.text += currentWord;

            m_textLines.push_back(std::move(currentLine));
            currentLine = TextLine();
            currentWord.clear();
            currentWordWidth = 0;
            continue;
        }

        if (currentLine.width + currentWordWidth > s_textWidth) {
            m_textLines.push_back(std::move(currentLine));
            currentLine = TextLine();
        }

        currentLine.text += currentWord + ' ';
        currentLine.width += currentWordWidth + spaceWidth;

        currentWord.clear();
        currentWordWidth = 0;
    }

    if (!currentLine.text.empty()) {
        m_textLines.push_back(std::move(currentLine));
    }

    // TODO: I'm lazy, parse good, different styling in a single line
    for (TextLine &line : m_textLines) {
        if (line.text.empty()) {
            continue;
        }
        if (line.text[0] != '<') {
            continue;
        }
        if (util::toLowercase(line.text).starts_with("<b>")) {
            line.bold = true;
        } else if (util::toLowercase(line.text).starts_with("<i>")) {
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

        const size_t index = i + m_textScrollOffset;
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

    float maxY = m_uiElements[TextDownButton].rect.y - m_uiElements[TextUpButton].rect.bottom() - m_uiElements[TextPositionIndicator].rect.height;
    m_uiElements[TextPositionIndicator].rect.y = m_uiElements[TextUpButton].rect.bottom() + maxY * m_textScrollOffset / int(m_textLines.size() - s_numVisibleTextLines);
}

void HistoryScreen::updateVisibleTitles()
{
    for (int i=0; i<s_numListEntries; i++) {
        const size_t index = i + m_titleScrollOffset;

        if (int(index) == m_currentEntry) {
            m_visibleTitles[i].text.setOutlineColor(sf::Color(192, 192, 0));
        } else {
            m_visibleTitles[i].text.setOutlineColor(sf::Color::Transparent);
        }

        if (index >= m_historyEntries.size()) {
            m_visibleTitles[i].text.setString("");
            continue;
        }
        m_visibleTitles[i].text.setString(m_historyEntries[index].title);
    }
    int maxY = m_uiElements[TitlesDownButton].rect.y - m_uiElements[TitlesUpButton].rect.bottom() - m_uiElements[TitlesPositionIndicator].rect.height;
    m_uiElements[TitlesPositionIndicator].rect.y = m_uiElements[TitlesUpButton].rect.bottom() + maxY * m_titleScrollOffset / int(m_historyEntries.size() - s_numListEntries);
}

