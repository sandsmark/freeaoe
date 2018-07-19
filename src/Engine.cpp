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

#include <SFML/Graphics/RenderWindow.hpp>
#include "resource/ResourceManager.h"
#include "resource/Resource.h"
#include "render/GraphicRender.h"
#include "global/Config.h"
#include <genie/resource/SlpFile.h>

const sf::Clock Engine::GameClock;


//------------------------------------------------------------------------------
Engine::Engine()
{

}

//------------------------------------------------------------------------------
Engine::~Engine()
{
  DBG << "Closing engine";
}

//------------------------------------------------------------------------------
void Engine::start()
{
    DBG << "Starting engine.";

    // Start the game loop
    while (renderWindow_->isOpen()) {
        std::shared_ptr<GameState> state = state_manager_.getActiveState();

        const int renderStart = GameClock.getElapsedTime().asMilliseconds();

        bool updated = false;

        // Process events
        sf::Event event;
        while (renderWindow_->pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                renderWindow_->close();

            state->handleEvent(event);

            updated = true;
        }

        updated = state->update(GameClock.getElapsedTime().asMilliseconds()) || updated;

        if (updated) {
            // Clear screen
            renderWindow_->clear(sf::Color::Green);
            state->draw();
            const int renderTime = GameClock.getElapsedTime().asMilliseconds() - renderStart;

            if (renderTime > 0) {
                fps_label_.setString("fps: " + std::to_string(1000/renderTime));
            }

            renderWindow_->draw(fps_label_);

            // Update the window
            renderWindow_->display();
        } else {
            sf::sleep(sf::milliseconds(1000 / 60));
        }

    }
}

//------------------------------------------------------------------------------
bool Engine::setup(const std::string &scnFile)
{
  renderWindow_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 1024), "freeaoe");
  renderWindow_->setMouseCursorVisible(false);
  renderWindow_->setFramerateLimit(60);
  
  renderTarget_ = std::make_shared<SfmlRenderTarget>(*renderWindow_);

  genie::SlpFilePtr loadingImageFile = ResourceManager::Inst()->getSlp("scrstart.slp");
  if (loadingImageFile) {
      sf::Texture loadingScreen;
      loadingScreen.loadFromImage(res::Resource::convertFrameToImage(
                                      loadingImageFile->getFrame(0),
                                      ResourceManager::Inst()->getPalette("scrstart.pal")
                                      ));
      sf::Sprite sprite;
      sprite.setTexture(loadingScreen);
      sprite.setPosition(0, 0);
      sprite.setScale(renderWindow_->getSize().x / float(loadingScreen.getSize().x),
                      renderWindow_->getSize().y / float(loadingScreen.getSize().y));
      renderTarget_->draw(sprite);
      renderWindow_->display();
  }

  std::shared_ptr<GameState> gameState = std::make_shared<GameState>(renderTarget_);

  if (!scnFile.empty()) {
      try {
          std::shared_ptr<genie::ScnFile> scenario(new genie::ScnFile());
          scenario->load(scnFile.c_str());
          gameState->setScenario(scenario);
      } catch (const std::exception &error) {
          WARN << "Failed to load" << scnFile << ":" << error.what();
          return false;
      }
  } else {
//      gameState->setScenario(ResourceManager::Inst()->getScn(56005));
  }

  if (!state_manager_.addActiveState(gameState)) {
      return false;
  }
  renderWindow_->setSize(gameState->uiSize());
  renderTarget_->setSize(gameState->uiSize());

  fps_label_.setPosition(sf::Vector2f(gameState->uiSize().width - 75, 5));
  fps_label_.setFillColor(sf::Color::White);
  font_.loadFromFile(FONT_DIR "Alegreya-Bold.latin");
  fps_label_.setFont(font_);
  fps_label_.setCharacterSize(15);

  return true;
}
