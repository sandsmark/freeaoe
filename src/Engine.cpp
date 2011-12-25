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

Logger& Engine::log = Logger::getLogger("freeaoe.Engine");

const sf::Clock Engine::GameClock;


//------------------------------------------------------------------------------
Engine::Engine() : render_window_(0), game_renderer_(0)
{

}

//------------------------------------------------------------------------------
Engine::~Engine()
{
  log.info("Closing engine");
  
  delete render_window_;
}

//------------------------------------------------------------------------------
void Engine::start()
{
  Logger::setLogLevel(Logger::L_INFO);
  
  log.info("Starting engine.");
  
  setup();
    
  // Start the game loop
  while (render_window_->IsOpened())
  {
    IState *state = state_manager_.getActiveState();
    
    
    res::GraphicPtr x = ResourceManager::Inst()->getGraphic(633);
    
    // Process events
    sf::Event event;
    while (render_window_->PollEvent(event))
    {
      // Close window : exit
      if (event.Type == sf::Event::Closed)
        render_window_->Close();

      //state->handleEvent(event);
    }
     
    // Clear screen
    render_window_->Clear();

    game_renderer_->draw(x, ScreenPos(10,10));
    //state->update();
    //state->draw();
    
    drawFps();
         
    // Update the window
    render_window_->Display();
  }

}

//------------------------------------------------------------------------------
void Engine::setup()
{
  render_window_ = new sf::RenderWindow(sf::VideoMode(1024, 786), "freeaoe");
  render_window_->SetFramerateLimit(60);
  
  game_renderer_ = new GameRenderer(*render_window_);
  
  //state_manager_.addActiveState(new GameState(render_window_));
  
  fps_label_.SetPosition(sf::Vector2f(10,10));
  fps_label_.SetColor(sf::Color::Green);
}

//------------------------------------------------------------------------------
void Engine::drawFps()
{ 
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
}
