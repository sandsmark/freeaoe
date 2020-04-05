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

#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "mechanics/GameState.h"
#include "mechanics/Map.h"
#include "mechanics/Player.h"
#include "mechanics/ScenarioController.h"
#include "mechanics/UnitManager.h"

#include "render/Camera.h"
#include "render/SfmlRenderTarget.h"
#include "render/MapRenderer.h"

#include "ui/ActionPanel.h"
#include "ui/Dialog.h"
#include "ui/IconButton.h"
#include "ui/Minimap.h"
#include "ui/NumberLabel.h"
#include "ui/UiScreen.h"
#include "ui/UnitInfoPanel.h"

#include "resource/AssetManager.h"
#include "resource/Resource.h"
#include "ui/MouseCursor.h"
#include "settings/input.h"

#include <genie/dat/ResourceUsage.h>
#include <genie/resource/SlpFile.h>
#include <genie/resource/UIFile.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <algorithm>
#include <utility>

#include <cstddef>

#define MOUSE_MOVE_EDGE_SIZE 10
#define CAMERA_SPEED 1.


const sf::Clock Engine::GameClock;

//------------------------------------------------------------------------------
void Engine::start()
{
    DBG << "Starting engine.";
    std::shared_ptr<GameState> state;

    ScreenPos mousePos;
    // Start the game loop
    size_t fpsSamples = 0;
    double totalFps = 0;
    while (renderWindow_->isOpen()) {
        if (state != state_manager_.getActiveState()) {
            state = state_manager_.getActiveState();
            m_minimap->setUnitManager(state->unitManager());
            m_minimap->setMap(state->map());
            m_minimap->setVisibilityMap(state->humanPlayer()->visibility);

            m_mapRenderer->setVisibilityMap(state->humanPlayer()->visibility);
            m_mapRenderer->setMap(state->map());

            m_actionPanel->setUnitManager(state->unitManager());
            m_actionPanel->setHumanPlayer(state->humanPlayer());
            m_unitInfoPanel->setUnitManager(state->unitManager());
        }

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

            if (!handleEvent(event, state)) {
//                state->handleEvent(event);
            }

            updated = true;
        }

        if (!m_currentDialog && state->result == GameState::Result::Running) {
            updated = state->update(GameClock.getElapsedTime().asMilliseconds()) || updated;

            if (state->result != GameState::Result::Running) {
                if (state->result == GameState::Result::Won) {
                    m_resultOverlay.setString("You won.");
                } else {
                    m_resultOverlay.setString("You were defeated."); // TODO: don't remember the exact text
                }
                const ScreenRect labelRect = m_resultOverlay.getLocalBounds();
                const Size windowSize = renderWindow_->getSize();

                m_resultOverlay.setPosition(windowSize.width / 2 - labelRect.width / 2, windowSize.height / 2 - labelRect.height / 2);
            }
        }

        updated = m_mouseCursor->setPosition(mousePos) || updated;
        updated = updateUi(state) || updated;


        if (m_selecting) {
            ScreenRect selectionRect(m_selectionStart, m_selectionCurr);
            if (selectionRect != m_selectionRect) {
                m_selectionRect = selectionRect;
                updated = true;
            }
        }


        if (updated) {
            // Clear screen
            renderWindow_->clear(sf::Color::Green);
            m_mapRenderer->display();

            std::vector<std::weak_ptr<Entity>> visibleEntities;
            visibleEntities = state->map()->entitiesBetween(m_mapRenderer->firstVisibleColumn(),
                                                            m_mapRenderer->firstVisibleRow(),
                                                            m_mapRenderer->lastVisibleColumn(),
                                                            m_mapRenderer->lastVisibleRow());

            state->unitManager()->render(renderTarget_, visibleEntities);

            state->draw();

            if (m_currentDialog) {
                m_currentDialog->render(renderWindow_);
            }

            if (state->result != GameState::Result::Running) {
                renderTarget_->draw(m_resultOverlay);
            }

            drawUi();

            const int renderTime = GameClock.getElapsedTime().asMilliseconds() - renderStart;

            if (renderTime > 0) {
                fpsSamples++;
                totalFps += 1000. / renderTime;
                fps_label_.setString("fps: " + std::to_string(1000/renderTime));
            }

            // Update the window
            renderWindow_->display();
        } else {
            sf::sleep(sf::milliseconds(1000 / 60));
        }

    }
    DBG << "avg fps:" << (totalFps / fpsSamples);
}

void Engine::addMessage(const std::string &message)
{
    for (int i=0; i<s_numMessagesLines - 1; i++) {
        m_visibleText[i].setString(m_visibleText[i+1].getString());
    }
    m_visibleText[s_numMessagesLines - 1].setString(message);
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
    float x = renderWindow_->getSize().x - 5;
    for (int i=0; i<IconButton::ButtonsCount; i++) {
        std::unique_ptr<IconButton> button = std::make_unique<IconButton>(renderTarget_);

        button->setType(IconButton::Type(i));

        x -= button->rect().width;
        button->setPosition({x, 5});

        m_buttons.push_back(std::move(button));
    }
}

void Engine::loadUiOverlay()
{
    std::shared_ptr<genie::SlpFile> overlayFile = AssetManager::Inst()->getUiOverlay(AssetManager::Ui1280x1024, AssetManager::Viking);
    if (overlayFile) {
        m_uiOverlay = renderTarget_->convertFrameToImage(overlayFile->getFrame());
        DBG << "Loaded UI overlay with size" << m_uiOverlay->size;
    } else {
        AssetManager::UiResolution attemptedResolution = AssetManager::Ui1280x1024;
        AssetManager::UiCiv attemptedCiv = AssetManager::Briton;
        do {
            attemptedCiv = AssetManager::UiCiv(attemptedCiv + 1);
            if (attemptedCiv > AssetManager::Korean) {
                if (attemptedResolution == AssetManager::Ui1280x1024) {
                    attemptedResolution = AssetManager::Ui1024x768;
                } else if (attemptedResolution == AssetManager::Ui1024x768) {
                    attemptedResolution = AssetManager::Ui800x600;
                } else {
                    break;
                }

                attemptedCiv = AssetManager::Briton;
            }
            overlayFile = AssetManager::Inst()->getUiOverlay(attemptedResolution, attemptedCiv);
        } while (!overlayFile);

        if (overlayFile) {
            WARN << "Loaded fallback ui overlay res" << attemptedResolution << "for civ" << attemptedCiv;
            m_uiOverlay = renderTarget_->convertFrameToImage(overlayFile->getFrame());
        } else {
            WARN << "Failed to load ui overlay";
        }
    }
}

void Engine::drawUi()
{
    if (m_selecting) {
        renderTarget_->draw(m_selectionRect, Drawable::Transparent, Drawable::White);
    }

    renderTarget_->draw(m_uiOverlay, ScreenPos(0, 0));

    for (const std::unique_ptr<IconButton> &button : m_buttons) {
        button->render();
    }

    m_minimap->draw();
    m_actionPanel->draw();
    m_unitInfoPanel->draw();

    m_woodLabel->render();
    m_foodLabel->render();
    m_goldLabel->render();
    m_stoneLabel->render();
    m_populationLabel->render();

    renderWindow_->draw(fps_label_);

    for (sf::Text &messageLine : m_visibleText) {
        renderWindow_->draw(messageLine);
    }

    m_mouseCursor->render();
}

bool Engine::handleEvent(const sf::Event &event, const std::shared_ptr<GameState> &state)
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

    if (m_actionPanel->handleEvent(event)) {
        return true;
    }
    if (m_minimap->handleEvent(event)) {
        return true;
    }
    if (m_unitInfoPanel->handleEvent(event)) {
        return true;
    }

    switch(event.type) {
    case sf::Event::KeyPressed:
        return handleKeyEvent(event, state);
    case sf::Event::MouseButtonPressed:
        return handleMousePress(event, state);
    case sf::Event::MouseButtonReleased:
        return handleMouseRelease(event, state);
    case sf::Event::MouseMoved:
        return handleMouseMove(event, state);
    default:
        break;
    }

    return false;
}

bool Engine::handleKeyEvent(const sf::Event &event, const std::shared_ptr<GameState> &state)
{
    ScreenPos cameraScreenPos = renderTarget_->camera()->targetPosition().toScreen();

    switch(event.key.code) {
    case sf::Keyboard::Left:
        cameraScreenPos.x -= 20;
        break;

    case sf::Keyboard::Right:
        cameraScreenPos.x += 20;
        break;

    case sf::Keyboard::Down:
        cameraScreenPos.y -= 20;
        break;

    case sf::Keyboard::Up:
        cameraScreenPos.y += 20;
        break;

    default:
        return false;
    }

    MapPos cameraMapPos = cameraScreenPos.toMap().clamped(state->map()->pixelSize());

    renderTarget_->camera()->setTargetPosition(cameraMapPos);

    return true;

}

bool Engine::handleMouseMove(const sf::Event &event, const std::shared_ptr<GameState> &state)
{
    const ScreenPos mousePos = ScreenPos(event.mouseMove.x, event.mouseMove.y);
    bool handled = false;

    if (mousePos.x < MOUSE_MOVE_EDGE_SIZE) {
        m_cameraDeltaX = -1;
        handled = true;
    } else if (mousePos.x > renderTarget_->getSize().width - MOUSE_MOVE_EDGE_SIZE) {
        m_cameraDeltaX = 1;
        handled = true;
    } else {
        m_cameraDeltaX = 0;
    }

    if (mousePos.y < MOUSE_MOVE_EDGE_SIZE) {
        m_cameraDeltaY = 1;
        handled = true;
    } else if (mousePos.y > renderTarget_->getSize().height - MOUSE_MOVE_EDGE_SIZE) {
        m_cameraDeltaY = -1;
        handled = true;
    } else {
        m_cameraDeltaY = 0;
    }

    if (mousePos.y < 800) {
        if (m_selecting) {
            m_selectionCurr = mousePos;
            handled = true;
        } else {
            state->unitManager()->onMouseMove(renderTarget_->camera()->absoluteMapPos(mousePos));
        }
    }

    return handled;
}

bool Engine::handleMousePress(const sf::Event &event, const std::shared_ptr<GameState> &state)
{
    const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    bool updated = false;
    for (const std::unique_ptr<IconButton> &button : m_buttons) {
        updated = button->onMousePressed(mousePos) || updated;
    }
    if (updated) {
        return true;
    }

    if (mousePos.y < 800 && event.mouseButton.button == sf::Mouse::Button::Left) {
        if (state->unitManager()->onLeftClick(ScreenPos(event.mouseButton.x, event.mouseButton.y), renderTarget_->camera())) {
            return true;
        }

        m_selectionStart = mousePos;
        m_selectionCurr = mousePos + ScreenPos(1, 1);
        m_selecting = true;
    }

    return true;
}

bool Engine::handleMouseRelease(const sf::Event &event, const std::shared_ptr<GameState> &state)
{
    const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);

    if (mousePos.y < 800 && event.mouseButton.button == sf::Mouse::Button::Left) {
        if (state->unitManager()->onMouseRelease()) {
            return true;
        }
    }

    IconButton::Type clickedButton = IconButton::Invalid;
    for (const std::unique_ptr<IconButton> &button : m_buttons) {
        if (button->onMouseReleased(mousePos)) {
            clickedButton = button->type();
        }
    }
    if (clickedButton == IconButton::GameMenu) {
        showMenu();
    }
    if (clickedButton != IconButton::Invalid) {
        return true;
    }

    if (event.mouseButton.button == sf::Mouse::Button::Left && m_selecting) {
        state->unitManager()->selectUnits(m_selectionRect, renderTarget_->camera());
        m_selectionRect = ScreenRect();
        m_selecting = false;
        return true;
    }
    if (event.mouseButton.button == sf::Mouse::Button::Right) {
        state->unitManager()->onRightClick(mousePos, renderTarget_->camera());
    }

    return false;
}

//------------------------------------------------------------------------------
Engine::Engine()
{
    m_mainScreen = std::make_unique<UiScreen>("dlg_men.sin");
}

// Just to make the crappy gcc unique_ptr implementation work, we can't use = default
Engine::~Engine() { } // NOLINT

bool Engine::setup(const std::shared_ptr<genie::ScnFile> &scenario)
{
    renderWindow_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 1024), "freeaoe", sf::Style::None);
    renderWindow_->setFramerateLimit(60);

    m_mainScreen->setRenderWindow(renderWindow_);
    m_mainScreen->init();

    renderTarget_ = std::make_shared<SfmlRenderTarget>(*renderWindow_);

    m_mouseCursor = std::make_unique<MouseCursor>(renderTarget_);
    if (m_mouseCursor->isValid()) {
        renderWindow_->setMouseCursorVisible(false);
    }

    m_woodLabel = std::make_unique<NumberLabel>(renderTarget_);
    m_foodLabel = std::make_unique<NumberLabel>(renderTarget_);
    m_goldLabel = std::make_unique<NumberLabel>(renderTarget_);
    m_stoneLabel = std::make_unique<NumberLabel>(renderTarget_);
    m_populationLabel = std::make_unique<NumberLabel>(renderTarget_);

    m_woodLabel->setPosition({75, 5});
    m_foodLabel->setPosition({153, 5});
    m_goldLabel->setPosition({230, 5});
    m_stoneLabel->setPosition({307, 5});
    m_populationLabel->setPosition({384, 5});

    showStartScreen();

    std::shared_ptr<GameState> gameState = std::make_shared<GameState>(renderTarget_);
    if (scenario) {
        gameState->setScenario(scenario);
    }
    gameState->scenarioController()->setEngine(this);

    if (!state_manager_.addActiveState(gameState)) {
        return false;
    }

    m_minimap = std::make_unique<Minimap>(renderTarget_);
    if (!m_minimap->init()) {
        WARN << "failed to init minimap";
    }

    m_actionPanel = std::make_unique<ActionPanel>(renderTarget_);
    if (!m_actionPanel->init()) {
        WARN << "failed to init action panel";
    }

    m_unitInfoPanel = std::make_unique<UnitInfoPanel>(renderTarget_);
    if (!m_unitInfoPanel->init()) {
        WARN << "failed to init info panel";
    }

    m_mapRenderer = std::make_unique<MapRenderer>();
    m_mapRenderer->setRenderTarget(renderTarget_);

    loadUiOverlay();

    Size uiSize = m_uiOverlay->size;
    if (!m_uiOverlay->size.isValid()) {
        WARN << "We don't have a valid UI overlay";
        uiSize = Size(640, 480);
    }

    renderWindow_->setSize(uiSize);
    renderTarget_->setSize(uiSize);

    m_resultOverlay.setFillColor(sf::Color::White);
    m_resultOverlay.setFont(SfmlRenderTarget::defaultFont());
    m_resultOverlay.setCharacterSize(25);
    m_resultOverlay.setOutlineColor(sf::Color::Black);
    m_resultOverlay.setOutlineThickness(3);

    fps_label_.setPosition(sf::Vector2f(uiSize.width - 75, uiSize.height - 20));
    fps_label_.setFillColor(sf::Color::White);
    fps_label_.setFont(SfmlRenderTarget::defaultFont());
    fps_label_.setCharacterSize(15);

    m_woodLabel->setValue(12345);
    m_foodLabel->setValue(12345);
    m_goldLabel->setValue(12345);
    m_stoneLabel->setValue(12345);
    m_populationLabel->setValue(125);
    m_populationLabel->setMaxValue(125);

    loadTopButtons();

    const sf::Font &font = SfmlRenderTarget::defaultFont();
    int posY = 30;
    for (int i=0; i<s_numMessagesLines; i++) {
        m_visibleText[i].setFont(font);
        m_visibleText[i].setCharacterSize(14);
        m_visibleText[i].setPosition(5, posY);
        m_visibleText[i].setOutlineColor(sf::Color::Black);
        m_visibleText[i].setOutlineThickness(2);
        m_visibleText[i].setFillColor(sf::Color::White);
        posY += font.getLineSpacing(13);
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

bool Engine::updateUi(const std::shared_ptr<GameState> &state)
{
    const int deltaTime = GameClock.getElapsedTime().asMilliseconds() - m_lastUpdate;

    bool updated = false;

    const Player::Ptr &humanPlayer = state->humanPlayer();
    updated = m_woodLabel->setValue(humanPlayer->resourcesAvailable(genie::ResourceType::WoodStorage)) || updated;
    updated = m_foodLabel->setValue(humanPlayer->resourcesAvailable(genie::ResourceType::FoodStorage)) || updated;
    updated = m_goldLabel->setValue(humanPlayer->resourcesAvailable(genie::ResourceType::GoldStorage)) || updated;
    updated = m_stoneLabel->setValue(humanPlayer->resourcesAvailable(genie::ResourceType::StoneStorage)) || updated;

    updated = m_populationLabel->setValue(humanPlayer->resourcesUsed(genie::ResourceType::PopulationHeadroom)) || updated;
    updated = m_populationLabel->setMaxValue(humanPlayer->resourcesAvailable(genie::ResourceType::PopulationHeadroom)) || updated;

    updated = m_mouseCursor->update(state->unitManager()) || updated;

    updated = m_mapRenderer->update(GameClock.getElapsedTime().asMilliseconds()) || updated;

    updated = updateCamera(state) || updated;

    updated = m_minimap->update(deltaTime) || updated;
    updated = m_actionPanel->update(deltaTime) || updated;
    updated = m_unitInfoPanel->update(deltaTime) || updated;

    m_lastUpdate = GameClock.getElapsedTime().asMilliseconds();
    return updated;
}

bool Engine::updateCamera(const std::shared_ptr<GameState> &state)
{
    if (m_cameraDeltaX == 0 && m_cameraDeltaY == 0) {
        return false;
    }

    ScreenPos cameraScreenPos = renderTarget_->camera()->targetPosition().toScreen();

    const int deltaTime = GameClock.getElapsedTime().asMilliseconds() - m_lastUpdate;
    cameraScreenPos.x += m_cameraDeltaX * deltaTime * CAMERA_SPEED;
    cameraScreenPos.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;

    MapPos cameraMapPos = cameraScreenPos.toMap().clamped(state->map()->pixelSize());
    renderTarget_->camera()->setTargetPosition(cameraMapPos);


    if (m_selecting) {
        m_selectionStart.x -= m_cameraDeltaX * deltaTime * CAMERA_SPEED;
        m_selectionStart.y += m_cameraDeltaY * deltaTime * CAMERA_SPEED;
        m_selectionRect = ScreenRect(m_selectionStart, m_selectionCurr);
    }

    return true;
}
