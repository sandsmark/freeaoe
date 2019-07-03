/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#include "Engine.h"

#include <sstream>

#include <SFML/Graphics.hpp>

#include "ui/UiScreen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include "resource/AssetManager.h"
#include "resource/Resource.h"
#include "render/GraphicRender.h"
#include "global/Config.h"
#include <genie/resource/SlpFile.h>
#include <genie/resource/UIFile.h>

const sf::Clock Engine::GameClock;

//------------------------------------------------------------------------------
void Engine::start()
{
    DBG << "Starting engine.";

    ScreenPos mousePos;
    // Start the game loop
    while (renderWindow_->isOpen()) {
        std::shared_ptr<GameState> state = state_manager_.getActiveState();

        const int renderStart = GameClock.getElapsedTime().asMilliseconds();

        bool updated = false;

        // Process events
        sf::Event event;
        while (renderWindow_->pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                renderWindow_->close();
            }

            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2f mappedPos = renderWindow_->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                event.mouseButton.x = mappedPos.x;
                event.mouseButton.y = mappedPos.y;
                mousePos = ScreenPos(mappedPos);
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mappedPos = renderWindow_->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                event.mouseMove.x = mappedPos.x;
                event.mouseMove.y = mappedPos.y;
                mousePos = ScreenPos(mappedPos);
            }

            if (!handleEvent(event)) {
                state->handleEvent(event);
            }

            updated = true;
        }

        if (!m_currentDialog) {
            updated = state->update(GameClock.getElapsedTime().asMilliseconds()) || updated;
            if (state->unitManager()->state() == UnitManager::State::SelectingAttackTarget) {
                m_mouseCursor.setCursor(Cursor::Normal);
            } else {
                const Task targetAction = state->unitManager()->defaultActionAt(mousePos, renderTarget_->camera());
                if (!targetAction.data) {
                    m_mouseCursor.setCursor(Cursor::Normal);
                } else if (targetAction.data->ActionType == genie::Task::Combat) {
                    m_mouseCursor.setCursor(Cursor::Attack);
                } else {
                    m_mouseCursor.setCursor(Cursor::Action);
                }
            }
        } else {
            m_mouseCursor.setCursor(Cursor::Normal);
        }

        m_mouseCursor.sprite.setPosition(mousePos);

        if (updated) {
            // Clear screen
            renderWindow_->clear(sf::Color::Green);
            state->draw();
            if (m_currentDialog) {
                m_currentDialog->render(renderWindow_);
            }

            updateUi(state->humanPlayer());
            drawUi();
            const int renderTime = GameClock.getElapsedTime().asMilliseconds() - renderStart;

            if (renderTime > 0) {
                fps_label_.setString("fps: " + std::to_string(1000/renderTime));
            }

            renderWindow_->draw(fps_label_);
            renderWindow_->draw(m_mouseCursor.sprite);

            // Update the window
            renderWindow_->display();
        } else {
            sf::sleep(sf::milliseconds(1000 / 60));
        }

    }
}

void Engine::showStartScreen()
{
    genie::UIFilePtr uiFile = AssetManager::Inst()->getUIFile("scrstart.sin");
    if (!uiFile) {
        WARN << "failed to load ui file for start screen";
        return;
    }

    genie::SlpFilePtr loadingImageFile = AssetManager::Inst()->getSlp(uiFile->backgroundSmall.fileId);
    if (!loadingImageFile) {
        WARN << "Failed to load background for start screen" << uiFile->backgroundSmall.filename << uiFile->backgroundSmall.alternateFilename;
        return;
    }

    sf::Texture loadingScreen;
    loadingScreen.loadFromImage(Resource::convertFrameToImage(
                                    loadingImageFile->getFrame(0),
                                    AssetManager::Inst()->getPalette(uiFile->paletteFile.id)
                                    ));

    sf::Sprite sprite;
    sprite.setTexture(loadingScreen);
    sprite.setPosition(0, 0);
    sprite.setScale(renderWindow_->getSize().x / float(loadingScreen.getSize().x),
                    renderWindow_->getSize().y / float(loadingScreen.getSize().y));
    renderTarget_->draw(sprite);
    renderWindow_->display();
}

void Engine::loadTopButtons()
{
    genie::SlpFilePtr buttonsFile = AssetManager::Inst()->getSlp("btngame2x.shp");
    if (!buttonsFile) {
        WARN << "Failed to load SLP for buttons";
        return;
    }

    if (buttonsFile->getFrameCount() < TopMenuButton::ButtonsCount * 2) {
        WARN << "Not enough buttons";
    }

    int x = renderWindow_->getSize().x - 5;
    for (int i=0; i<TopMenuButton::ButtonsCount; i++) {
        TopMenuButton button;
        button.type = TopMenuButton::Type(i);

        button.texture.loadFromImage(Resource::convertFrameToImage(buttonsFile->getFrame(i * 2)));
        button.pressedTexture.loadFromImage(Resource::convertFrameToImage(buttonsFile->getFrame(i * 2 + 1)));

        button.rect.setSize(button.texture.getSize());
        x -= button.rect.width;

        button.rect.x = x;
        button.rect.y = 5;

        m_buttons.push_back(std::move(button));
    }
}

void Engine::drawUi()
{
    for (const TopMenuButton &button : m_buttons) {
        sf::Sprite sprite;
        if (button.type == m_pressedButton) {
            sprite.setTexture(button.pressedTexture);
        } else {
            sprite.setTexture(button.texture);
        }

        sprite.setPosition(button.rect.topLeft());
        renderWindow_->draw(sprite);
    }

    renderTarget_->draw(m_woodLabel.text);
    renderTarget_->draw(m_foodLabel.text);
    renderTarget_->draw(m_goldLabel.text);
    renderTarget_->draw(m_stoneLabel.text);
    renderTarget_->draw(m_populationLabel.text);
}

bool Engine::handleEvent(sf::Event event)
{
    if (m_currentDialog) {
        Dialog::Choice choice = m_currentDialog->handleEvent(event);
        if (choice == Dialog::Cancel) {
            m_currentDialog.reset();
        } else if (choice == Dialog::Quit) {
            renderWindow_->close();
        }

        return true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (m_pressedButton == TopMenuButton::GameMenu) {
            showMenu();
        }

        if (m_pressedButton != TopMenuButton::Invalid) {
            m_pressedButton = TopMenuButton::Invalid;
            return true;
        }

        return false;
    }

    if (event.type != sf::Event::MouseButtonPressed) {
        return false;
    }
    const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    for (const TopMenuButton &button : m_buttons) {
        if (button.rect.contains(mousePos)) {
            m_pressedButton = button.type;
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
Engine::Engine() :
    m_woodLabel(75, 5),
    m_foodLabel(153, 5),
    m_goldLabel(230, 5),
    m_stoneLabel(307, 5),
    m_populationLabel(384, 5)
{
    m_mainScreen = std::make_unique<UiScreen>("dlg_men.sin");
}

bool Engine::setup(const std::shared_ptr<genie::ScnFile> &scenario)
{
    renderWindow_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 1024), "freeaoe", sf::Style::None);
    renderWindow_->setMouseCursorVisible(false);
    renderWindow_->setFramerateLimit(60);

    m_mainScreen->setRenderWindow(renderWindow_);
    m_mainScreen->init();

    renderTarget_ = std::make_shared<SfmlRenderTarget>(*renderWindow_);

    showStartScreen();

    std::shared_ptr<GameState> gameState = std::make_shared<GameState>(renderTarget_);
    if (scenario) {
        gameState->setScenario(scenario);
    }

    if (!state_manager_.addActiveState(gameState)) {
        return false;
    }

    renderWindow_->setSize(gameState->uiSize());
    renderTarget_->setSize(gameState->uiSize());

    fps_label_.setPosition(sf::Vector2f(gameState->uiSize().width - 75, gameState->uiSize().height - 20));
    fps_label_.setFillColor(sf::Color::White);
    fps_label_.setFont(SfmlRenderTarget::defaultFont());
    fps_label_.setCharacterSize(15);

    m_woodLabel.setValue(12345);
    m_foodLabel.setValue(12345);
    m_goldLabel.setValue(12345);
    m_stoneLabel.setValue(12345);
    m_populationLabel.setValue(125);
    m_populationLabel.setMaxValue(125);

    loadTopButtons();

    m_mouseCursor.cursorsFile = AssetManager::Inst()->getSlp(AssetManager::filenameID("mcursors.shp"));
    if (m_mouseCursor.cursorsFile) {
        m_mouseCursor.texture.loadFromImage(Resource::convertFrameToImage(m_mouseCursor.cursorsFile->getFrame(Cursor::Normal)));
        m_mouseCursor.sprite.setTexture(m_mouseCursor.texture);
    } else {
        WARN << "Failed to get cursors";
    }

    return true;
}

void Engine::showMenu()
{
    genie::UIFilePtr uiFile = AssetManager::Inst()->getUIFile("dlg_men.sin");
    if (!uiFile) {
        WARN << "failed to load ui file for menu";
        return;
    }

    genie::SlpFilePtr backgroundSlp = AssetManager::Inst()->getSlp(uiFile->backgroundSmall.fileId);
    if (!backgroundSlp) {
        WARN << "Failed to load menu background";
        return;
    }
    sf::Image menuBg = Resource::convertFrameToImage(backgroundSlp->getFrame(0));

    m_currentDialog = std::make_unique<Dialog>(m_mainScreen.get());
    if (!m_currentDialog->background.loadFromImage(menuBg)) {
        WARN << "Failed to load menu background";
    }
    DBG << "showing menu";

}

void Engine::updateUi(const Player::Ptr &humanPlayer)
{
    m_woodLabel.setValue(humanPlayer->resourcesAvailable[genie::ResourceType::WoodStorage]);
    m_foodLabel.setValue(humanPlayer->resourcesAvailable[genie::ResourceType::FoodStorage]);
    m_goldLabel.setValue(humanPlayer->resourcesAvailable[genie::ResourceType::GoldStorage]);
    m_stoneLabel.setValue(humanPlayer->resourcesAvailable[genie::ResourceType::StoneStorage]);

    m_populationLabel.setValue(humanPlayer->resourcesUsed[genie::ResourceType::PopulationHeadroom]);
    m_populationLabel.setMaxValue(humanPlayer->resourcesAvailable[genie::ResourceType::PopulationHeadroom]);
}
