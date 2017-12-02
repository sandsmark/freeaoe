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
#include "render/GraphicRender.h"
#include "global/Config.h"

Logger& Engine::log = Logger::getLogger("freeaoe.Engine");

const sf::Clock Engine::GameClock;


//------------------------------------------------------------------------------
Engine::Engine() : renderWindow_(0)
{

}

//------------------------------------------------------------------------------
Engine::~Engine()
{
  log.info("Closing engine");
  
  delete renderWindow_;
}

//------------------------------------------------------------------------------
void Engine::start()
{
    Logger::setLogLevel(Logger::L_INFO);

    log.info("Starting engine.");

    setup();

    // Start the game loop
    while (renderWindow_->isOpen()) {
        IState *state = state_manager_.getActiveState();

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
            renderWindow_->clear();
            state->draw();
            drawFps();
            // Update the window
            renderWindow_->display();
        } else {
            sf::sleep(sf::milliseconds(1000 / 60));
        }

    }
}

//------------------------------------------------------------------------------
void Engine::setup()
{
//   renderWindow_ = new sf::RenderWindow(sf::VideoMode(384 - (48 + 96) + 296, 96*2 - (24 + 48)), "freeaoe");
  renderWindow_ = new sf::RenderWindow(sf::VideoMode(800, 600), "freeaoe");
  renderWindow_->setFramerateLimit(60);
  
  renderTarget_ = IRenderTargetPtr(new SfmlRenderTarget(*renderWindow_));
  
  GameState *gameState = new GameState(renderTarget_);
  
  std::string scnFile = Config::Inst()->getScenarioFile();
  
  if (!scnFile.empty())
  {
    std::shared_ptr<genie::ScnFile> scenario(new genie::ScnFile());
    scenario->load(scnFile.c_str());
    gameState->setScenario(scenario);
  }
  state_manager_.addActiveState(gameState);

  fps_label_.setPosition(sf::Vector2f(10,10));
  fps_label_.setColor(sf::Color::Green);
}

//------------------------------------------------------------------------------
void Engine::drawFps()
{ 
  /*
  static sf::Clock clock;

  if (clock.GetElapsedTime() >= 1000)
  {
    float fps = 1000 / render_window_->GetFrameTime();
  
    std::stringstream ss;
  
    ss << fps;
    sf::String dfps;
    dfps = "FPS: " + ss.str(); 
    fps_label_.SetString(dfps);    
    
    clock.Reset();
  }
  render_window_->Draw(fps_label_);
  */
}
