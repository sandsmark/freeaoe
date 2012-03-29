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


#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

#include "global/Logger.h"
#include "mechanics/StateManager.h"

namespace sf {
class RenderWindow;
}

class Engine
{

public:
  static const sf::Clock GameClock;
  
  Engine();
  virtual ~Engine();
  
  void start();
  
private:
  static Logger &log;
  
  sf::RenderWindow *render_window_;

  
  StateManager state_manager_;
  
  sf::Text fps_label_;
  
  void setup();
  
  void drawFps();
  
  
};

#endif // ENGINE_H
